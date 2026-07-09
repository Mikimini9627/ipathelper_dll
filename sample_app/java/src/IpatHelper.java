import java.util.Arrays;
import java.util.List;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Platform;
import com.sun.jna.Pointer;
import com.sun.jna.Structure;

public class IpatHelper {

	//DLLのインスタンスを取得する
	private IpatHelperInvoker m_iPatHelperInvoker = null;

	//DLL関数呼び出しインターフェース
	private interface IpatHelperInvoker extends Library {

		public int Login(String iNetId, String id, String password, String pars);
		public int Logout();
		public int Deposit(int depositValue, short retryCount);
		public int Withdraw(short retryCount);
		public int GetPurchaseData(ST_PURCHASE_DATA_INTERNAL purchaseData);
		// 変更: 値渡し → ポインタ渡し（ByReference）
		public void ReleasePurchaseData(ST_PURCHASE_DATA_INTERNAL.ByReference purchaseData);
		public int GetBetInstance(short place, byte raceNo,
				byte year, byte month, byte day, byte houshiki,
				byte shikibetsu, int kingaku, String kaime, ST_BET_DATA betData);
		public int Bet(ST_BET_DATA[] betData, short betCount, short waitMilliSeconds);
		public int SetAutoDepositFlag(boolean enable, int depositValue, short confirmTimeout);
		public int GetBetInstanceWin5(int kingaku, byte year,
				byte month, byte day, String kaime, ST_BET_DATA_WIN5 betData);
		public int BetWin5(ST_BET_DATA_WIN5 betData, short waitMilliSeconds);
		public int GetOdds(short place, byte raceNo, byte shikibetsu, ST_ODDS_DATA_INTERNAL oddsData);
		public void ReleaseOddsData(ST_ODDS_DATA_INTERNAL.ByReference oddsData);
		public int GetRaceCard(short place, byte raceNo, ST_RACECARD_DATA_INTERNAL raceCardData);
		public void ReleaseRaceCardData(ST_RACECARD_DATA_INTERNAL.ByReference raceCardData);
	}

	//開催
	public class Kaisai{
		public static final int KAISAI_SAPPORO = 0;
		public static final int KAISAI_HAKODATE = 1;
		public static final int KAISAI_FUKUSHIMA = 2;
		public static final int KAISAI_NIIGATA = 3;
		public static final int KAISAI_TOKYO = 4;
		public static final int KAISAI_NAKAYAMA = 5;
		public static final int KAISAI_CHUKYO	 = 6;
		public static final int KAISAI_KYOTO = 7;
		public static final int KAISAI_HANSHIN = 8;
		public static final int KAISAI_KOKURA = 9;

		public static final int KAISAI_SONODA = 10;
		public static final int KAISAI_HIMEJI = 11;
		public static final int KAISAI_NAGOYA = 12;
		public static final int KAISAI_MONBETSU = 13;
		public static final int KAISAI_MORIOKA = 14;
		public static final int KAISAI_MIZUSAWA = 15;
		public static final int KAISAI_URAWA = 16;
		public static final int KAISAI_FUNABASHI = 17;
		public static final int KAISAI_OI = 18;
		public static final int KAISAI_KAWASAKI = 19;
		public static final int KAISAI_KASAMATSU = 20;
		public static final int KAISAI_KANAZAWA = 21;
		public static final int KAISAI_KOCHI = 22;
		public static final int KAISAI_SAGA = 23;
		
		public static final int KAISAI_LONGCHAMP = 24;
		public static final int KAISAI_SHATIN = 25;
		public static final int KAISAI_SANTAANITA = 26;
		public static final int KAISAI_DEAUVILE = 27;
		public static final int KAISAI_CHURCHILLDOWNS = 28;
		public static final int KAISAI_ABDULAZIZ = 29;
	}

	//方式
	public class Houshiki{
		public static final int HOUSHIKI_NORMAL	 = 0;
		public static final int HOUSHIKI_FORMATION	 = 1;
		public static final int HOUSHIKI_BOX = 2;
	}

