using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace IpatHelper_DotNetTestApl
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
            public byte youbi;
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
            public byte youbi;
            public uint kingaku;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
            public uint[] horseNo;
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
            MEYDAN,
            SHATIN,
            DEAUVILE,
            CHURCHILLDOWNS
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
            QUINELLAPLACE,
            QUINELLA,
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
            FAILED_COMMUNICATE = 16
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
            internal static extern uint Deposit(uint unDepositValue);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern uint Withdraw();

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern uint GetPurchaseData(ref ST_PURCHASE_DATA_INTERNAL objPurchaseData);

            [DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]
            internal static extern void ReleasePurchaseData(ST_PURCHASE_DATA_INTERNAL objPurchaseData);

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
            internal static extern uint SetAutoDepositFlag([MarshalAs(UnmanagedType.Bool)] bool bEnable, uint unDepositValue, ushort usConfrimTimeout);
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

            return NativeMethods.Login(Encoding.UTF8.GetBytes(iNetId),
                                       Encoding.UTF8.GetBytes(id),
                                       Encoding.UTF8.GetBytes(password),
                                       Encoding.UTF8.GetBytes(pars));
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
        public static uint Deposit(uint depositValue)
        {
            return NativeMethods.Deposit(depositValue);
        }

        /// <summary>
        /// 出金処理実行
        /// </summary>
        /// <returns></returns>
        public static uint Withdraw()
        {
            return NativeMethods.Withdraw();
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
                NativeMethods.ReleasePurchaseData(tempTicketData);
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
                NativeMethods.ReleasePurchaseData(tempTicketData);
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
                    NativeMethods.ReleasePurchaseData(tempTicketData);
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

            NativeMethods.ReleasePurchaseData(tempTicketData);

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
        #endregion
    }
}
