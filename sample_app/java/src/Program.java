import java.io.PrintStream;
import java.nio.charset.StandardCharsets;

import com.sun.jna.Native;
import com.sun.jna.win32.StdCallLibrary;

public class Program {

	// Windows コンソール出力コードページを UTF-8 に切り替えるための最小 JNA 定義。
	// kernel32 は WINAPI (stdcall) のため StdCallLibrary を使う (x86 でも安全)。
	private interface Kernel32 extends StdCallLibrary {
		Kernel32 INSTANCE = Native.load("kernel32", Kernel32.class);
		boolean SetConsoleOutputCP(int wCodePageID);
	}

	public static void main(String[] args) {

		// DLL が返す文字列 (馬名・レース名等) は UTF-8。既定のコンソール (CP932) と
		// System.out の双方を UTF-8 に合わせないと文字化けするため、両方を切り替える。
		try {
			Kernel32.INSTANCE.SetConsoleOutputCP(65001);
			System.setOut(new PrintStream(System.out, true, StandardCharsets.UTF_8));
		} catch (Throwable ignore) {
			// コンソールが無い/JNA 未解決などの環境では無視して続行する
		}

		int returnValue = 0;
		
		//IpatHelperのインスタンスを取得する
		IpatHelper iPatHelper = new IpatHelper();
		
		//DLL内部のログを受け取る(調査時は LOG_LEVEL_TRACE)
		//入出金はサーバがエラーコードを返さないため、失敗の原因を知る唯一の手段になる
		iPatHelper.SetLogCallback((level, message) -> {
			String[] levelName = { "TRACE", "INFO", "WARN", "ERROR" };
			//メッセージはUTF-8のnull終端文字列
			System.out.println("[" + levelName[level] + "] " + message.getString(0, "UTF-8"));
		}, IpatHelper.LogLevel.LOG_LEVEL_INFO);

		//ログイン処理(各自自分のIDに変えてください)
		returnValue = iPatHelper.Login("********", "********", "****", "****");
		if((returnValue & IpatHelper.ReturnValue.SUCCESS) != IpatHelper.ReturnValue.SUCCESS) {
			if((returnValue & IpatHelper.ReturnValue.FAILED_OUT_OF_SERVICE) != 0) {
				//投票受付時間外またはメンテナンス中。即座に再試行しても必ず失敗する
				System.out.println("ログインに失敗しました。(サービス時間外)");
			} else {
				System.out.println("ログインに失敗しました。");
			}
			return;
		}

		//お知らせ取得。解放はラッパー内部で実施される
		IpatHelper.ST_NOTICE_DATA notice = new IpatHelper.ST_NOTICE_DATA();
		returnValue = iPatHelper.GetNotice(notice);
		if((returnValue & IpatHelper.ReturnValue.SUCCESS) == IpatHelper.ReturnValue.SUCCESS) {
			if(!notice.message.isEmpty()) {
				System.out.println("お知らせ: " + notice.message);
			}
			for (IpatHelper.ST_NOTICE_ITEM item : notice.items) {
				System.out.println("  " + item.date + " " + item.title + " " + item.url);
			}
		}

		//オッズ取得(馬連・中央競馬/地方競馬/海外競馬に対応)。解放はラッパー内部で実施される
		IpatHelper.ST_ODDS_DATA oddsData = new IpatHelper.ST_ODDS_DATA();
		returnValue = iPatHelper.GetOdds(IpatHelper.Kaisai.KAISAI_TOKYO, 11, IpatHelper.Shikibetsu.SHIKIBETSU_QUINELLA, oddsData);
		if((returnValue & IpatHelper.ReturnValue.SUCCESS) == IpatHelper.ReturnValue.SUCCESS) {
			System.out.println("オッズ更新時刻: " + oddsData.oddsTime + " / 明細数: " + oddsData.detailCount);
			for (IpatHelper.ST_ODDS_DETAIL detail : oddsData.oddsDetail) {
				String oddsText = (detail.status == 0) ? String.format("%.1f", detail.odds / 10.0) : ("status=" + detail.status);
				System.out.println("  " + detail.horse1 + "-" + detail.horse2 + " : " + oddsText);
			}
		}

		//出馬表取得(中央競馬/地方競馬/海外競馬に対応)。解放はラッパー内部で実施される
		IpatHelper.ST_RACECARD_DATA raceCard = new IpatHelper.ST_RACECARD_DATA();
		returnValue = iPatHelper.GetRaceCard(IpatHelper.Kaisai.KAISAI_TOKYO, 11, raceCard);
		if((returnValue & IpatHelper.ReturnValue.SUCCESS) == IpatHelper.ReturnValue.SUCCESS) {
			System.out.println("レース名: " + raceCard.raceName);
			System.out.println("締切: " + raceCard.deadline + " / 発売状態: " + raceCard.raceStatus);
			System.out.println("オッズ更新時刻: " + raceCard.oddsTime + " / 出走頭数: " + raceCard.entryCount);
			for (IpatHelper.ST_ENTRY_DETAIL entry : raceCard.entries) {
				String name = IpatHelper.Utf8ToString(entry.horseName);
				String sex = IpatHelper.Utf8ToString(entry.sex);
				String jockey = IpatHelper.Utf8ToString(entry.jockeyName);
				String win = (entry.winOddsStatus == 0) ? String.format("%.1f", entry.winOdds / 10.0) : "-";
				System.out.println(String.format("  %2d番 %s %s%d 斤量%.1f 騎手:%s 単勝:%s 人気:%d",
						entry.umaban, name, sex, entry.age, entry.burden / 10.0, jockey, win, entry.winPopular));
			}
		}

		//買い目取得
		IpatHelper.ST_BET_DATA betData = new IpatHelper.ST_BET_DATA();
		returnValue = iPatHelper.GetBetInstance(IpatHelper.Kaisai.KAISAI_TOKYO, 11, 2021, 3, 14, IpatHelper.Houshiki.HOUSHIKI_NORMAL, 
				IpatHelper.Shikibetsu.SHIKIBETSU_TRIO, 100, "1-2-3", betData);
		if((returnValue & IpatHelper.ReturnValue.SUCCESS) != IpatHelper.ReturnValue.SUCCESS) {
			System.out.println("買い目取得に失敗しました。");
			iPatHelper.Logout();
			return;
		}
		
		//購入
		IpatHelper.ST_BET_DATA[] betDataList = new IpatHelper.ST_BET_DATA[] {betData};
		returnValue = iPatHelper.Bet(betDataList, betDataList.length, 1000);
		if((returnValue & IpatHelper.ReturnValue.SUCCESS) != IpatHelper.ReturnValue.SUCCESS) {
			System.out.println("購入に失敗しました。");
			iPatHelper.Logout();
			return;
		}
		
		//買い目取得(Win5)
		IpatHelper.ST_BET_DATA_WIN5 betDataWin5 = new IpatHelper.ST_BET_DATA_WIN5();
		returnValue = iPatHelper.GetBetInstanceWin5(100, 2021, 3, 14, "1-2-3-4-5", betDataWin5);
		if((returnValue & IpatHelper.ReturnValue.SUCCESS) != IpatHelper.ReturnValue.SUCCESS) {
			System.out.println("買い目取得(Win5)に失敗しました。");
			iPatHelper.Logout();
			return;
		}
		
		//購入(Win5)
		returnValue = iPatHelper.BetWin5(betDataWin5, 1000);
		if((returnValue & IpatHelper.ReturnValue.SUCCESS) != IpatHelper.ReturnValue.SUCCESS) {
			System.out.println("購入(Win5)に失敗しました。");
			iPatHelper.Logout();
			return;
		}

		//ログアウト処理
		iPatHelper.Logout();

		//コールバックを解除する(DLLを明示的にアンロードする場合は必須)
		iPatHelper.SetLogCallback(null, IpatHelper.LogLevel.LOG_LEVEL_INFO);
	}
}