	//式別
	public class Shikibetsu{
		public static final int SHIKIBETSU_WIN = 1;
		public static final int SHIKIBETSU_PLACE = 2;
		public static final int SHIKIBETSU_BRACKETQUINELLA = 3;
		public static final int SHIKIBETSU_QUINELLA = 4;
		public static final int SHIKIBETSU_QUINELLAPLACE = 5;
		public static final int SHIKIBETSU_EXACTA = 6;
		public static final int SHIKIBETSU_TRIO = 7;
		public static final int SHIKIBETSU_TRIFECTA = 8;
	}

	//オッズ状態
	public class OddsStatus{
		public static final int ODDS_STATUS_NORMAL = 0;
		public static final int ODDS_STATUS_CANCEL = 1;
		public static final int ODDS_STATUS_UNACQUIRED = 2;
	}

	//馬券購入日タイプ
	public class DayType{
		public static final int DAYTYPE_TODAY = 1;
		public static final int DAYTYPE_BEFORE = 2;
	}

	//購入フラグ
	public class BetFlag{
		public static final int BETFLAG_NORMAL = 1;
		public static final int BETFLAG_WIN5 = 2;
		public static final int BETFLAG_INTERNAL = 3;
	}

	//購入ステータス
	public class DecisionFlag{
		public static final int DECISIONFLAG_DEFAULT = 1;
		public static final int DECISIONFLAG_NORMAL = 2;
		public static final int DECISIONFLAG_DEADLINE = 3;
		public static final int DECISIONFLAG_CANCEL = 4;
		public static final int DECISIONFLAG_FLATMATESCANCEL = 5;
		public static final int DECISIONFLAG_HIT = 6;
		public static final int DECISIONFLAG_MISS = 7;
		public static final int DECISIONFLAG_BACK = 8;
		public static final int DECISIONFLAG_PARTCANCEL = 10;
		public static final int DECISIONFLAG_INVALID = 11;
		public static final int DECISIONFLAG_SALECANCEL = 12;
	}

	//曜日
	public class WeekDay{
		public static final int WEEKDAY_SUNDAY = 1;
		public static final int WEEKDAY_MONDAY = 2;
		public static final int WEEKDAY_TUESDAY = 3;
		public static final int WEEKDAY_WEDNESDAY = 4;
		public static final int WEEKDAY_THURSDAY = 5;
		public static final int WEEKDAY_FRIDAY = 6;
		public static final int WEEKDAY_SATURDAY = 7;
	}

	//定数
	public class Constant{
		public static final int DEPOSIT_DEFAULT_VALUE = 1000;
		public static final int DEFAULT_CONFIRM_TIMEOUT = 10000;
		public static final int DEFAULT_RETRY_COUNT = 10;
	}

	//戻り値
	public class ReturnValue{
		public static final int SUCCESS = 1;
		public static final int UNSUCCESS = 2;
		public static final int FAILED_CHUOU  = 4;
		public static final int FAILED_CHIHOU = 8;
		public static final int FAILED_COMMUNICATE_CHUOU = 16;
		public static final int FAILED_COMMUNICATE_CHIHOU  = 32;
	}

	// 馬券情報(詳細)
	public static class ST_TICKET_DATA_DETAIL  extends Structure {
		
		@Override
        protected List<String> getFieldOrder() {
            return Arrays.asList("decisionFlag", "betFlag", "kaisai", 
            		"raceNo", "week", "method", "type", "horseNo", "multi");
        }
		
		public byte decisionFlag;
		public byte betFlag;
		public short kaisai;
		public byte raceNo;
		public byte week;
		public byte method;
		public byte type;
		public int[] horseNo;
		public byte multi;

		public ST_TICKET_DATA_DETAIL()
		{
			decisionFlag = 0;
			betFlag = 0;
			kaisai = 0;
			raceNo = 0;
			week = 0;
			method = 0;
			type = 0;
			horseNo = new int[5];
			multi = 0;
		}

		public static int GetSize(){
			return 32;
		}
	};
	
