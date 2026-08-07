#ifndef IPAT_HELPER_H
#define IPAT_HELPER_H

constexpr auto DEPOSIT_DEFAULT_VALUE		= 1000;	// 自動入金のデフォルト値(円)
constexpr auto DEFAULT_CONFIRM_TIMEOUT		= 10000;// 自動入金時のデフォルトタイムアウト(ms)
constexpr auto DEFAULT_BET_TIMEOUT			= 500;	// 馬券購入間隔のデフォルト値(ms)
constexpr auto DEFAULT_RETRY_COUNT			= 10;	// 入出金処理のデフォルトリトライ回数

constexpr auto WIN5_RACE_COUNT				= 5;	// WIN5のレース数
constexpr auto UMABAN_COLUMN_COUNT			= 3;	// フォーメーションでの列数
constexpr auto UMABAN_TICKET_COLUMN_COUNT	= 5;	// フォーメーションでの列数(WIN5も含める)

// 投票電文の金額フィールドは16進4桁のため、電文として表現できる金額には上限がある。
// これは電文フォーマット側の不変条件で、実際に指定できる上限ではない(下記参照)。
constexpr auto MAX_KINGAKU_UNIT				= 0xFFFF;					// 100円単位での上限
constexpr auto MAX_KINGAKU_YEN				= MAX_KINGAKU_UNIT * 100;	// 6,553,500円

// 1回の送信あたりの合計購入金額の上限(円)。I-PAT のフロントエンドが
// CN_TOTALMONEYMAX として同じ値で検査しており、超過するとサーバに拒否される。
// 1点でもこの上限が効くため、実際に指定できる1点あたりの金額上限もこの値になる
// (MAX_KINGAKU_YEN には到達しない)。
constexpr auto MAX_TOTAL_AMOUNT_PER_SEND	= 1000000;					// 1,000,000円

// ---------------------------------------------------------------------------
// 呼び出し規約
//   公開関数・コールバックはすべて __cdecl。x64 では規約が1つのため差は出ないが、
//   x86 版も配布しているため明示する (C# の [DllImport] 既定は Winapi=StdCall、
//   Python の ctypes.WinDLL も StdCall のため、x86 では呼び出し側で Cdecl 指定が必須)。
//     C#     : [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
//              [UnmanagedFunctionPointer(CallingConvention.Cdecl)]  // LogCallback 用
//     Python : ctypes.CDLL("IpatHelper.dll")   (WinDLL ではない)
// ---------------------------------------------------------------------------
#ifndef IPAT_API
#define IPAT_API __cdecl
#endif

// ---------------------------------------------------------------------------
// スレッドと再入について
//   通信を伴う公開関数は DLL 内部の単一ロックで直列化される。複数スレッドから同時に
//   呼び出しても壊れないが、先行する呼び出しが完了するまでブロックする
//   (投票・入出金は通信と残高反映待ちを含むため数分に及ぶことがある)。
//   GetBetInstance / GetBetInstanceWin5 は通信もグローバル状態の参照も行わない
//   純粋な入力変換のためロックを取らず、通信中でも並行して呼び出せる。
//   例外は本 DLL の境界を越えない。内部で発生した例外は捕捉され UNSUCCESS になる。
// ---------------------------------------------------------------------------

