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
        }

        public struct ST_RACECARD_DATA
        {
            public ushort place;
            public byte raceNo;
            public string oddsTime;
            public uint entryCount;
            public ST_ENTRY_DETAIL[] entries;
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
            ABDULAZIZ
        }

        public enum Houshiki
        {
            NORMAL = 0,
            FORMATION,
            BOX
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

        public enum RETURN_VALUE
        {
            SUCCESS = 1,
            UNSUCCESS = 2,
            FAILED_CHUOU = 4,
            FAILED_CHIHOU = 8,
            FAILED_COMMUNICATE_CHUOU = 16,
            FAILED_COMMUNICATE_CHIHOU = 32,
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

        #region 内部クラス
        private class NativeMethods
        {
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
            internal static extern uint SetAutoDepositFlag([MarshalAs(UnmanagedType.I1)] bool bEnable, uint unDepositValue, ushort usConfrimTimeout);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern uint GetOdds(ushort usKaisai, byte byRaceNo, byte byShikibetsu, ref ST_ODDS_DATA_INTERNAL objOddsData);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern void ReleaseOddsData(ref ST_ODDS_DATA_INTERNAL objOddsData);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern uint GetRaceCard(ushort usPlace, byte byRaceNo, ref ST_RACECARD_DATA_INTERNAL objRaceCardData);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern void ReleaseRaceCardData(ref ST_RACECARD_DATA_INTERNAL objRaceCardData);
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
        /// オッズ取得処理実行(中央競馬・地方競馬に対応)
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
        /// 出馬表取得処理実行(中央競馬・地方競馬に対応)
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
                pobjEntry = IntPtr.Zero
            };

            uint returnValue = NativeMethods.GetRaceCard((ushort)place, raceNo, ref tempRaceCardData);

            raceCard = new ST_RACECARD_DATA()
            {
                place = tempRaceCardData.usPlace,
                raceNo = tempRaceCardData.ucRaceNo,
                oddsTime = DecodeUtf8(tempRaceCardData.szOddsTime),
                entryCount = tempRaceCardData.unEntryCount,
                entries = Array.Empty<ST_ENTRY_DETAIL>()
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