	// 馬券詳細情報リスト(内部使用)
	public static class ST_TICKET_DATA_DETAIL_LIST_INTERNAL  extends Structure {
		
		@Override
        protected List<String> getFieldOrder() {
            return Arrays.asList("detailDataList");
        }
		
		public ST_TICKET_DATA_DETAIL[] detailDataList; 

		public ST_TICKET_DATA_DETAIL_LIST_INTERNAL(Pointer sourcePointer, int detailCount) {
	        super(sourcePointer);
	        detailDataList = new ST_TICKET_DATA_DETAIL[detailCount];
	        read();
	    }
	};
	
	// 馬券情報(内部使用)
	public static class ST_TICKET_DATA_INTERNAL  extends Structure {
		
		@Override
        protected List<String> getFieldOrder() {
            return Arrays.asList("dayFlag", "receiptNo", "hour", 
            		"minute", "kingaku", "payout", "detailCount", "detailData");
        }
		
		public byte dayFlag;
		public byte receiptNo;
		public byte hour;
		public byte minute;
		public int kingaku;
		public int payout;
		public int detailCount;
		public Pointer detailData; 

		public ST_TICKET_DATA_INTERNAL()
		{
			dayFlag = 0;
			receiptNo = 0;
			hour = 0;
			minute = 0;
			kingaku = 0;
			payout = 0;
			detailCount = 0;
			detailData = null;
		}

		public static int GetSize(){
			return 24;
		}
	};
	
	// 馬券情報リスト(内部使用)
	public static class ST_TICKET_DATA_LIST_INTERNAL  extends Structure {
		
		@Override
        protected List<String> getFieldOrder() {
            return Arrays.asList("ticketList");
        }
		
		public ST_TICKET_DATA_INTERNAL[] ticketList; 

		public ST_TICKET_DATA_LIST_INTERNAL(Pointer sourcePointer, int ticketCount) {
	        super(sourcePointer);
	        ticketList = new ST_TICKET_DATA_INTERNAL[ticketCount];
	        read();
	    }
	};
	
	//購入情報(内部使用)
	public static class ST_PURCHASE_DATA_INTERNAL extends Structure {

		@Override
        protected List<String> getFieldOrder() {
            return Arrays.asList("remainBetCount", "balance",
            		"dayPurchase", "dayHaraimodosi", "totalPurchase", "totalHaraimodosi", "ticketCount", "ticketData");
        }

		public short remainBetCount;
		public int balance;
		public int dayPurchase;
		public int dayHaraimodosi;
		public int totalPurchase;
		public int totalHaraimodosi;
		public int ticketCount;
		public Pointer ticketData; 

		public ST_PURCHASE_DATA_INTERNAL()
		{
			remainBetCount = 0;
			balance = 0;
			dayPurchase = 0;
			dayHaraimodosi = 0;
			totalPurchase = 0;
			totalHaraimodosi = 0;
			ticketCount = 0;
			ticketData = null ;
		}

		// 変更: ポインタ渡し用の ByReference 内部クラスを追加
		public static class ByReference extends ST_PURCHASE_DATA_INTERNAL implements Structure.ByReference {}
    }
	
	// 馬券情報
	public static class ST_TICKET_DATA {
		
		public byte dayFlag;
		public byte receiptNo;
		public byte hour;
		public byte minute;
		public int kingaku;
		public int payout;
		public int detailCount;
		public ST_TICKET_DATA_DETAIL[] detailData; 

		public ST_TICKET_DATA()
		{
			dayFlag = 0;
			receiptNo = 0;
			hour = 0;
			minute = 0;
			kingaku = 0;
			payout = 0;
			detailCount = 0;
			detailData = null;
		}
	};
	
	//購入情報
	public static class ST_PURCHASE_DATA {

		public short remainBetCount;
		public int balance;
		public int dayPurchase;
		public int dayHaraimodosi;
		public int totalPurchase;
		public int totalHaraimodosi;
		public int ticketCount;
		public ST_TICKET_DATA[] ticketData; 