#ifdef	__cplusplus
extern	"C" {
#endif

	/// <summary>
	/// ログレベル
	/// </summary>
	enum LOG_LEVEL {
		LOG_LEVEL_TRACE = 0,	///< 詳細トレース
		LOG_LEVEL_INFO,			///< 情報 (既定の DEBUG_PRINTF はこのレベル)
		LOG_LEVEL_WARN,			///< 警告
		LOG_LEVEL_ERROR			///< エラー
	};

	/// <summary>
	/// ログコールバック型。DLL 内部のログを受け取るために利用者が実装する。
	/// </summary>
	/// <param name="nLevel">ログレベル (LOG_LEVEL)</param>
	/// <param name="pszMessage">
	/// ログ本文 (null 終端、UTF-8)。本 DLL は /utf-8 でコンパイルされるため、
	/// ソース中の日本語メッセージは UTF-8 で渡されます。
	/// C# では Encoding.UTF8 でデコードしてください (応答データ本文の各 API も UTF-8)。
	/// </param>
	typedef void (IPAT_API *LogCallback)(int nLevel, const char* pszMessage);

	/// <summary>
	/// <para>ログコールバックを登録します。Release ビルドでもログを取得できます。</para>
	/// <para>callback に nullptr を渡すと解除します。nMinLevel 未満のログは通知されません。</para>
	/// <para>コールバック未登録時 (Release) はログ生成コスト自体が発生しません。</para>
	/// <para>実装上の注意:</para>
	/// <para>・コールバックは DLL 内部ロックを保持したまま呼ばれます。
	/// コールバックから本 DLL の API を呼び返さないでください (デッドロックします)。</para>
	/// <para>・Login 中は中央・地方の 2 スレッドから同時に呼ばれます。
	/// スレッドセーフに実装してください。</para>
	/// <para>・解除 (nullptr) の直後も、実行中の呼び出しが短時間残る可能性があります。
	/// コールバック(C# ではデリゲート)の寿命は Logout 完了後まで保持してください。</para>
	/// </summary>
	/// <param name="callback">ログコールバック (nullptr で解除)</param>
	/// <param name="nMinLevel">通知する最小レベル (LOG_LEVEL)</param>
	void IPAT_API SetLogCallback(
		LogCallback callback,
		int         nMinLevel
	);

	/// <summary>
	/// 曜日
	/// </summary>
	enum class WEEK_DAY {

		/// <summary>
		/// 日曜日
		/// </summary>
		SUNDAY = 1,

		/// <summary>
		/// 月曜日
		/// </summary>
		MONDAY,

		/// <summary>
		/// 火曜日
		/// </summary>
		TUESDAY,

		/// <summary>
		/// 水曜日
		/// </summary>
		WEDNESDAY,

		/// <summary>
		/// 木曜日
		/// </summary>
		THURSDAY,

		/// <summary>
		/// 金曜日
		/// </summary>
		FRIDAY,

		/// <summary>
		/// 土曜日
		/// </summary>
		SATURDAY
	};

	/// <summary>
	/// 確定フラグ
	/// </summary>
	enum class DECISIONFLAG {

		DEFAULT = 1,
		NORMAL,
		DEADLINE,
		CANCEL,
		FLATMATESCANCEL,
		HIT,
		MISS,
		BACK,
		PARTCANCEL,
		INVALID,
		SALECANCEL
	};

	/// <summary>
	/// 購入フラグ
	/// </summary>
	enum class BET_FLAG {

		/// <summary>
		/// 通常
		/// </summary>
		NORMAL,

		/// <summary>
		/// WIN5
		/// </summary>
		WIN5,

		/// <summary>
		/// 海外
		/// </summary>
		INTERNATIONAL
	};

	/// <summary>
	/// 開催場
	/// </summary>
	enum class KAISAI {

		/// <summary>
		/// 札幌
		/// </summary>
		SAPPORO,

		/// <summary>
		/// 函館
		/// </summary>
		HAKODATE,

		/// <summary>
		/// 福島
		/// </summary>
		FUKUSHIMA,

		/// <summary>
		/// 新潟
		/// </summary>
		NIIGATA,

		/// <summary>
		/// 東京
		/// </summary>
		TOKYO,

		/// <summary>
		/// 中山
		/// </summary>
		NAKAYAMA,

		/// <summary>
		/// 中京
		/// </summary>
		CHUKYO,

		/// <summary>
		/// 京都
		/// </summary>
		KYOTO,

		/// <summary>
		/// 阪神
		/// </summary>
		HANSHIN,

		/// <summary>
		/// 小倉
		/// </summary>
		KOKURA,

		/// <summary>
		/// 園田
		/// </summary>
		SONODA,

		/// <summary>
		/// 姫路
		/// </summary>
		HIMEJI,

		/// <summary>
		/// 名古屋
		/// </summary>
		NAGOYA,

		/// <summary>
		/// 門別
		/// </summary>
		MONBETSU,

		/// <summary>
		/// 盛岡
		/// </summary>
		MORIOKA,

		/// <summary>
		/// 水沢
		/// </summary>
		MIZUSAWA,

		/// <summary>
		/// 浦和
		/// </summary>
		URAWA,

		/// <summary>
		/// 船橋
		/// </summary>
		FUNABASHI,

		/// <summary>
		/// 大井
		/// </summary>
		OI,

		/// <summary>
		/// 川崎
		/// </summary>
		KAWASAKI,

		/// <summary>
		/// 笠松
		/// </summary>
		KASAMATSU,

		/// <summary>
		/// 金沢
		/// </summary>
		KANAZAWA,

		/// <summary>
		/// 高知
		/// </summary>
		KOCHI,

		/// <summary>
		/// 佐賀
		/// </summary>
		SAGA,

		/// <summary>
		/// ロンシャン
		/// </summary>
		LONGCHAMP,

		/// <summary>
		/// シャティン
		/// </summary>
		SHATIN,

		/// <summary>
		/// サンタアニタ
		/// </summary>
		SANTAANITA,

		/// <summary>
		/// ドーヴィル
		/// </summary>
		DEAUVILLE,

		/// <summary>
		/// チャーチルダウンズ
		/// </summary>
		CHURCHILLDOWNS,

		/// <summary>
		/// キングアブドゥルアジーズ
		/// </summary>
		ABDULAZIZ,

		/// <summary>
		/// アスコット
		/// </summary>
		ASCOT
	};

	/// <summary>
	/// <para>方式</para>
	/// <para>0〜8 は IPAT の送信方式コードと一致します。ながし系は買い目の列(買い目文字列の</para>
	/// <para>ハイフン区切り)の意味が式別により異なります(詳細は README「買い目文字列の書式」)。</para>
	/// <para>マルチ(WHEEL_MULTI_*)は馬単・三連単のみ有効で、GetBetInstance が内部で</para>
	/// <para>基底のながし方式(軸1頭=WHEEL_1ST, 軸2頭=WHEEL_1ST_2ND)＋マルチフラグへ変換します。</para>
	/// </summary>
	enum class HOUSHIKI {

		/// <summary>
		/// 通常
		/// </summary>
		NORMAL = 0,

		/// <summary>
		/// フォーメーション
		/// </summary>
		FORMATION = 1,

		/// <summary>
		/// ボックス
		/// </summary>
		BOX = 2,

		/// <summary>
		/// <para>軸1頭ながし(1着流し)。</para>
		/// <para>馬連・ワイド・枠連ながし / 馬単1着ながし / 三連複軸1頭ながし / 三連単1着ながし。</para>
		/// <para>買い目: 「軸-相手」(軸1頭 - 相手)。</para>
		/// </summary>
		WHEEL_1ST = 3,

		/// <summary>
		/// <para>2着ながし。馬単2着ながし / 三連単2着ながし。買い目: 「軸-相手」。</para>
		/// </summary>
		WHEEL_2ND = 4,

		/// <summary>
		/// <para>3着ながし。三連単3着ながし。買い目: 「軸-相手」。</para>
		/// </summary>
		WHEEL_3RD = 5,

		/// <summary>
		/// <para>軸2頭ながし。三連複軸2頭ながし / 三連単1・2着ながし。</para>
		/// <para>三連複: 買い目「軸,軸-相手」。三連単: 買い目「1着軸-2着軸-相手」(着順)。</para>
		/// </summary>
		WHEEL_1ST_2ND = 6,

		/// <summary>
		/// <para>三連単1・3着ながし。買い目: 「1着軸-相手-3着軸」(着順)。</para>
		/// </summary>
		WHEEL_1ST_3RD = 7,

		/// <summary>
		/// <para>三連単2・3着ながし。買い目: 「相手-2着軸-3着軸」(着順)。</para>
		/// </summary>
		WHEEL_2ND_3RD = 8,

		/// <summary>
		/// <para>軸1頭ながしマルチ(馬単・三連単のみ)。</para>
		/// <para>軸と相手の全着順を購入します。買い目: 「軸-相手」。</para>
		/// </summary>
		WHEEL_MULTI_AXIS1 = 9,

		/// <summary>
		/// <para>軸2頭ながしマルチ(三連単のみ)。</para>
		/// <para>軸2頭と相手の全着順を購入します。買い目: 「軸-軸-相手」(各列に軸を1頭ずつ、末尾に相手)。</para>
		/// </summary>
		WHEEL_MULTI_AXIS2 = 10
	};

	/// <summary>
	/// 式別
	/// </summary>
	enum class SHIKIBETSU {

		/// <summary>
		/// 単勝
		/// </summary>
		WIN = 1,

		/// <summary>
		/// 複勝
		/// </summary>
		PLACE,

		/// <summary>
		/// 枠連
		/// </summary>
		BRACKETQUINELLA,

		/// <summary>
		/// 馬連
		/// </summary>
		QUINELLA,

		/// <summary>
		/// ワイド
		/// </summary>
		QUINELLAPLACE,

		/// <summary>
		/// 馬単
		/// </summary>
		EXACTA,

		/// <summary>
		/// 三連複
		/// </summary>
		TRIO,

		/// <summary>
		/// 三連単
		/// </summary>
		TRIFECTA
	};

	/// <summary>
	/// 購入日種類
	/// </summary>
	enum class DAY_TYPE {

		/// <summary>
		/// 当日
		/// </summary>
		TODAY = 1,

		/// <summary>
		/// 前日
		/// </summary>
		BEFORE
	};

	/// <summary>
	/// 戻り値
	/// </summary>
	enum class RETURN_VALUE {

		/// <summary>
		/// 処理に成功
		/// </summary>
		SUCCESS = 0b00000001,

		/// <summary>
		/// 処理に失敗
		/// </summary>
		UNSUCCESS = 0b00000010,

		/// <summary>
		/// 中央競馬での処理に失敗
		/// </summary>
		FAILED_CHUOU = 0b00000100,

		/// <summary>
		/// 地方競馬での処理に失敗
		/// </summary>
		FAILED_CHIHOU = 0b00001000,

		/// <summary>
		/// 中央競馬での通信に失敗(IPATレスポンスエラー)
		/// </summary>
		FAILED_COMMUNICATE_CHUOU = 0b00010000,

		/// <summary>
		/// 地方競馬での通信に失敗(IPATレスポンスエラー)
		/// </summary>
		FAILED_COMMUNICATE_CHIHOU = 0b00100000
	};

	/// <summary>
	/// 馬券詳細情報
	/// </summary>
	struct ST_TICKET_DATA_DETAIL {

		/// <summary>
		/// 確定フラグ
		/// </summary>
		unsigned char ucDecisionFlag;

		/// <summary>
		/// 購入フラグ
		/// </summary>
		unsigned char ucBetFlag;

		/// <summary>
		/// 開催場
		/// </summary>
		unsigned short usKaisai;

		/// <summary>
		/// レース番号
		/// </summary>
		unsigned char ucRaceNo;

		/// <summary>
		/// 週
		/// </summary>
		unsigned char ucWeek;

		/// <summary>
		/// 方式
		/// </summary>
		unsigned char ucMethod;

		/// <summary>
		/// 式別
		/// </summary>
		unsigned char ucType;

		/// <summary>
		/// 買い目
		/// </summary>
		unsigned int unHorse[UMABAN_TICKET_COLUMN_COUNT];

		/// <summary>
		/// マルチかどうか
		/// </summary>
		unsigned char ucMulti;
	};

	/// <summary>
	/// 馬券基本情報
	/// </summary>
	struct ST_TICKET_DATA {

		/// <summary>
		/// 購入日フラグ
		/// </summary>
		unsigned char ucDayFlag;

		/// <summary>
		/// 受付No
		/// </summary>
		unsigned char ucReceiptNo;

		/// <summary>
		/// 時間(H)
		/// </summary>
		unsigned char ucHour;

		/// <summary>
		/// 時間(M)
		/// </summary>
		unsigned char ucMinute;

		/// <summary>
		/// 金額
		/// </summary>
		unsigned int unKingaku;

		/// <summary>
		/// 払い戻し
		/// </summary>
		unsigned int unPayout;

		/// <summary>
		/// 詳細情報数
		/// </summary>
		unsigned int unDetailCount;

		/// <summary>
		/// 詳細情報
		/// </summary>
		ST_TICKET_DATA_DETAIL* pobjDetail;
	};

	/// <summary>
	/// 馬券購入履歴
	/// </summary>
	struct ST_PURCHASE_DATA {

		/// <summary>
		/// 残購入可能数
		/// </summary>
		unsigned short usRemainBetCount;

		/// <summary>
		/// 残高
		/// </summary>
		unsigned int unBalance;

		/// <summary>
		/// 一日購入金額
		/// </summary>
		unsigned int unDayPurchase;

		/// <summary>
		/// 一日払戻金額
		/// </summary>
		unsigned int unDayPayout;

		/// <summary>
		/// 合計購入金額
		/// </summary>
		unsigned int unTotalPurchase;

		/// <summary>
		/// 合計払戻金額
		/// </summary>
		unsigned int unTotalPayout;

		/// <summary>
		/// 馬券情報数
		/// </summary>
		unsigned int unTicketCount;

		/// <summary>
		/// 馬券購入履歴
		/// </summary>
		ST_TICKET_DATA* pobjTicketData;
	};

	/// <summary>
	/// 馬券購入情報
	/// </summary>
	struct ST_BET_DATA {

		/// <summary>
		/// 開催場
		/// </summary>
		unsigned short usPlace;

		/// <summary>
		/// レース番号
		/// </summary>
		unsigned char ucRaceNo;

		/// <summary>
		/// 曜日
		/// </summary>
		unsigned char ucYoubi;

		/// <summary>
		/// 方式
		/// </summary>
		unsigned char ucHoushiki;

		/// <summary>
		/// 式別
		/// </summary>
		unsigned char ucShikibetsu;

		/// <summary>
		/// 金額
		/// </summary>
		unsigned int unKingaku;

		/// <summary>
		/// 馬番
		/// </summary>
		unsigned int unUmaban[UMABAN_COLUMN_COUNT];

		/// <summary>
		/// 合計購入額
		/// </summary>
		unsigned int unTotalAmount;

		/// <summary>
		/// <para>マルチかどうか(0:通常 1:マルチ)。</para>
		/// <para>馬単・三連単のながし方式でのみ有効。GetBetInstance が</para>
		/// <para>HOUSHIKI::WHEEL_MULTI_* 指定時に 1 を設定します。</para>
		/// </summary>
		unsigned char ucMulti;
	};

	/// <summary>
	/// 馬券購入情報(WIN5)
	/// </summary>
	struct ST_BET_DATA_WIN5 {

		/// <summary>
		/// 購入金額
		/// </summary>
		unsigned int unKingaku;

		/// <summary>
		/// 曜日
		/// </summary>
		unsigned char ucYoubi;

		/// <summary>
		/// 馬番
		/// </summary>
		unsigned int unUmaban[WIN5_RACE_COUNT];
	};

	/// <summary>
	/// オッズ明細(1点)
	/// </summary>
	struct ST_ODDS_DETAIL {

		/// <summary>
		/// 式別(SHIKIBETSU)
		/// </summary>
		unsigned char ucType;

		/// <summary>
		/// 馬番/枠番1
		/// </summary>
		unsigned char ucHorse1;

		/// <summary>
		/// 馬番/枠番2(単勝・複勝は0)
		/// </summary>
		unsigned char ucHorse2;

		/// <summary>
		/// 馬番3(三連複・三連単のみ、それ以外は0)
		/// </summary>
		unsigned char ucHorse3;

		/// <summary>
		/// 状態(0:通常 1:発売中止 2:オッズ未取得)
		/// </summary>
		unsigned char ucStatus;

		/// <summary>
		/// オッズ×10(複勝・ワイドは下限)。例:12.3倍→123
		/// </summary>
		unsigned int unOdds;

		/// <summary>
		/// 複勝・ワイドの上限オッズ×10(それ以外は0)
		/// </summary>
		unsigned int unOddsHigh;
	};

	/// <summary>
	/// オッズ情報
	/// </summary>
	struct ST_ODDS_DATA {

		/// <summary>
		/// 開催場(入力値)
		/// </summary>
		unsigned short usPlace;

		/// <summary>
		/// レース番号
		/// </summary>
		unsigned char ucRaceNo;

		/// <summary>
		/// オッズ更新時刻 "HH:MM"
		/// </summary>
		char szOddsTime[8];

		/// <summary>
		/// 明細数
		/// </summary>
		unsigned int unDetailCount;

		/// <summary>
		/// オッズ明細配列
		/// </summary>
		ST_ODDS_DETAIL* pobjDetail;
	};

	/// <summary>
	/// 出走馬明細(出馬表の1頭分)
	/// </summary>
	struct ST_ENTRY_DETAIL {

		/// <summary>
		/// 枠番
		/// </summary>
		unsigned char ucWakuban;

		/// <summary>
		/// 馬番
		/// </summary>
		unsigned char ucUmaban;

		/// <summary>
		/// 馬名(UTF-8)
		/// </summary>
		char szHorseName[64];

		/// <summary>
		/// 性別(UTF-8: 牡/牝/セン等)
		/// </summary>
		char szSex[8];

		/// <summary>
		/// 年齢
		/// </summary>
		unsigned char ucAge;

		/// <summary>
		/// 馬体重状態(0:通常 1:未発表 2:出走取消 3:計量不能)
		/// </summary>
		unsigned char ucWeightStatus;

		/// <summary>
		/// 馬体重(kg)。ucWeightStatusが0以外の場合は0
		/// </summary>
		unsigned short usWeight;

		/// <summary>
		/// 馬体重増減符号(0:なし 1:増 2:減 3:増減なし 7:初出走 8:前計不)
		/// </summary>
		unsigned char ucWeightDiffCode;

		/// <summary>
		/// 馬体重増減量(kg)
		/// </summary>
		unsigned short usWeightDiff;

		/// <summary>
		/// 見習騎手コード(0:なし 1:☆1kg減〜5:5kg減相当 9:女性騎手2kg減)
		/// </summary>
		unsigned char ucApprentice;

		/// <summary>
		/// 騎手名(UTF-8)
		/// </summary>
		char szJockeyName[48];

		/// <summary>
		/// 斤量×10。例:57.0kg→570
		/// </summary>
		unsigned short usBurden;

		/// <summary>
		/// 調教師名(UTF-8)
		/// </summary>
		char szTrainerName[48];

		/// <summary>
		/// 単勝人気(0:データなし)
		/// </summary>
		unsigned short usWinPopular;

		/// <summary>
		/// 単勝オッズ状態(0:通常 1:発売中止 2:オッズ未取得)
		/// </summary>
		unsigned char ucWinOddsStatus;

		/// <summary>
		/// 単勝オッズ×10。例:12.3倍→123
		/// </summary>
		unsigned int unWinOdds;

		/// <summary>
		/// 複勝オッズ状態(0:通常 1:発売中止 2:オッズ未取得)
		/// </summary>
		unsigned char ucPlaceOddsStatus;

		/// <summary>
		/// 複勝オッズ下限×10
		/// </summary>
		unsigned int unPlaceOddsLow;

		/// <summary>
		/// 複勝オッズ上限×10
		/// </summary>
		unsigned int unPlaceOddsHigh;
	};

	/// <summary>
	/// 出馬表情報
	/// </summary>
	struct ST_RACECARD_DATA {

		/// <summary>
		/// 開催場(入力値)
		/// </summary>
		unsigned short usPlace;

		/// <summary>
		/// レース番号(入力値)
		/// </summary>
		unsigned char ucRaceNo;

		/// <summary>
		/// オッズ更新時刻 "HH:MM"
		/// </summary>
		char szOddsTime[8];

		/// <summary>
		/// 出走馬数
		/// </summary>
		unsigned int unEntryCount;

		/// <summary>
		/// 出走馬明細配列
		/// </summary>
		ST_ENTRY_DETAIL* pobjEntry;

		/// <summary>
		/// レース名(UTF-8)。開催メニュー(ri)から取得。取得できない場合は空文字。
		/// </summary>
		char szRaceName[128];
	};

	/// <summary>
	/// お知らせ一覧の1件分(sai配列の1要素)
	/// </summary>
	struct ST_NOTICE_ITEM {

		/// <summary>
		/// タイトル(UTF-8)
		/// </summary>
		char szTitle[512];

		/// <summary>
		/// 日付テキスト(UTF-8)
		/// </summary>
		char szDate[64];

		/// <summary>
		/// リンクURL
		/// </summary>
		char szUrl[1024];

		/// <summary>
		/// アイコンファイル名
		/// </summary>
		char szIcon[128];

		/// <summary>
		/// 日付表示色
		/// </summary>
		char szColor[32];
	};

	/// <summary>
	/// お知らせ情報
	/// </summary>
	struct ST_NOTICE_DATA {

		/// <summary>
		/// 強制表示お知らせ本文(foinf, UTF-8)。無い場合は空文字。
		/// </summary>
		char szMessage[2048];

		/// <summary>
		/// お知らせ番号(fino)
		/// </summary>
		char szNoticeNo[16];

		/// <summary>
		/// お知らせ種別(fit)
		/// </summary>
		char szNoticeType[8];

		/// <summary>
		/// お知らせ一覧(sai)の件数
		/// </summary>
		unsigned int unItemCount;

		/// <summary>
		/// お知らせ一覧配列(unItemCount件)。0件の場合はnullptr。
		/// </summary>
		ST_NOTICE_ITEM* pobjItem;
	};

	/// <summary>
	/// I-PATへログインします。
	/// </summary>
	/// <param name="szINetId">I-NET ID</param>
	/// <param name="szId">ログインID</param>
	/// <param name="szPassword">パスワード</param>
	/// <param name="szPars">P-ARS番号</param>
	/// <returns></returns>
	unsigned int IPAT_API Login(
		const char szINetId[],
		const char szId[],
		const char szPassword[],
		const char szPars[]
	);

	/// <summary>
	/// I-PATからログアウトします。
	/// </summary>
	/// <returns></returns>
	unsigned int IPAT_API Logout(
	);

	/// <summary>
	/// <para>登録口座から入金します。</para>
	/// <para>入金指示の完了後、入金額が残高へ加算されたことを確認できるまで待機し、
	/// 反映を確認できた場合のみ成功を返します。</para>
	/// <para>SetAutoDepositFlagのusConfirmTimeout(既定10000ms)以内に反映されない場合は失敗を返します。</para>
	/// </summary>
	/// <param name="unDepositValue">入金額</param>
	/// <param name="usRetryCount">
	/// <para>リトライ回数。適用されるのは入金実行電文を送信する前の準備段階
	/// (口座セッションの確立・確認画面への遷移)のみです。</para>
	/// <para>入金実行そのものは、応答を受信できなかった場合でもサーバ側で成立している
	/// 可能性があるため再送しません(二重入金の防止)。この場合は残高への反映で成否を判定し、
	/// 反映を確認できなければ失敗を返します。</para>
	/// <para>1未満を指定した場合は1回として扱います。</para>
	/// </param>
	/// <returns></returns>
	unsigned int IPAT_API Deposit(
		const unsigned int unDepositValue,
		const unsigned short usRetryCount = DEFAULT_RETRY_COUNT
	);

	/// <summary>
	/// <para>登録口座へ全額出金します。</para>
	/// <para>出金指示の完了後、残高が0になったことを確認できるまで待機し、
	/// 反映を確認できた場合のみ成功を返します。</para>
	/// <para>SetAutoDepositFlagのusConfirmTimeout(既定10000ms)以内に反映されない場合は失敗を返します。</para>
	/// </summary>
	/// <param name="usRetryCount">
	/// <para>リトライ回数。適用されるのは出金実行電文を送信する前の準備段階
	/// (口座セッションの確立・確認画面への遷移)のみです。</para>
	/// <para>出金実行そのものは、応答を受信できなかった場合でもサーバ側で成立している
	/// 可能性があるため再送しません(二重出金の防止)。この場合は残高が0になったかで成否を
	/// 判定し、確認できなければ失敗を返します。</para>
	/// <para>1未満を指定した場合は1回として扱います。</para>
	/// </param>
	/// <returns></returns>
	unsigned int IPAT_API Withdraw(
		const unsigned short usRetryCount = DEFAULT_RETRY_COUNT
	);

	/// <summary>
	/// <para>馬券購入履歴を取得します。</para>
	/// <para>使用後は必ずReleasePurchaseDataを使用して解放してください。</para>
	/// <para>同じ構造体を使い回す場合、次の取得前に必ずReleasePurchaseDataを呼んでください
	/// (本関数は先頭で構造体をゼロ初期化するため、未解放のまま再取得するとリークします)。</para>
	/// </summary>
	/// <param name="pobjStatus">
	/// <para>馬券購入履歴</para>
	/// <para>ST_PURCHASE_DATAは例えば以下のような構造となっています。</para>
	/// <para>ST_PURCHASE_DATA</para>
	/// <para>├─ST_TICKET_DATA[1]</para>
	/// <para>│  ├─ST_TICKET_DATA_DETAIL[1]</para>
	/// <para>│  └─ST_TICKET_DATA_DETAIL[2]</para>
	/// <para>├─ST_TICKET_DATA[2]</para>
	/// <para>│  ├─ST_TICKET_DATA_DETAIL[1]</para>
	/// <para>│  ├─ST_TICKET_DATA_DETAIL[2]</para>
	/// <para>│  └─ST_TICKET_DATA_DETAIL[3]</para>
	/// <para>├─ST_TICKET_DATA[3]</para>
	/// <para>│  └─ST_TICKET_DATA_DETAIL[1]</para>
	/// <para>└─ST_TICKET_DATA[4]</para>
	/// <para>    ├─ST_TICKET_DATA_DETAIL[1]</para>
	/// <para>    ├─ST_TICKET_DATA_DETAIL[2]</para>
	/// <para>    ├─ST_TICKET_DATA_DETAIL[3]</para>
	/// <para>    ├─ST_TICKET_DATA_DETAIL[4]</para>
	/// <para>    └─ST_TICKET_DATA_DETAIL[5]</para>
	/// </param>
	/// <returns></returns>
	unsigned int IPAT_API GetPurchaseData(
		ST_PURCHASE_DATA* pobjStatus
	);

	/// <summary>
	/// <para>馬券購入履歴を解放します。</para>
	/// <para>GetPurchaseDataの可否に依らず必ず実行してください。</para>
	/// </summary>
	/// <param name="objStatus">馬券購入履歴</param>
	void IPAT_API ReleasePurchaseData(
		ST_PURCHASE_DATA* pobjStatus
	);

	/// <summary>
	/// 馬券購入情報を取得します。
	/// </summary>
	/// <param name="usPlace">開催場</param>
	/// <param name="ucRaceNo">レース番号</param>
	/// <param name="usYear">開催年</param>
	/// <param name="ucMonth">開催月</param>
	/// <param name="ucDay">開催日</param>
	/// <param name="ucHoushiki">方式</param>
	/// <param name="ucShikibetsu">式別</param>
	/// <param name="nKingaku">金額(100円以上MAX_KINGAKU_YEN以下、100円単位)</param>
	/// <param name="szKaime">
	/// <para>買い目。馬番は1〜18(海外は1〜24)の範囲で指定してください。</para>
	/// <para>範囲外の馬番が含まれる場合は失敗します(黙って無視はしません)。</para>
	/// </param>
	/// <param name="pobjBetData">馬券購入情報</param>
	/// <returns></returns>
	unsigned int IPAT_API GetBetInstance(
		const unsigned short usPlace,
		const unsigned char ucRaceNo,
		const unsigned short usYear,
		const unsigned char ucMonth,
		const unsigned char ucDay,
		const unsigned char ucHoushiki,
		const unsigned char ucShikibetsu,
		const unsigned int nKingaku,
		const char szKaime[],
		ST_BET_DATA* pobjBetData
	);

	/// <summary>
	/// <para>馬券を購入します。</para>
	/// <para>GetBetInstanceで取得した構造体の配列を指定することで一括で購入することが可能です。</para>
	/// <para>配列の要素ごとに購入を行いますが、間隔が短い場合購入に失敗する可能性があります。</para>
	/// <para>ネットワーク環境によって間隔は異なりますが、usWaitMillisecondsに任意の数値を指定することで調整が可能です。</para>
	/// </summary>
	/// <param name="pobjBetData">馬券購入情報(配列)</param>
	/// <param name="usBetCount">配列数</param>
	/// <param name="usWaitMilliseconds">馬券購入間隔(ms)</param>
	/// <returns></returns>
	unsigned int IPAT_API Bet(
		const ST_BET_DATA pobjBetData[],
		const unsigned short usBetCount,
		const unsigned short usWaitMilliseconds = DEFAULT_BET_TIMEOUT
	);

	/// <summary>
	/// 馬券購入情報(WIN5)を取得します。
	/// </summary>
	/// <param name="unKingaku">購入金額(100円以上MAX_KINGAKU_YEN以下、100円単位)</param>
	/// <param name="usYear">開催年</param>
	/// <param name="ucMonth">開催月</param>
	/// <param name="ucDay">開催日</param>
	/// <param name="szKaime">買い目(5レース分。馬番は1〜18)</param>
	/// <param name="pobjBetData">馬券購入情報(WIN5)</param>
	/// <returns></returns>
	unsigned int IPAT_API GetBetInstanceWin5(
		const unsigned int unKingaku,
		const unsigned short usYear,
		const unsigned char ucMonth,
		const unsigned char ucDay,
		const char szKaime[],
		ST_BET_DATA_WIN5* pobjBetData
	);

	/// <summary>
	/// <para>馬券(WIN5)を購入します。</para>
	/// <para>GetBetInstanceWin5で取得した構造体を指定することで一括で購入することが可能です。</para>
	/// <para>組み合わせごとに購入を行いますが、間隔が短い場合購入に失敗する可能性があります。</para>
	/// <para>ネットワーク環境によって間隔は異なりますが、usWaitMillisecondsに任意の数値を指定することで調整が可能です。</para>
	/// </summary>
	/// <param name="objBetData">馬券購入情報(WIN5)</param>
	/// <param name="usWaitMilliseconds">馬券購入間隔</param>
	/// <returns></returns>
	unsigned int IPAT_API BetWin5(
		const ST_BET_DATA_WIN5 objBetData,
		const unsigned short usWaitMilliseconds = DEFAULT_BET_TIMEOUT
	);

	/// <summary>
	/// <para>自動入金設定を行います。</para>
	/// <para>購入時に残高が不足している場合、自動で入金してから購入に移ります。</para>
	/// <para>usConfirmTimeoutは残高反映待機のタイムアウト(ms)で、
	/// Deposit/Withdrawの反映待機にも使用されます。</para>
	/// </summary>
	/// <param name="bEnable">有効にするかどうか</param>
	/// <param name="unDepositValue">
	/// <para>自動入金額(100円以上、100円単位)。bEnableがfalseの場合は検証しません。</para>
	/// </param>
	/// <param name="usConfirmTimeout">残高反映の確認タイムアウト(ms)</param>
	/// <returns></returns>
	/// <remarks>
	/// bEnableはC++のbool(1バイト)です。C#では[MarshalAs(UnmanagedType.I1)]を指定してください
	/// (C#のboolの既定マーシャリングは4バイトのBOOLのため)。
	/// </remarks>
	unsigned int IPAT_API SetAutoDepositFlag(
		const bool bEnable,
		const unsigned int unDepositValue = DEPOSIT_DEFAULT_VALUE,
		const unsigned short usConfirmTimeout = DEFAULT_CONFIRM_TIMEOUT
	);

	/// <summary>
	/// <para>指定レース・式別のオッズを取得します。</para>
	/// <para>単勝・複勝は基本オッズ、枠連〜三連単は全通りのオッズ表を取得します。</para>
	/// <para>中央競馬・地方競馬・海外競馬に対応しています。</para>
	/// <para>海外開催は中央競馬へのログインが必要です。また海外競馬に枠は無いため、
	/// 枠連を指定するとUNSUCCESSを返します。</para>
	/// <para>使用後は必ずReleaseOddsDataで解放してください。</para>
	/// </summary>
	/// <param name="usPlace">開催場(KAISAI)</param>
	/// <param name="ucRaceNo">レース番号(1〜12)</param>
	/// <param name="ucShikibetsu">式別(SHIKIBETSU)</param>
	/// <param name="pobjOdds">オッズ情報</param>
	/// <returns></returns>
	unsigned int IPAT_API GetOdds(
		const unsigned short usPlace,
		const unsigned char ucRaceNo,
		const unsigned char ucShikibetsu,
		ST_ODDS_DATA* pobjOdds
	);

	/// <summary>
	/// <para>オッズ情報を解放します。</para>
	/// <para>GetOddsの可否に依らず必ず実行してください。</para>
	/// </summary>
	/// <param name="pobjOdds">オッズ情報</param>
	void IPAT_API ReleaseOddsData(
		ST_ODDS_DATA* pobjOdds
	);

	/// <summary>
	/// <para>指定レースの出馬表を取得します。</para>
	/// <para>中央競馬・地方競馬・海外競馬に対応しています。</para>
	/// <para>各出走馬の枠番・馬番・馬名・性齢・馬体重・騎手・斤量・調教師・
	/// 単勝人気・単勝/複勝オッズを取得します。文字列はUTF-8で格納されます。</para>
	/// <para>海外開催はI-PATが返す項目が異なり、取得できるのは
	/// 馬番・馬名・単勝人気・単勝/複勝オッズのみです。枠番・性齢・馬体重・騎手・斤量・
	/// 調教師・レース名は0または空文字になります。また海外開催は中央競馬への
	/// ログインが必要です。</para>
	/// <para>使用後は必ずReleaseRaceCardDataで解放してください。</para>
	/// </summary>
	/// <param name="usPlace">開催場(KAISAI)</param>
	/// <param name="ucRaceNo">レース番号(1〜12)</param>
	/// <param name="pobjRaceCard">出馬表情報</param>
	/// <returns></returns>
	unsigned int IPAT_API GetRaceCard(
		const unsigned short usPlace,
		const unsigned char ucRaceNo,
		ST_RACECARD_DATA* pobjRaceCard
	);

	/// <summary>
	/// <para>出馬表情報を解放します。</para>
	/// <para>GetRaceCardの可否に依らず必ず実行してください。</para>
	/// </summary>
	/// <param name="pobjRaceCard">出馬表情報</param>
	void IPAT_API ReleaseRaceCardData(
		ST_RACECARD_DATA* pobjRaceCard
	);

	/// <summary>
	/// <para>現在有効なお知らせを取得します。</para>
	/// <para>ログイン済みのセッションが必要です(中央優先、失敗時は地方へフォールバック)。</para>
	/// <para>強制表示お知らせ本文(szMessage)と、お知らせ一覧(pobjItem/unItemCount)を返します。</para>
	/// <para>お知らせが無い場合はszMessageが空文字・unItemCountが0で成功を返します。</para>
	/// <para>使用後は必ずReleaseNoticeDataで解放してください。</para>
	/// </summary>
	/// <param name="pobjNotice">お知らせ情報</param>
	/// <returns></returns>
	unsigned int IPAT_API GetNotice(
		ST_NOTICE_DATA* pobjNotice
	);

	/// <summary>
	/// <para>お知らせ情報を解放します。</para>
	/// <para>GetNoticeの可否に依らず必ず実行してください。</para>
	/// </summary>
	/// <param name="pobjNotice">お知らせ情報</param>
	void IPAT_API ReleaseNoticeData(
		ST_NOTICE_DATA* pobjNotice
	);

#ifdef __cplusplus
}

// operator| / operator|= を extern "C" ブロック外で定義 (ADL のため)
inline unsigned int operator|(unsigned int l, RETURN_VALUE r) noexcept
{
    return l | static_cast<unsigned int>(r);
}
inline unsigned int& operator|=(unsigned int& l, RETURN_VALUE r) noexcept
{
    l |= static_cast<unsigned int>(r);
    return l;
}
#endif

#endif
