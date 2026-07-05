public class Program {

	public static void main(String[] args) {
		
		int returnValue = 0;
		
		//IpatHelperのインスタンスを取得する
		IpatHelper iPatHelper = new IpatHelper();
		
		//ログイン処理(各自自分のIDに変えてください)
		returnValue = iPatHelper.Login("********", "********", "****", "****");
		if((returnValue & 1) != 1) {
			System.out.println("ログインに失敗しました。");
			return;
		}

		//オッズ取得(馬連・中央競馬のみ)。解放はラッパー内部で実施される
		IpatHelper.ST_ODDS_DATA oddsData = new IpatHelper.ST_ODDS_DATA();
		returnValue = iPatHelper.GetOdds(IpatHelper.Kaisai.KAISAI_TOKYO, 11, IpatHelper.Shikibetsu.SHIKIBETSU_QUINELLA, oddsData);
		if((returnValue & 1) == 1) {
			System.out.println("オッズ更新時刻: " + oddsData.oddsTime + " / 明細数: " + oddsData.detailCount);
			for (IpatHelper.ST_ODDS_DETAIL detail : oddsData.oddsDetail) {
				String oddsText = (detail.status == 0) ? String.format("%.1f", detail.odds / 10.0) : ("status=" + detail.status);
				System.out.println("  " + detail.horse1 + "-" + detail.horse2 + " : " + oddsText);
			}
		}

		//買い目取得
		IpatHelper.ST_BET_DATA betData = new IpatHelper.ST_BET_DATA();
		returnValue = iPatHelper.GetBetInstance(IpatHelper.Kaisai.KAISAI_TOKYO, 11, 2021, 3, 14, IpatHelper.Houshiki.HOUSHIKI_NORMAL, 
				IpatHelper.Shikibetsu.SHIKIBETSU_TRIO, 100, "1-2-3", betData);
		if((returnValue & 1) != 1) {
			System.out.println("買い目取得に失敗しました。");
			iPatHelper.Logout();
			return;
		}
		
		//購入
		IpatHelper.ST_BET_DATA[] betDataList = new IpatHelper.ST_BET_DATA[] {betData};
		returnValue = iPatHelper.Bet(betDataList, betDataList.length, 1000);
		if((returnValue & 1) != 1) {
			System.out.println("購入に失敗しました。");
			iPatHelper.Logout();
			return;
		}
		
		//買い目取得(Win5)
		IpatHelper.ST_BET_DATA_WIN5 betDataWin5 = new IpatHelper.ST_BET_DATA_WIN5();
		returnValue = iPatHelper.GetBetInstanceWin5(100, 2021, 3, 14, "1-2-3-4-5", betDataWin5);
		if((returnValue & 1) != 1) {
			System.out.println("買い目取得(Win5)に失敗しました。");
			iPatHelper.Logout();
			return;
		}
		
		//購入(Win5)
		returnValue = iPatHelper.BetWin5(betDataWin5, 1000);
		if((returnValue & 1) != 1) {
			System.out.println("購入(Win5)に失敗しました。");
			iPatHelper.Logout();
			return;
		}

		//ログアウト処理
		iPatHelper.Logout();
	}
}