		public ST_PURCHASE_DATA()
		{
			remainBetCount = 0;
			balance = 0;
			dayPurchase = 0;
			dayHaraimodosi = 0;
			totalPurchase = 0;
			totalHaraimodosi = 0;
			ticketCount = 0;
			ticketData = null ;
		}
    }

	//買い目データ
	public static class ST_BET_DATA extends Structure {

		@Override
        protected List<String> getFieldOrder() {
            return Arrays.asList("place", "raceNo",  "youbi", "kaikata", "shikibetsu", "kingaku", "umabanNo", "totalAmount");
        }

		public short place;
		public byte raceNo;
		public byte youbi;
		public byte kaikata;
		public byte shikibetsu;
		public int kingaku;
		public int[] umabanNo;
		public int totalAmount;

		public ST_BET_DATA() {
			place = 0;
			raceNo = 0;
			youbi = 0;
			kaikata = 0;
			shikibetsu = 0;
			kingaku = 0;
			umabanNo = new int[3];
			totalAmount = 0;
		}
	}

	//買い目データ(Win5)
	public static class ST_BET_DATA_WIN5 extends Structure {

		@Override
        protected List<String> getFieldOrder() {
            return Arrays.asList("kingaku", "youbi", "umabanNo");
        }

		public int kingaku;
		public byte youbi;
		public int[] umabanNo;

		public ST_BET_DATA_WIN5() {
			kingaku = 0;
			youbi = 0;
			umabanNo = new int[5];
		}
	}

	// オッズ明細
	public static class ST_ODDS_DETAIL extends Structure {

		@Override
        protected List<String> getFieldOrder() {
            return Arrays.asList("type", "horse1", "horse2", "horse3", "status", "odds", "oddsHigh");
        }

		public byte type;      // 式別(Shikibetsu)
		public byte horse1;    // 馬番/枠番1
		public byte horse2;    // 馬番/枠番2(単勝・複勝は0)
		public byte horse3;    // 馬番3(三連複・三連単のみ、それ以外0)
		public byte status;    // 0:通常 1:発売中止 2:オッズ未取得
		public int odds;       // オッズ×10(複勝・ワイドは下限)
		public int oddsHigh;   // 複勝・ワイドの上限×10(それ以外0)

		public ST_ODDS_DETAIL() {
			type = 0;
			horse1 = 0;
			horse2 = 0;
			horse3 = 0;
			status = 0;
			odds = 0;
			oddsHigh = 0;
		}

		public static int GetSize(){
			return 16;
		}
	};

	// オッズ明細リスト(内部使用)
	public static class ST_ODDS_DETAIL_LIST_INTERNAL extends Structure {

		@Override
        protected List<String> getFieldOrder() {
            return Arrays.asList("detailList");
        }

		public ST_ODDS_DETAIL[] detailList;

		public ST_ODDS_DETAIL_LIST_INTERNAL(Pointer sourcePointer, int detailCount) {
	        super(sourcePointer);
	        detailList = new ST_ODDS_DETAIL[detailCount];
	        read();
	    }
	};

	// オッズ情報(内部使用)
	public static class ST_ODDS_DATA_INTERNAL extends Structure {

		@Override
        protected List<String> getFieldOrder() {
            return Arrays.asList("place", "raceNo", "oddsTime", "detailCount", "detailData");
        }

		public short place;
		public byte raceNo;
		public byte[] oddsTime;
		public int detailCount;
		public Pointer detailData;

		public ST_ODDS_DATA_INTERNAL() {
			place = 0;
			raceNo = 0;
			oddsTime = new byte[8];
			detailCount = 0;
			detailData = null;
		}

		// ポインタ渡し用の ByReference 内部クラス
		public static class ByReference extends ST_ODDS_DATA_INTERNAL implements Structure.ByReference {}
	};

	// オッズ情報
	public static class ST_ODDS_DATA {

		public short place;
		public byte raceNo;
		public String oddsTime;
		public int detailCount;
		public ST_ODDS_DETAIL[] oddsDetail;

