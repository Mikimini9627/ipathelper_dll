#ifndef _IPAT_HELPER_H
#define _IPAT_HELPER_H

#define DEPOSIT_DEFAULT_VALUE	1000	// 自動入金のデフォルト値(ms)
#define DEFAULT_CONFIRM_TIMEOUT	10000	// 自動入金時のデフォルトタイムアウト(ms)
#define DEFAULT_BET_TIMEOUT		500		// 馬券購入間隔のデフォルト値

#define WIN5_RACE_COUNT				5	// WIN5のレース数
#define UMABAN_COLUMN_COUNT			3	// フォーメーションでの列数
#define UMABAN_TICKET_COLUMN_COUNT	5	// フォーメーションでの列数(WIN5も含める)

#ifdef	__cplusplus
extern	"C" {
#endif

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
		/// WIN%
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
		/// メイダン
		/// </summary>
		MEYDAN,

		/// <summary>
		/// シャティン
		/// </summary>
		SHATIN,

		/// <summary>
		/// ドーヴィル
		/// </summary>
		DEAUVILE,

		/// <summary>
		/// チャーチルダウンズ
		/// </summary>
		CHURCHILLDOWNS
	};

	/// <summary>
	/// 方式
	/// </summary>
	enum class HOUSHIKI {

		/// <summary>
		/// 通常
		/// </summary>
		NORMAL,

		/// <summary>
		/// フォーメーション
		/// </summary>
		FORMATION,

		/// <summary>
		/// ボックス
		/// </summary>
		BOX
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
		/// ワイド
		/// </summary>
		QUINELLAPLACE,

		/// <summary>
		/// 馬連
		/// </summary>
		QUINELLA,

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
		/// 通信に失敗(IPATレスポンスエラー)
		/// </summary>
		FAILED_COMMUNICATE = 0b00010000
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
		/// 曜日
		/// </summary>
		unsigned char ucYoubi;

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
		/// 受領No
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
	/// I-PATへログインします。
	/// </summary>
	/// <param name="szINetId">I-NET ID</param>
	/// <param name="szId">ログインID</param>
	/// <param name="szPassword">パスワード</param>
	/// <param name="szPars">P-ARS番号</param>
	/// <returns></returns>
	unsigned int Login(
		const char szINetId[],
		const char szId[],
		const char szPassword[],
		const char szPars[]
	);

	/// <summary>
	/// I-PATからログアウトします。
	/// </summary>
	/// <returns></returns>
	unsigned int Logout(
	);

	/// <summary>
	/// 登録口座から入金します。
	/// </summary>
	/// <param name="unDepositValue">入金額</param>
	/// <returns></returns>
	unsigned int Deposit(
		const unsigned int unDepositValue
	);

	/// <summary>
	/// 登録口座へ出金します。
	/// </summary>
	/// <returns></returns>
	unsigned int Withdraw(
	);

	/// <summary>
	/// <para>馬券購入履歴を取得します。</para>
	/// <para>使用後は必ずReleasePurchaseDataを使用して解放してください。</para>
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
	unsigned int GetPurchaseData(
		ST_PURCHASE_DATA* pobjStatus
	);

	/// <summary>
	/// <para>馬券購入履歴を解放します。</para>
	/// <para>GetPurchaseDataの可否に依らず必ず実行してください。</para>
	/// </summary>
	/// <param name="objStatus">馬券購入履歴</param>
	void ReleasePurchaseData(
		ST_PURCHASE_DATA objStatus
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
	/// <param name="nKingaku">金額</param>
	/// <param name="szKaime">買い目</param>
	/// <param name="pobjBetData">馬券購入情報</param>
	/// <returns></returns>
	unsigned int GetBetInstance(
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
	/// <para>ネットワーク環境によって間隔は異なりますが、usWaitMilliSecondsに任意の数値を指定することで調整が可能です。</para>
	/// </summary>
	/// <param name="pobjBetData">馬券購入情報(配列)</param>
	/// <param name="usBetCount">配列数</param>
	/// <param name="usWaitMilliSeconds">馬券購入間隔(ms)</param>
	/// <returns></returns>
	unsigned int Bet(
		const ST_BET_DATA pobjBetData[],
		const unsigned short usBetCount,
		const unsigned short usWaitMilliSeconds = DEFAULT_BET_TIMEOUT
	);

	/// <summary>
	/// 馬券購入情報(WIN5)を取得します。
	/// </summary>
	/// <param name="unKingaku">購入金額</param>
	/// <param name="usYear">開催年</param>
	/// <param name="ucMonth">開催月</param>
	/// <param name="ucDay">開催日</param>
	/// <param name="szKaime">買い目</param>
	/// <param name="pobjBetData">馬券購入情報(WIN5)</param>
	/// <returns></returns>
	unsigned int GetBetInstanceWin5(
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
	/// <para>ネットワーク環境によって間隔は異なりますが、usWaitMilliSecondsに任意の数値を指定することで調整が可能です。</para>
	/// </summary>
	/// <param name="objBetData">馬券購入情報(WIN5)</param>
	/// <param name="usWaitMilliSeconds">馬券購入間隔</param>
	/// <returns></returns>
	unsigned int BetWin5(
		const ST_BET_DATA_WIN5 objBetData,
		const unsigned short usWaitMilliSeconds = DEFAULT_BET_TIMEOUT
	);

	/// <summary>
	/// <para>自動入金設定を行います。</para>
	/// <para>入金が完了したかどうかをusConfirmTimeout(ms)後に再度確認します。</para>
	/// <para>購入するのに十分な入金がされている場合のみ購入に移ります。</para>
	/// </summary>
	/// <param name="bEnable">有効にするかどうか</param>
	/// <param name="unDepositValue">自動入金額</param>
	/// <param name="usConfirmTimeout">確認タイムアウト</param>
	/// <returns></returns>
	unsigned int SetAutoDepositFlag(
		const bool bEnable,
		const unsigned int unDepositValue = DEPOSIT_DEFAULT_VALUE,
		const unsigned short usConfirmTimeout = DEFAULT_CONFIRM_TIMEOUT
	);

#ifdef __cplusplus
}
#endif

#endif
