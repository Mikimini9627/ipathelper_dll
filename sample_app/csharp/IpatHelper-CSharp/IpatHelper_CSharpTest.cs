using System;

namespace IpatHelper_DotNetSampleApl
{
    class Program
    {
        static void Main()
        {
            //ログイン処理(各自自分のIDに変えてください)
            uint returnValue = IpatHelper.Login("********", "********", "****", "****");
            if (!IsSuccess(returnValue))
            {
                //投票受付時間外またはメンテナンス中は即座に再試行しても必ず失敗する
                bool outOfService = (returnValue & (uint)IpatHelper.RETURN_VALUE.FAILED_OUT_OF_SERVICE) != 0;
                Console.WriteLine(outOfService ? "Login Error (out of service)" : "Login Error");
                return;
            }

            //お知らせ取得。解放はラッパー内部で実施される
            returnValue = IpatHelper.GetNotice(out IpatHelper.ST_NOTICE_DATA notice);
            if (IsSuccess(returnValue))
            {
                if (!string.IsNullOrEmpty(notice.message))
                {
                    Console.WriteLine($"Notice: {notice.message}");
                }
                foreach (var item in notice.items)
                {
                    Console.WriteLine($"  {item.date} {item.title} {item.url}");
                }
            }

            //オッズ取得(馬連・中央競馬/地方競馬/海外競馬に対応)。解放はラッパー内部で実施される
            returnValue = IpatHelper.GetOdds(IpatHelper.Kaisai.TOKYO, 11, IpatHelper.Shikibetsu.QUINELLA, out IpatHelper.ST_ODDS_DATA oddsData);
            if (IsSuccess(returnValue))
            {
                Console.WriteLine($"Odds Time: {oddsData.oddsTime} / Count: {oddsData.detailCount}");
                foreach (var detail in oddsData.oddsDetail)
                {
                    string oddsText = detail.status == 0 ? (detail.odds / 10.0).ToString("0.0") : $"status={detail.status}";
                    Console.WriteLine($"  {detail.horse1}-{detail.horse2} : {oddsText}");
                }
            }

            //出馬表取得(中央競馬/地方競馬/海外競馬に対応)。解放はラッパー内部で実施される
            returnValue = IpatHelper.GetRaceCard(IpatHelper.Kaisai.TOKYO, 11, out IpatHelper.ST_RACECARD_DATA raceCard);
            if (IsSuccess(returnValue))
            {
                Console.WriteLine($"Race Name: {raceCard.raceName}");
                Console.WriteLine($"Deadline: {raceCard.deadline} / Status: {raceCard.raceStatus}");
                Console.WriteLine($"Odds Time: {raceCard.oddsTime} / Entries: {raceCard.entryCount}");
                foreach (var entry in raceCard.entries)
                {
                    string winText = entry.winOddsStatus == 0 ? (entry.winOdds / 10.0).ToString("0.0") : "-";
                    Console.WriteLine($"  {entry.umaban,2} {entry.horseName} {entry.sex}{entry.age} " +
                                      $"burden={entry.burden / 10.0:0.0} jockey={entry.jockeyName} " +
                                      $"win={winText} popular={entry.winPopular}");
                }
            }

            //馬券購入用のインスタンス取得
            returnValue = IpatHelper.GetBetInstance(IpatHelper.Kaisai.NAKAYAMA, 11, DateTime.Parse("2020/12/27"),
                IpatHelper.Houshiki.FORMATION, IpatHelper.Shikibetsu.TRIO, 100, "9-13-7,3,8,10", out IpatHelper.ST_BET_DATA objBetData);
            if (!IsSuccess(returnValue))
            {
                Console.WriteLine("Get Bet Instance Error");
                IpatHelper.Logout();
                return;
            }

            //馬券購入処理実行
            returnValue = IpatHelper.Bet(new() { objBetData });
            if (!IsSuccess(returnValue))
            {
                Console.WriteLine("Bet Error");
                IpatHelper.Logout();
                return;
            }

            //馬券購入用のインスタンス取得(WIN5)
            returnValue = IpatHelper.GetBetInstanceWin5(100, DateTime.Parse("2020/12/27"),
                "14-9,13-12-2-1,3,4,5", out IpatHelper.ST_BET_DATA_WIN5 objBetDataWin5);
            if (!IsSuccess(returnValue))
            {
                Console.WriteLine("Get Bet Instance(Win5) Error");
                IpatHelper.Logout();
                return;
            }

            //馬券購入処理実行(WIN5)
            returnValue = IpatHelper.BetWin5(objBetDataWin5);
            if (!IsSuccess(returnValue))
            {
                Console.WriteLine("Bet(Win5) Error");
                IpatHelper.Logout();
                return;
            }

            //ログアウト処理実行
            IpatHelper.Logout();
        }

        //戻り値は RETURN_VALUE のビットフラグ。SUCCESS が立っているかで成否を判定する
        private static bool IsSuccess(uint returnValue)
        {
            return (returnValue & (uint)IpatHelper.RETURN_VALUE.SUCCESS) != 0;
        }
    }
}