		public ST_ODDS_DATA() {
			place = 0;
			raceNo = 0;
			oddsTime = "";
			detailCount = 0;
			oddsDetail = null;
		}
	}

	// 出走馬明細
	public static class ST_ENTRY_DETAIL extends Structure {

		@Override
        protected List<String> getFieldOrder() {
            return Arrays.asList("wakuban", "umaban", "horseName", "sex", "age",
            		"weightStatus", "weight", "weightDiffCode", "weightDiff", "apprentice",
            		"jockeyName", "burden", "trainerName", "winPopular", "winOddsStatus", "winOdds",
            		"placeOddsStatus", "placeOddsLow", "placeOddsHigh");
        }

		public byte wakuban;         // 枠番
		public byte umaban;          // 馬番
		public byte[] horseName;     // 馬名(UTF-8)
		public byte[] sex;           // 性別(UTF-8)
		public byte age;             // 年齢
		public byte weightStatus;    // 0:通常 1:未発表 2:出走取消 3:計量不能
		public short weight;         // 馬体重(kg)
		public byte weightDiffCode;  // 増減符号(0:なし 1:増 2:減 3:増減なし 7:初出走 8:前計不)
		public short weightDiff;     // 増減量(kg)
		public byte apprentice;      // 見習騎手コード
		public byte[] jockeyName;    // 騎手名(UTF-8)
		public short burden;         // 斤量×10
		public byte[] trainerName;   // 調教師名(UTF-8)
		public short winPopular;     // 単勝人気
		public byte winOddsStatus;   // 0:通常 1:発売中止 2:未取得
		public int winOdds;          // 単勝オッズ×10
		public byte placeOddsStatus; // 0:通常 1:発売中止 2:未取得
		public int placeOddsLow;     // 複勝オッズ下限×10
		public int placeOddsHigh;    // 複勝オッズ上限×10

		public ST_ENTRY_DETAIL() {
			wakuban = 0;
			umaban = 0;
			horseName = new byte[64];
			sex = new byte[8];
			age = 0;
			weightStatus = 0;
			weight = 0;
			weightDiffCode = 0;
			weightDiff = 0;
			apprentice = 0;
			jockeyName = new byte[48];
			burden = 0;
			trainerName = new byte[48];
			winPopular = 0;
			winOddsStatus = 0;
			winOdds = 0;
			placeOddsStatus = 0;
			placeOddsLow = 0;
			placeOddsHigh = 0;
		}

		public static int GetSize(){
			return 204;
		}
	};

	// 出走馬明細リスト(内部使用)
	public static class ST_ENTRY_DETAIL_LIST_INTERNAL extends Structure {

		@Override
        protected List<String> getFieldOrder() {
            return Arrays.asList("entryList");
        }

		public ST_ENTRY_DETAIL[] entryList;

		public ST_ENTRY_DETAIL_LIST_INTERNAL(Pointer sourcePointer, int entryCount) {
	        super(sourcePointer);
	        entryList = new ST_ENTRY_DETAIL[entryCount];
	        read();
	    }
	};

	// 出馬表情報(内部使用)
	public static class ST_RACECARD_DATA_INTERNAL extends Structure {

		@Override
        protected List<String> getFieldOrder() {
            return Arrays.asList("place", "raceNo", "oddsTime", "entryCount", "entryData");
        }

		public short place;
		public byte raceNo;
		public byte[] oddsTime;
		public int entryCount;
		public Pointer entryData;

		public ST_RACECARD_DATA_INTERNAL() {
			place = 0;
			raceNo = 0;
			oddsTime = new byte[8];
			entryCount = 0;
			entryData = null;
		}

		// ポインタ渡し用の ByReference 内部クラス
		public static class ByReference extends ST_RACECARD_DATA_INTERNAL implements Structure.ByReference {}
	};

	// 出馬表情報
	public static class ST_RACECARD_DATA {

		public short place;
		public byte raceNo;
		public String oddsTime;
		public int entryCount;
		public ST_ENTRY_DETAIL[] entries;

