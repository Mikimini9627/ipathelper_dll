using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace IpatHelper_DotNetSampleApl
{
    public class IpatHelper
    {
        #region 構造体
        [StructLayout(LayoutKind.Sequential)]
        public struct ST_TICKET_DATA_DETAIL
        {
            public byte decisionFlag;
            public byte betFlag;
            public ushort kaisai;
            public byte raceNo;
            public byte week;
            public byte method;
            public byte type;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
            public uint[] horseNo;
            public byte multi;
        };

        [StructLayout(LayoutKind.Sequential)]
        private struct ST_TICKET_DATA_INTERNAL
        {
            public byte dayFlag;
            public byte receiptNo;
            public byte hour;
            public byte minute;
            public uint kingaku;
            public uint payout;
            public uint detailCount;
            public IntPtr detailData;
        };

        [StructLayout(LayoutKind.Sequential)]
        private struct ST_PURCHASE_DATA_INTERNAL
        {
            public ushort remainBetCount;
            public uint balance;
            public uint dayPurchase;
            public uint dayHaraimodosi;
            public uint totalPurchase;
            public uint totalHaraimodosi;
            public uint ticketCount;
            public IntPtr ticketData;
        };

        public struct ST_TICKET_DATA
        {
            public byte dayFlag;
            public byte receiptNo;
            public byte hour;
            public byte minute;
            public uint kingaku;
            public uint payout;
            public uint detailCount;
            public ST_TICKET_DATA_DETAIL[] detailData;
        };

        public struct ST_PURCHASE_DATA
        {
            public ushort remainBetCount;
            public uint balance;
            public uint dayPurchase;
            public uint dayHaraimodosi;
            public uint totalPurchase;
            public uint totalHaraimodosi;
            public uint ticketCount;
            public ST_TICKET_DATA[] ticketData;
        };

        [StructLayout(LayoutKind.Sequential)]
        public struct ST_BET_DATA
        {
            public ushort kaisai;
            public byte raceNo;
            public byte youbi;
            public byte houshiki;
            public byte shikibetsu;
            public uint kingaku;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
            public uint[] horseNo;
            public uint totalAmount;
            public byte multi; // マルチかどうか(0:通常 1:マルチ)
        };

        [StructLayout(LayoutKind.Sequential)]
        public struct ST_BET_DATA_WIN5
        {
            public uint kingaku;
            public byte youbi;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
            public uint[] horseNo;
        };

        [StructLayout(LayoutKind.Sequential)]
        public struct ST_ODDS_DETAIL
        {
            public byte type;       // 式別(Shikibetsu)
            public byte horse1;     // 馬番/枠番1
            public byte horse2;     // 馬番/枠番2(単勝・複勝は0)
            public byte horse3;     // 馬番3(三連複・三連単のみ、それ以外0)
            public byte status;     // 0:通常 1:発売中止 2:オッズ未取得
            public uint odds;       // オッズ×10(複勝・ワイドは下限)
            public uint oddsHigh;   // 複勝・ワイドの上限×10(それ以外0)
        };

        [StructLayout(LayoutKind.Sequential)]
        private struct ST_ODDS_DATA_INTERNAL
        {
            public ushort place;
            public byte raceNo;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public byte[] oddsTime;
            public uint detailCount;
            public IntPtr detailData;
        };

        public struct ST_ODDS_DATA
        {
            public ushort place;
            public byte raceNo;
            public string oddsTime;
            public uint detailCount;
            public ST_ODDS_DETAIL[] oddsDetail;
        };

        [StructLayout(LayoutKind.Sequential)]
        private struct ST_ENTRY_DETAIL_INTERNAL
        {
            public byte ucWakuban;
            public byte ucUmaban;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
            public byte[] szHorseName;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public byte[] szSex;
            public byte ucAge;
            public byte ucWeightStatus;
            public ushort usWeight;
            public byte ucWeightDiffCode;
            public ushort usWeightDiff;
            public byte ucApprentice;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 48)]
            public byte[] szJockeyName;
            public ushort usBurden;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 48)]
            public byte[] szTrainerName;
            public ushort usWinPopular;
            public byte ucWinOddsStatus;
            public uint unWinOdds;
            public byte ucPlaceOddsStatus;
            public uint unPlaceOddsLow;
            public uint unPlaceOddsHigh;
        }

        public struct ST_ENTRY_DETAIL
        {
            public byte wakuban;            // 枠番
            public byte umaban;             // 馬番
            public string horseName;        // 馬名
            public string sex;              // 性別
            public byte age;                // 年齢
            public byte weightStatus;       // 0:通常 1:未発表 2:出走取消 3:計量不能
            public ushort weight;           // 馬体重(kg)
            public byte weightDiffCode;     // 増減符号(0:なし 1:増 2:減 3:増減なし 7:初出走 8:前計不)
            public ushort weightDiff;       // 増減量(kg)
            public byte apprentice;         // 見習騎手コード
            public string jockeyName;       // 騎手名
            public ushort burden;           // 斤量×10
            public string trainerName;      // 調教師名
            public ushort winPopular;       // 単勝人気
            public byte winOddsStatus;      // 0:通常 1:発売中止 2:未取得
            public uint winOdds;            // 単勝オッズ×10
            public byte placeOddsStatus;    // 0:通常 1:発売中止 2:未取得
            public uint placeOddsLow;       // 複勝オッズ下限×10
            public uint placeOddsHigh;      // 複勝オッズ上限×10
        };

        [StructLayout(LayoutKind.Sequential)]
        private struct ST_RACECARD_DATA_INTERNAL
        {
            public ushort usPlace;
            public byte ucRaceNo;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public byte[] szOddsTime;
            public uint unEntryCount;
            public IntPtr pobjEntry;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
            public byte[] szRaceName;
            // この構造体はネイティブ側が直接書き込む領域のため、
            // 順序・型が DLL 側の ST_RACECARD_DATA と一致していないとメモリ破壊になる。
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public byte[] szDeadline;
            public byte ucRaceStatus;
        }

        public struct ST_RACECARD_DATA
        {
            public ushort place;
            public byte raceNo;
            public string oddsTime;
            public uint entryCount;
            public ST_ENTRY_DETAIL[] entries;
            public string raceName;
            public string deadline;         // 発売締切時刻 "HH:MM"(取得不可時は空文字)
            public RACE_STATUS raceStatus;  // 発売状態
        };

        // お知らせ一覧の1件
        [StructLayout(LayoutKind.Sequential)]
        private struct ST_NOTICE_ITEM_INTERNAL
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 512)]
            public byte[] szTitle;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
            public byte[] szDate;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
            public byte[] szUrl;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
            public byte[] szIcon;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
            public byte[] szColor;
        }

        public struct ST_NOTICE_ITEM
        {
            public string title;    // タイトル
            public string date;     // 日付テキスト
            public string url;      // リンクURL
            public string icon;     // アイコンファイル名
            public string color;    // 日付表示色
        };

        [StructLayout(LayoutKind.Sequential)]
        private struct ST_NOTICE_DATA_INTERNAL
        {
            // この構造体はネイティブ側が直接書き込む領域のため、
            // 順序・型が DLL 側の ST_NOTICE_DATA と一致していないとメモリ破壊になる。
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2048)]
            public byte[] szMessage;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
            public byte[] szNoticeNo;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public byte[] szNoticeType;
            public uint unItemCount;
            public IntPtr pobjItem;
        }

        public struct ST_NOTICE_DATA
        {
            public string message;          // 強制表示お知らせ本文(無い場合は空文字)
            public string noticeNo;         // お知らせ番号
            public string noticeType;       // お知らせ種別
            public uint itemCount;          // お知らせ一覧の件数
            public ST_NOTICE_ITEM[] items;  // お知らせ一覧
        };
        #endregion

        #region 列挙体
        public enum Kaisai
        {
            SAPPORO,
            HAKODATE,
            FUKUSHIMA,
            NIIGATA,
            TOKYO,
            NAKAYAMA,
            CHUKYO,
            KYOTO,
            HANSHIN,
            KOKURA,
            SONODA,
            HIMEJI,
            NAGOYA,
            MONBETSU,
            MORIOKA,
            MIZUSAWA,
            URAWA,
            FUNABASHI,
            OI,
            KAWASAKI,
            KASAMATSU,
            KANAZAWA,
            KOCHI,
            SAGA,
            LONGCHAMP,
            SHATIN,
            SANTAANITA,
            DEAUVILE,
            CHURCHILLDOWNS,
            ABDULAZIZ,
            ASCOT
        }

        public enum Houshiki
        {
            NORMAL = 0,
            FORMATION = 1,
            BOX = 2,
            WHEEL_1ST = 3,        // 軸1頭ながし(1着流し)/馬連・ワイド・枠連/三連複軸1頭/三連単1着
            WHEEL_2ND = 4,        // 2着ながし(馬単・三連単)
            WHEEL_3RD = 5,        // 3着ながし(三連単)
            WHEEL_1ST_2ND = 6,    // 軸2頭ながし(三連複)/1・2着ながし(三連単)
            WHEEL_1ST_3RD = 7,    // 1・3着ながし(三連単)
            WHEEL_2ND_3RD = 8,    // 2・3着ながし(三連単)
            WHEEL_MULTI_AXIS1 = 9,// 軸1頭ながしマルチ(馬単・三連単)
            WHEEL_MULTI_AXIS2 = 10// 軸2頭ながしマルチ(三連単)
        }

        public enum Shikibetsu
        {
            WIN = 1,
            PLACE,
            BRACKETQUINELLA,
            QUINELLA,
            QUINELLAPLACE,
            EXACTA,
            TRIO,
            TRIFECTA
        }

        public enum DAY_TYPE
        {
            TODAY = 1,
            BEFORE
        }

        /// <summary>
        /// レースの発売状態(ST_RACECARD_DATA.raceStatus)。
        /// UNKNOWN が 0 でないのは、0 が「発売中」でありゼロ初期化と区別する必要があるため。
        /// </summary>
        public enum RACE_STATUS : byte
        {
            ON_SALE = 0,
            CLOSED = 1,
            CANCELED = 2,
            BEFORE_SALE = 3,
            UNKNOWN = 0xFF
        }

        public enum RETURN_VALUE
        {
            SUCCESS = 1,
            UNSUCCESS = 2,
            FAILED_CHUOU = 4,
            FAILED_CHIHOU = 8,
            FAILED_COMMUNICATE_CHUOU = 16,
            FAILED_COMMUNICATE_CHIHOU = 32,
            // サービス時間外(FAILED_CHUOU / FAILED_CHIHOU と併せて立つ)。
            // 投票受付時間外が最も多い原因で、即座に再試行しても必ず失敗する。
            FAILED_OUT_OF_SERVICE = 64,
        }

        public enum WEEK_DAY
        {
            SUNDAY = 1,
            MONDAY,
            TUESDAY,
            WEDNESDAY,
            THURSDAY,
            FRIDAY,
            SATURDAY
        }

        public enum DECISIONFLAG
        {
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
        }

        public enum BET_FLAG
        {
            NORMAL,
            WIN5,
            INTERNATIONAL
        }
        #endregion

        #region ログ
        /// <summary>
        /// ログレベル。SetLogCallback の minLevel に指定する。
        /// </summary>
        public enum LogLevel
        {
            /// <summary>詳細トレース。入出金失敗時の応答本文の抜粋はこのレベルでのみ通知される。</summary>
            Trace = 0,
            /// <summary>情報 (既定)</summary>
            Info = 1,
            /// <summary>警告</summary>
            Warn = 2,
            /// <summary>エラー。失敗した段階・画面ID・タイトルはこのレベルで通知される。</summary>
            Error = 3,
        }

        /// <summary>
        /// DLL 内部のログを受け取るハンドラ。
        /// </summary>
        /// <param name="level">ログレベル</param>
        /// <param name="message">ログ本文 (UTF-8 からデコード済み)</param>
        public delegate void LogHandler(LogLevel level, string message);

        // ネイティブ側へ渡すデリゲートは GC されるとコールバック時にクラッシュするため、
        // 静的フィールドで参照を保持する。
        private static NativeMethods.LogCallback _nativeLogCallback;
        private static LogHandler _logHandler;

        /// <summary>
        /// <para>DLL 内部のログを受け取るハンドラを登録する。null で解除。</para>
        /// <para>入出金はサーバがエラーコードを返さないため、失敗の原因を知るには
        /// このログが唯一の手掛かりになる。失敗した段階・画面ID・タイトルは
        /// <see cref="LogLevel.Error"/> で通知されるが、サーバ側の拒否理由が載る
        /// 応答本文の抜粋は <see cref="LogLevel.Trace"/> を指定したときのみ通知される。</para>
        /// <para>注意: ハンドラは DLL 内部ロックを保持したまま呼ばれるため、
        /// ハンドラ内から本クラスの API を呼び返さないこと (デッドロックする)。
        /// また Login 中は中央・地方の 2 スレッドから同時に呼ばれる。</para>
        /// <para>応答本文の抜粋には口座番号や残高が含まれ得るため、
        /// Trace は調査時のみ指定し、ログの取り扱いに注意すること。</para>
        /// </summary>
        /// <param name="handler">ログハンドラ (null で解除)</param>
        /// <param name="minLevel">通知する最小レベル</param>
        public static void SetLogCallback(LogHandler handler, LogLevel minLevel = LogLevel.Info)
        {
            _logHandler = handler;

            if (handler == null)
            {
                // 解除時は DLL 側が排他ロックを取るため、戻った時点で実行中の呼び出しは無い
                NativeMethods.SetLogCallback(null, (int)minLevel);
                _nativeLogCallback = null;
                return;
            }

            _nativeLogCallback = (level, message) =>
            {
                // message は UTF-8 の null 終端文字列。既定のマーシャリング (ANSI) では
                // 日本語が化けるため IntPtr で受けて明示的にデコードする。
                string text = message == IntPtr.Zero ? string.Empty : PtrToStringUtf8(message);
                try { _logHandler?.Invoke((LogLevel)level, text); }
                catch { /* ハンドラ側の例外をネイティブへ伝播させない */ }
            };
            NativeMethods.SetLogCallback(_nativeLogCallback, (int)minLevel);
        }

        private static string PtrToStringUtf8(IntPtr ptr)
        {
            int len = 0;
            while (Marshal.ReadByte(ptr, len) != 0) len++;
            if (len == 0) return string.Empty;
            byte[] buffer = new byte[len];
            Marshal.Copy(ptr, buffer, 0, len);
            return Encoding.UTF8.GetString(buffer);
        }
        #endregion

        #region 内部クラス
        private class NativeMethods
        {
            // ネイティブ側の呼び出し規約は __cdecl。x86 では C# の既定 (Winapi=StdCall) と
            // 異なるため明示が必須。
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void LogCallback(int nLevel, IntPtr pszMessage);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern void SetLogCallback(LogCallback callback, int nMinLevel);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern uint Login(byte[] arybyINetId, byte[] arybyId, byte[] arybyPassword, byte[] arybyPars);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern uint Logout();

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern uint Deposit(uint unDepositValue, ushort usRetryCount);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern uint Withdraw(ushort usRetryCount);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern uint GetPurchaseData(ref ST_PURCHASE_DATA_INTERNAL objPurchaseData);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern void ReleasePurchaseData(ref ST_PURCHASE_DATA_INTERNAL objPurchaseData);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern uint GetBetInstance(ushort usKaisai,
                                                      byte byRaceNo,
                                                      ushort usYear,
                                                      byte byMonth,
                                                      byte byDay,
                                                      byte byHoushiki,
                                                      byte byShikibetsu,
                                                      uint unKingaku,
                                                      byte[] arybyKaime,
                                                      ref ST_BET_DATA objBetData);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern uint GetBetInstanceWin5(uint unKingaku,
                                                          ushort usYear,
                                                          byte byMonth,
                                                          byte byDay,
                                                          byte[] arybyKaime,
                                                          ref ST_BET_DATA_WIN5 objBetData);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern uint Bet([In, Out] ST_BET_DATA[] lstBetData, ushort usBetCount, ushort usWaitMiliSeconds);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern uint BetWin5(ST_BET_DATA_WIN5 objBetData, ushort usWaitMiliSeconds);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern uint BetWin5Auto(byte ucMode, byte[] arybyAxisUmaban,
                ushort usBetCount, uint unKingaku, ushort usYear, byte ucMonth, byte ucDay);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern uint SetAutoDepositFlag([MarshalAs(UnmanagedType.I1)] bool bEnable, uint unDepositValue, ushort usConfrimTimeout);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern uint GetOdds(ushort usKaisai, byte byRaceNo, byte byShikibetsu, ref ST_ODDS_DATA_INTERNAL objOddsData);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern void ReleaseOddsData(ref ST_ODDS_DATA_INTERNAL objOddsData);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern uint GetRaceCard(ushort usPlace, byte byRaceNo, ref ST_RACECARD_DATA_INTERNAL objRaceCardData);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern void ReleaseRaceCardData(ref ST_RACECARD_DATA_INTERNAL objRaceCardData);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern uint GetNotice(ref ST_NOTICE_DATA_INTERNAL objNoticeData);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern void ReleaseNoticeData(ref ST_NOTICE_DATA_INTERNAL objNoticeData);
        }
        #endregion

        #region 公開関数
        /// <summary>
        /// ログイン処理実行
        /// </summary>
        /// <param name="iNetId"></param>
        /// <param name="id"></param>
        /// <param name="password"></param>
        /// <param name="pars"></param>
        /// <returns></returns>
        public static uint Login(string iNetId, string id, string password, string pars)
        {
            Encoding.RegisterProvider(CodePagesEncodingProvider.Instance);

            return NativeMethods.Login(Encoding.UTF8.GetBytes(iNetId + "\0"),
                                       Encoding.UTF8.GetBytes(id + "\0"),
                                       Encoding.UTF8.GetBytes(password + "\0"),
                                       Encoding.UTF8.GetBytes(pars + "\0"));
        }

        /// <summary>
        /// ログアウト処理実行
        /// </summary>
        /// <returns></returns>
        public static uint Logout()
        {
            return NativeMethods.Logout();
        }

        /// <summary>
        /// 入金処理実行
        /// </summary>
        /// <param name="depositValue"></param>
        /// <returns></returns>
        public static uint Deposit(uint depositValue, ushort retryCount = 10)
        {
            return NativeMethods.Deposit(depositValue, retryCount);
        }

        /// <summary>
        /// 出金処理実行
        /// </summary>
        /// <returns></returns>
        public static uint Withdraw(ushort retryCount = 10)
        {
            return NativeMethods.Withdraw(retryCount);
        }

        /// <summary>
        /// 馬券購入状況取得処理実行
        /// </summary>
        /// <param name="purchaseData"></param>
        /// <returns></returns>
        public static uint GetPurchaseData(out ST_PURCHASE_DATA purchaseData)
        {
            ST_PURCHASE_DATA_INTERNAL tempTicketData = new()
            {
                remainBetCount = 0,
                balance = 0,
                dayPurchase = 0,
                dayHaraimodosi = 0,
                totalPurchase = 0,
                totalHaraimodosi = 0,
                ticketCount = 0,
                ticketData = IntPtr.Zero
            };

            uint returnValue = NativeMethods.GetPurchaseData(ref tempTicketData);
            if ((returnValue & 1) != 1)
            {
                NativeMethods.ReleasePurchaseData(ref tempTicketData);
                purchaseData = new ST_PURCHASE_DATA();
                return returnValue;
            }

            purchaseData = new ST_PURCHASE_DATA()
            {
                remainBetCount = tempTicketData.remainBetCount,
                balance = tempTicketData.balance,
                dayPurchase = tempTicketData.dayPurchase,
                dayHaraimodosi = tempTicketData.dayHaraimodosi,
                totalPurchase = tempTicketData.totalPurchase,
                totalHaraimodosi = tempTicketData.totalHaraimodosi,
                ticketCount = tempTicketData.ticketCount,
                ticketData = new ST_TICKET_DATA[tempTicketData.ticketCount]
            };

            if (tempTicketData.ticketCount <= 0)
            {
                NativeMethods.ReleasePurchaseData(ref tempTicketData);
                return returnValue;
            }

            // 構造体データ格納用バッファを確保する
            byte[] allTicketBytes = new byte[Marshal.SizeOf(typeof(ST_TICKET_DATA_INTERNAL)) * tempTicketData.ticketCount];

            // IntPtrからbyte配列に変換する
            Marshal.Copy(tempTicketData.ticketData, allTicketBytes, 0, allTicketBytes.Length);

            for (int i = 0; i < tempTicketData.ticketCount; i++)
            {
                // 1つの構造体サイズ分のポインタを確保する
                IntPtr tempPtr = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(ST_TICKET_DATA_INTERNAL)));

                // バイト配列から1つの構造体分のデータをコピーする
                Marshal.Copy(allTicketBytes, i * Marshal.SizeOf(typeof(ST_TICKET_DATA_INTERNAL)), tempPtr, Marshal.SizeOf(typeof(ST_TICKET_DATA_INTERNAL)));

                // ポインタを構造体に変換する
                ST_TICKET_DATA_INTERNAL tempTicket = (ST_TICKET_DATA_INTERNAL)Marshal.PtrToStructure(tempPtr, typeof(ST_TICKET_DATA_INTERNAL));

                // 使用したポインタを解放する
                Marshal.FreeHGlobal(tempPtr);

                purchaseData.ticketData[i] = new ST_TICKET_DATA()
                {
                    dayFlag = tempTicket.dayFlag,
                    receiptNo = tempTicket.receiptNo,
                    hour = tempTicket.hour,
                    minute = tempTicket.minute,
                    kingaku = tempTicket.kingaku,
                    payout = tempTicket.payout,
                    detailCount = tempTicket.detailCount,
                    detailData = new ST_TICKET_DATA_DETAIL[tempTicket.detailCount]
                };

                if (tempTicket.detailCount <= 0)
                {
                    NativeMethods.ReleasePurchaseData(ref tempTicketData);
                    return returnValue;
                }

                // 構造体データ格納用バッファを確保する
                byte[] allDetailBytes = new byte[Marshal.SizeOf(typeof(ST_TICKET_DATA_DETAIL)) * tempTicket.detailCount];

                // IntPtrからbyte配列に変換する
                Marshal.Copy(tempTicket.detailData, allDetailBytes, 0, allDetailBytes.Length);

                for (int j = 0; j < tempTicket.detailCount; j++)
                {
                    // 1つの構造体サイズ分のポインタを確保する
                    tempPtr = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(ST_TICKET_DATA_DETAIL)));

                    // バイト配列から1つの構造体分のデータをコピーする
                    Marshal.Copy(allDetailBytes, j * Marshal.SizeOf(typeof(ST_TICKET_DATA_DETAIL)), tempPtr, Marshal.SizeOf(typeof(ST_TICKET_DATA_DETAIL)));

                    // ポインタを構造体に変換する
                    purchaseData.ticketData[i].detailData[j] = (ST_TICKET_DATA_DETAIL)Marshal.PtrToStructure(tempPtr, typeof(ST_TICKET_DATA_DETAIL));

                    // 使用したポインタを解放する
                    Marshal.FreeHGlobal(tempPtr);
                }
            }

            NativeMethods.ReleasePurchaseData(ref tempTicketData);

            return returnValue;
        }

        /// <summary>
        /// 馬券購入用インスタンス取得
        /// </summary>
        /// <param name="place"></param>
        /// <param name="raceNo"></param>
        /// <param name="kaisaibi"></param>
        /// <param name="houshiki"></param>
        /// <param name="shikibetsu"></param>
        /// <param name="kingaku"></param>
        /// <param name="kaime"></param>
        /// <param name="betData"></param>
        /// <returns></returns>
        public static uint GetBetInstance(Kaisai place, byte raceNo, DateTime kaisaibi, Houshiki houshiki,
            Shikibetsu shikibetsu, uint kingaku, string kaime, out ST_BET_DATA betData)
        {
            betData = new ST_BET_DATA()
            {
                kaisai = 0,
                raceNo = 0,
                youbi = 0,
                houshiki = 0,
                shikibetsu = 0,
                kingaku = 0,
                horseNo = new uint[3],
                totalAmount = 0
            };

            return NativeMethods.GetBetInstance((byte)place, raceNo, (ushort)kaisaibi.Year, (byte)kaisaibi.Month, (byte)kaisaibi.Day, (byte)houshiki,
                                                       (byte)shikibetsu, kingaku, Encoding.UTF8.GetBytes(kaime), ref betData);
        }

        /// <summary>
        /// 馬券購入用インスタンス取得(WIN5)
        /// </summary>
        /// <param name="kingaku"></param>
        /// <param name="kaisaibi"></param>
        /// <param name="kaime"></param>
        /// <param name="objBetData"></param>
        /// <returns></returns>
        public static uint GetBetInstanceWin5(uint kingaku, DateTime kaisaibi, string kaime, out ST_BET_DATA_WIN5 objBetData)
        {
            objBetData = new ST_BET_DATA_WIN5()
            {
                youbi = 0,
                kingaku = 0,
                horseNo = new uint[5]
            };

            return NativeMethods.GetBetInstanceWin5(kingaku, (ushort)kaisaibi.Year, (byte)kaisaibi.Month, (byte)kaisaibi.Day, Encoding.UTF8.GetBytes(kaime), ref objBetData);
        }

        /// <summary>
        /// 馬券購入処理実行
        /// </summary>
        /// <param name="betDataList"></param>
        /// <param name="waitMiliSeconds"></param>
        /// <returns></returns>
        public static uint Bet(List<ST_BET_DATA> betDataList, ushort waitMiliSeconds = 1000)
        {
            return NativeMethods.Bet(betDataList.ToArray(), (ushort)betDataList.Count, waitMiliSeconds);
        }

        /// <summary>
        /// 馬券購入処理実行(WIN5)
        /// </summary>
        /// <param name="betData"></param>
        /// <param name="waitMiliSeconds"></param>
        /// <returns></returns>
        public static uint BetWin5(ST_BET_DATA_WIN5 betData, ushort waitMiliSeconds = 1000)
        {
            return NativeMethods.BetWin5(betData, waitMiliSeconds);
        }

        /// <summary>
        /// WIN5 の購入方式 (BetWin5Auto)
        /// </summary>
        public enum Win5AutoMode
        {
            /// <summary>セレクト: 軸馬を指定し、残りはサーバが選ぶ</summary>
            Select = 2,
            /// <summary>ランダム: すべてサーバが選ぶ</summary>
            Random = 3,
        }

        /// <summary>
        /// <para>WIN5 を「セレクト」または「ランダム」で購入する (中央競馬のみ)。</para>
        /// <para>買い目はサーバが生成する。生成された買い目はそのまま購入されるため、
        /// 内容を事前に確認する手段は無い。<b>実際に購入が行われる。</b></para>
        /// </summary>
        /// <param name="mode">購入方式</param>
        /// <param name="axisUmaban">
        /// セレクト時の軸馬番。5 レース分をカンマ区切りで指定する (例 "3,0,7,0,12")。
        /// 0 のレースはサーバが選ぶ。<b>すべて 0 は指定できない</b>。ランダム時は無視される。
        /// </param>
        /// <param name="betCount">生成させる点数 (1〜50)</param>
        /// <param name="kingaku">1 点あたりの購入金額 (円。100 円単位)</param>
        /// <param name="kaisaibi">開催日</param>
        public static uint BetWin5Auto(Win5AutoMode mode, string axisUmaban, uint betCount, uint kingaku, DateTime kaisaibi)
        {
            return NativeMethods.BetWin5Auto(
                (byte)mode,
                axisUmaban == null ? null : Encoding.UTF8.GetBytes(axisUmaban),
                (ushort)betCount, kingaku,
                (ushort)kaisaibi.Year, (byte)kaisaibi.Month, (byte)kaisaibi.Day);
        }

        /// <summary>
        /// 自動入金フラグ設定
        /// </summary>
        /// <param name="enable"></param>
        /// <param name="usDepositValue"></param>
        /// <returns></returns>
        public static uint SetAutoDepositFlag(bool enable, uint depositValue = 1000, ushort confirmTimeout = 10000)
        {
            return NativeMethods.SetAutoDepositFlag(enable, depositValue, confirmTimeout);
        }

        /// <summary>
        /// オッズ取得処理実行(中央競馬・地方競馬・海外競馬に対応)
        /// </summary>
        /// <param name="place">開催場</param>
        /// <param name="raceNo">レース番号</param>
        /// <param name="shikibetsu">式別</param>
        /// <param name="oddsData">取得したオッズ情報</param>
        /// <returns></returns>
        public static uint GetOdds(Kaisai place, byte raceNo, Shikibetsu shikibetsu, out ST_ODDS_DATA oddsData)
        {
            ST_ODDS_DATA_INTERNAL tempOddsData = new()
            {
                place = 0,
                raceNo = 0,
                oddsTime = new byte[8],
                detailCount = 0,
                detailData = IntPtr.Zero
            };

            uint returnValue = NativeMethods.GetOdds((ushort)place, raceNo, (byte)shikibetsu, ref tempOddsData);

            oddsData = new ST_ODDS_DATA()
            {
                place = tempOddsData.place,
                raceNo = tempOddsData.raceNo,
                oddsTime = tempOddsData.oddsTime != null
                    ? Encoding.ASCII.GetString(tempOddsData.oddsTime).TrimEnd('\0')
                    : string.Empty,
                detailCount = tempOddsData.detailCount,
                oddsDetail = Array.Empty<ST_ODDS_DETAIL>()
            };

            // 取得失敗、または明細が無い場合はここで解放して戻る
            if ((returnValue & 1) != 1 || tempOddsData.detailCount <= 0 || tempOddsData.detailData == IntPtr.Zero)
            {
                NativeMethods.ReleaseOddsData(ref tempOddsData);
                return returnValue;
            }

            // ネイティブ側で確保された明細配列をマネージド配列へ複製する
            oddsData.oddsDetail = new ST_ODDS_DETAIL[tempOddsData.detailCount];
            int detailSize = Marshal.SizeOf(typeof(ST_ODDS_DETAIL));
            for (int i = 0; i < tempOddsData.detailCount; i++)
            {
                IntPtr elementPtr = IntPtr.Add(tempOddsData.detailData, i * detailSize);
                oddsData.oddsDetail[i] = Marshal.PtrToStructure<ST_ODDS_DETAIL>(elementPtr);
            }

            // データの複製が終わったら、取得と同時にネイティブ側のメモリを解放する
            NativeMethods.ReleaseOddsData(ref tempOddsData);

            return returnValue;
        }

        /// <summary>
        /// 出馬表取得処理実行(中央競馬・地方競馬・海外競馬に対応)
        /// </summary>
        /// <param name="place">開催場</param>
        /// <param name="raceNo">レース番号</param>
        /// <param name="raceCard">取得した出馬表情報</param>
        /// <returns></returns>
        public static uint GetRaceCard(Kaisai place, byte raceNo, out ST_RACECARD_DATA raceCard)
        {
            ST_RACECARD_DATA_INTERNAL tempRaceCardData = new()
            {
                usPlace = 0,
                ucRaceNo = 0,
                szOddsTime = new byte[8],
                unEntryCount = 0,
                pobjEntry = IntPtr.Zero,
                szRaceName = new byte[128],
                szDeadline = new byte[8],
                ucRaceStatus = (byte)RACE_STATUS.UNKNOWN
            };

            uint returnValue = NativeMethods.GetRaceCard((ushort)place, raceNo, ref tempRaceCardData);

            raceCard = new ST_RACECARD_DATA()
            {
                place = tempRaceCardData.usPlace,
                raceNo = tempRaceCardData.ucRaceNo,
                oddsTime = DecodeUtf8(tempRaceCardData.szOddsTime),
                entryCount = tempRaceCardData.unEntryCount,
                entries = Array.Empty<ST_ENTRY_DETAIL>(),
                raceName = DecodeUtf8(tempRaceCardData.szRaceName),
                deadline = DecodeUtf8(tempRaceCardData.szDeadline),
                raceStatus = (RACE_STATUS)tempRaceCardData.ucRaceStatus
            };

            // 取得失敗、または明細が無い場合はここで解放して戻る
            if ((returnValue & 1) != 1 || tempRaceCardData.unEntryCount <= 0 || tempRaceCardData.pobjEntry == IntPtr.Zero)
            {
                NativeMethods.ReleaseRaceCardData(ref tempRaceCardData);
                return returnValue;
            }

            // ネイティブ側で確保された明細配列をマネージド配列へ複製する
            raceCard.entries = new ST_ENTRY_DETAIL[tempRaceCardData.unEntryCount];
            int entrySize = Marshal.SizeOf(typeof(ST_ENTRY_DETAIL_INTERNAL));
            for (int i = 0; i < tempRaceCardData.unEntryCount; i++)
            {
                IntPtr elementPtr = IntPtr.Add(tempRaceCardData.pobjEntry, i * entrySize);
                ST_ENTRY_DETAIL_INTERNAL e = Marshal.PtrToStructure<ST_ENTRY_DETAIL_INTERNAL>(elementPtr);

                raceCard.entries[i] = new ST_ENTRY_DETAIL()
                {
                    wakuban = e.ucWakuban,
                    umaban = e.ucUmaban,
                    horseName = DecodeUtf8(e.szHorseName),
                    sex = DecodeUtf8(e.szSex),
                    age = e.ucAge,
                    weightStatus = e.ucWeightStatus,
                    weight = e.usWeight,
                    weightDiffCode = e.ucWeightDiffCode,
                    weightDiff = e.usWeightDiff,
                    apprentice = e.ucApprentice,
                    jockeyName = DecodeUtf8(e.szJockeyName),
                    burden = e.usBurden,
                    trainerName = DecodeUtf8(e.szTrainerName),
                    winPopular = e.usWinPopular,
                    winOddsStatus = e.ucWinOddsStatus,
                    winOdds = e.unWinOdds,
                    placeOddsStatus = e.ucPlaceOddsStatus,
                    placeOddsLow = e.unPlaceOddsLow,
                    placeOddsHigh = e.unPlaceOddsHigh
                };
            }

            NativeMethods.ReleaseRaceCardData(ref tempRaceCardData);

            return returnValue;
        }

        /// <summary>
        /// お知らせ取得処理実行
        /// ログイン済みのセッションが必要(中央優先、失敗時は地方へフォールバック)。
        /// お知らせが無い場合は message が空文字・itemCount が 0 で成功を返す。
        /// </summary>
        /// <param name="notice">取得したお知らせ情報</param>
        /// <returns></returns>
        public static uint GetNotice(out ST_NOTICE_DATA notice)
        {
            ST_NOTICE_DATA_INTERNAL tempNoticeData = new()
            {
                szMessage = new byte[2048],
                szNoticeNo = new byte[16],
                szNoticeType = new byte[8],
                unItemCount = 0,
                pobjItem = IntPtr.Zero
            };

            uint returnValue = NativeMethods.GetNotice(ref tempNoticeData);

            notice = new ST_NOTICE_DATA()
            {
                message = DecodeUtf8(tempNoticeData.szMessage),
                noticeNo = DecodeUtf8(tempNoticeData.szNoticeNo),
                noticeType = DecodeUtf8(tempNoticeData.szNoticeType),
                itemCount = tempNoticeData.unItemCount,
                items = Array.Empty<ST_NOTICE_ITEM>()
            };

            // 取得失敗、または一覧が無い場合はここで解放して戻る
            if ((returnValue & (uint)RETURN_VALUE.SUCCESS) == 0 || tempNoticeData.unItemCount <= 0 || tempNoticeData.pobjItem == IntPtr.Zero)
            {
                NativeMethods.ReleaseNoticeData(ref tempNoticeData);
                return returnValue;
            }

            // ネイティブ側で確保された一覧配列をマネージド配列へ複製する
            notice.items = new ST_NOTICE_ITEM[tempNoticeData.unItemCount];
            int itemSize = Marshal.SizeOf(typeof(ST_NOTICE_ITEM_INTERNAL));
            for (int i = 0; i < tempNoticeData.unItemCount; i++)
            {
                IntPtr elementPtr = IntPtr.Add(tempNoticeData.pobjItem, i * itemSize);
                ST_NOTICE_ITEM_INTERNAL item = Marshal.PtrToStructure<ST_NOTICE_ITEM_INTERNAL>(elementPtr);

                notice.items[i] = new ST_NOTICE_ITEM()
                {
                    title = DecodeUtf8(item.szTitle),
                    date = DecodeUtf8(item.szDate),
                    url = DecodeUtf8(item.szUrl),
                    icon = DecodeUtf8(item.szIcon),
                    color = DecodeUtf8(item.szColor)
                };
            }

            // データの複製が終わったら、取得と同時にネイティブ側のメモリを解放する
            NativeMethods.ReleaseNoticeData(ref tempNoticeData);

            return returnValue;
        }

        /// <summary>
        /// DLLが返すUTF-8・null終端のバイト列を文字列へデコードする
        /// </summary>
        private static string DecodeUtf8(byte[] raw)
        {
            if (raw == null)
            {
                return string.Empty;
            }

            int length = Array.IndexOf(raw, (byte)0);
            if (length < 0)
            {
                length = raw.Length;
            }

            return length == 0 ? string.Empty : Encoding.UTF8.GetString(raw, 0, length);
        }
        #endregion
    }
}