		public ST_RACECARD_DATA() {
			place = 0;
			raceNo = 0;
			oddsTime = "";
			entryCount = 0;
			entries = null;
		}
	}

	//コンストラクタ
	@SuppressWarnings("deprecation")
	public IpatHelper()
	{
		//ライブラリのロード
		if(Platform.is64Bit() == true) {
			m_iPatHelperInvoker = (IpatHelperInvoker)Native.loadLibrary(".\\library\\x64\\IpatHelper.dll", IpatHelperInvoker.class);
		}else {
			m_iPatHelperInvoker = (IpatHelperInvoker)Native.loadLibrary(".\\library\\x86\\IpatHelper.dll", IpatHelperInvoker.class);
		}
	}

	//ログイン
	public int Login(String iNetId, String id, String password, String pars) {

		return m_iPatHelperInvoker.Login(iNetId, id, password, pars);
	}
	
	//ログアウト
	public int Logout() {

		return m_iPatHelperInvoker.Logout();
	}

	//入金
	public int Deposit(int depositValue, int retryCount) {

		return m_iPatHelperInvoker.Deposit(depositValue, (short)retryCount);
	}

	public int Deposit(int depositValue) {

		return Deposit(depositValue, Constant.DEFAULT_RETRY_COUNT);
	}

	//出金
	public int Withdraw(int retryCount) {

		return m_iPatHelperInvoker.Withdraw((short)retryCount);
	}

	public int Withdraw() {

		return Withdraw(Constant.DEFAULT_RETRY_COUNT);
	}

	//購入状況取得
	public int GetPurchaseData(ST_PURCHASE_DATA purchaseData) {

		ST_PURCHASE_DATA_INTERNAL tempPurchase = new ST_PURCHASE_DATA_INTERNAL();
		tempPurchase.remainBetCount = 0;
		tempPurchase.balance = 0;
		tempPurchase.dayPurchase = 0;
		tempPurchase.dayHaraimodosi = 0;
		tempPurchase.totalPurchase = 0;
		tempPurchase.totalHaraimodosi = 0;
		tempPurchase.ticketCount = 0;
		tempPurchase.ticketData = null;
		
		int returnValue = m_iPatHelperInvoker.GetPurchaseData(tempPurchase);
		if ((returnValue & 1) != 1) {
			ST_PURCHASE_DATA_INTERNAL.ByReference ref = new ST_PURCHASE_DATA_INTERNAL.ByReference();
			ref.useMemory(tempPurchase.getPointer(), 0);
			m_iPatHelperInvoker.ReleasePurchaseData(ref);
			return returnValue;
		}

		purchaseData.remainBetCount = tempPurchase.remainBetCount;
		purchaseData.balance = tempPurchase.balance;
		purchaseData.dayHaraimodosi = tempPurchase.dayPurchase;
		purchaseData.dayHaraimodosi = tempPurchase.dayHaraimodosi;
		purchaseData.totalPurchase = tempPurchase.totalPurchase;
		purchaseData.totalHaraimodosi = tempPurchase.totalHaraimodosi;
		purchaseData.ticketCount = tempPurchase.ticketCount;
		purchaseData.ticketData = new ST_TICKET_DATA[tempPurchase.ticketCount];
		
		if(tempPurchase.ticketCount <= 0) {
			ST_PURCHASE_DATA_INTERNAL.ByReference ref = new ST_PURCHASE_DATA_INTERNAL.ByReference();
			ref.useMemory(tempPurchase.getPointer(), 0);
			m_iPatHelperInvoker.ReleasePurchaseData(ref);
			return returnValue;
		}
		
		// ポインターから馬券情報リストを取得する
		ST_TICKET_DATA_LIST_INTERNAL ticketDataList = new ST_TICKET_DATA_LIST_INTERNAL(tempPurchase.ticketData, tempPurchase.ticketCount);

		for (int i = 0; i < tempPurchase.ticketCount; i++){

			purchaseData.ticketData[i] = new ST_TICKET_DATA();
			purchaseData.ticketData[i].dayFlag = ticketDataList.ticketList[i].dayFlag;
			purchaseData.ticketData[i].receiptNo = ticketDataList.ticketList[i].receiptNo;
			purchaseData.ticketData[i].hour = ticketDataList.ticketList[i].hour;
			purchaseData.ticketData[i].minute = ticketDataList.ticketList[i].minute;
			purchaseData.ticketData[i].kingaku = ticketDataList.ticketList[i].kingaku;
			purchaseData.ticketData[i].payout = ticketDataList.ticketList[i].payout;
			purchaseData.ticketData[i].detailCount = ticketDataList.ticketList[i].detailCount;
			purchaseData.ticketData[i].detailData = new ST_TICKET_DATA_DETAIL[ticketDataList.ticketList[i].detailCount];

			if(ticketDataList.ticketList[i].detailCount <= 0) {
			ST_PURCHASE_DATA_INTERNAL.ByReference ref = new ST_PURCHASE_DATA_INTERNAL.ByReference();
			ref.useMemory(tempPurchase.getPointer(), 0);
			m_iPatHelperInvoker.ReleasePurchaseData(ref);
				return returnValue;
			}
			
			// ポインターから馬券情報リストを取得する
			ST_TICKET_DATA_DETAIL_LIST_INTERNAL detailDataList = new ST_TICKET_DATA_DETAIL_LIST_INTERNAL(ticketDataList.ticketList[i].detailData, ticketDataList.ticketList[i].detailCount);

			for (int j = 0; j < ticketDataList.ticketList[i].detailCount; j++){
				purchaseData.ticketData[i].detailData[j] = detailDataList.detailDataList[j];
			}
		}

		return returnValue;
	}

	//ベットインスタンス取得
	public int GetBetInstance(int place, int raceNo,
			int year, int month, int day, int houshiki,
			int shikibetsu, int kingaku, String kaime, ST_BET_DATA betData) {

		return m_iPatHelperInvoker.GetBetInstance((short)place, (byte)raceNo, (byte)year, 
				(byte)month,(byte) day, (byte)houshiki, (byte)shikibetsu, kingaku, kaime, betData);
	}

	//投票
	public int Bet(ST_BET_DATA[] betData, int betCount, int waitMilliSeconds) {
		return m_iPatHelperInvoker.Bet(betData, (short)betCount , (short)waitMilliSeconds);
	}

	//自動入金機能設定
	public int SetAutoDepositFlag(boolean enable, int depositValue, int confirmTimeout) {
		return m_iPatHelperInvoker.SetAutoDepositFlag(enable, depositValue, (short)confirmTimeout);
	}

	//ベットインスタンス取得(Win5)
	public int GetBetInstanceWin5(int kingaku, int year,
			int month, int day, String kaime, ST_BET_DATA_WIN5 betData) {
		return m_iPatHelperInvoker.GetBetInstanceWin5(kingaku, (byte)year, (byte)month, (byte)day, kaime, betData);
	}

	//投票(Win5)
	public int BetWin5(ST_BET_DATA_WIN5 betData, int waitMilliSeconds) {
		return m_iPatHelperInvoker.BetWin5(betData, (short)waitMilliSeconds);
	}

	//オッズ取得(中央競馬・地方競馬に対応)
	public int GetOdds(int place, int raceNo, int shikibetsu, ST_ODDS_DATA oddsData) {

		ST_ODDS_DATA_INTERNAL tempOdds = new ST_ODDS_DATA_INTERNAL();

		int returnValue = m_iPatHelperInvoker.GetOdds((short)place, (byte)raceNo, (byte)shikibetsu, tempOdds);

		oddsData.place = tempOdds.place;
		oddsData.raceNo = tempOdds.raceNo;
		oddsData.oddsTime = ByteArrayToString(tempOdds.oddsTime);
		oddsData.detailCount = tempOdds.detailCount;
		oddsData.oddsDetail = new ST_ODDS_DETAIL[Math.max(tempOdds.detailCount, 0)];

		// 取得失敗・明細なしはここで解放して戻る
		if ((returnValue & 1) != 1 || tempOdds.detailCount <= 0 || tempOdds.detailData == null) {
			ST_ODDS_DATA_INTERNAL.ByReference ref = new ST_ODDS_DATA_INTERNAL.ByReference();
			ref.useMemory(tempOdds.getPointer(), 0);
			m_iPatHelperInvoker.ReleaseOddsData(ref);
			return returnValue;
		}

		// ポインターからオッズ明細リストを取得する
		ST_ODDS_DETAIL_LIST_INTERNAL detailList = new ST_ODDS_DETAIL_LIST_INTERNAL(tempOdds.detailData, tempOdds.detailCount);
		for (int i = 0; i < tempOdds.detailCount; i++) {
			oddsData.oddsDetail[i] = detailList.detailList[i];
		}

		// 取得と同時にネイティブ側のメモリを解放する
		ST_ODDS_DATA_INTERNAL.ByReference ref = new ST_ODDS_DATA_INTERNAL.ByReference();
		ref.useMemory(tempOdds.getPointer(), 0);
		m_iPatHelperInvoker.ReleaseOddsData(ref);

		return returnValue;
	}

	//出馬表取得(中央競馬・地方競馬に対応)
	public int GetRaceCard(int place, int raceNo, ST_RACECARD_DATA raceCard) {

		ST_RACECARD_DATA_INTERNAL tempRaceCard = new ST_RACECARD_DATA_INTERNAL();

		int returnValue = m_iPatHelperInvoker.GetRaceCard((short)place, (byte)raceNo, tempRaceCard);

		raceCard.place = tempRaceCard.place;
		raceCard.raceNo = tempRaceCard.raceNo;
		raceCard.oddsTime = ByteArrayToString(tempRaceCard.oddsTime);
		raceCard.entryCount = tempRaceCard.entryCount;
		raceCard.entries = new ST_ENTRY_DETAIL[Math.max(tempRaceCard.entryCount, 0)];

		// 取得失敗・明細なしはここで解放して戻る
		if ((returnValue & 1) != 1 || tempRaceCard.entryCount <= 0 || tempRaceCard.entryData == null) {
			ST_RACECARD_DATA_INTERNAL.ByReference ref = new ST_RACECARD_DATA_INTERNAL.ByReference();
			ref.useMemory(tempRaceCard.getPointer(), 0);
			m_iPatHelperInvoker.ReleaseRaceCardData(ref);
			return returnValue;
		}

		// ポインターから出走馬明細リストを取得する
		ST_ENTRY_DETAIL_LIST_INTERNAL entryList = new ST_ENTRY_DETAIL_LIST_INTERNAL(tempRaceCard.entryData, tempRaceCard.entryCount);
		for (int i = 0; i < tempRaceCard.entryCount; i++) {
			raceCard.entries[i] = entryList.entryList[i];
		}

		// 取得と同時にネイティブ側のメモリを解放する
		ST_RACECARD_DATA_INTERNAL.ByReference ref = new ST_RACECARD_DATA_INTERNAL.ByReference();
		ref.useMemory(tempRaceCard.getPointer(), 0);
		m_iPatHelperInvoker.ReleaseRaceCardData(ref);

		return returnValue;
	}

	//オッズ更新時刻(byte[8]、終端まで)を文字列へ変換する
	private static String ByteArrayToString(byte[] bytes) {
		int length = 0;
		while (length < bytes.length && bytes[length] != 0) {
			length++;
		}
		return new String(bytes, 0, length, java.nio.charset.StandardCharsets.US_ASCII);
	}

	//馬名等(byte[]、UTF-8、終端まで)を文字列へ変換する
	public static String Utf8ToString(byte[] bytes) {
		int length = 0;
		while (length < bytes.length && bytes[length] != 0) {
			length++;
		}
		return new String(bytes, 0, length, java.nio.charset.StandardCharsets.UTF_8);
	}
}
