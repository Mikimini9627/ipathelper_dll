using System;

namespace IpatHelper_DotNetTestApl
{
    class Program
    {
        static void Main()
        {
            //ログイン処理(各自自分のIDに変えてください)
            uint returnValue = IpatHelper.Login("********", "********", "****", "****");
            if ((returnValue & 1) != 1)
            {
                Console.WriteLine("Login Error");
                return;
            }

            //馬券購入用のインスタンス取得
            returnValue = IpatHelper.GetBetInstance(IpatHelper.Kaisai.NAKAYAMA, 11, DateTime.Parse("2020/12/27"),
                IpatHelper.Houshiki.FORMATION, IpatHelper.Shikibetsu.TRIO, 100, "9-13-7,3,8,10", out IpatHelper.ST_BET_DATA objBetData);
            if ((returnValue & 1) != 1)
            {
                Console.WriteLine("Get Bet Instance Error");
                IpatHelper.Logout();
                return;
            }

            //馬券購入処理実行
            returnValue = IpatHelper.Bet(new() { objBetData });
            if ((returnValue & 1) != 1)
            {
                Console.WriteLine("Bet Error");
                IpatHelper.Logout();
                return;
            }

            //馬券購入用のインスタンス取得(WIN5)
            returnValue = IpatHelper.GetBetInstanceWin5(100, DateTime.Parse("2020/12/27"), 
                "14-9,13-12-2-1,3,4,5", out IpatHelper.ST_BET_DATA_WIN5 objBetDataWin5);
            if ((returnValue & 1) != 1)
            {
                Console.WriteLine("Get Bet Instance(Win5) Error");
                IpatHelper.Logout();
                return;
            }

            //馬券購入処理実行(WIN5)
            returnValue = IpatHelper.BetWin5(objBetDataWin5);
            if ((returnValue & 1) != 1)
            {
                Console.WriteLine("Bet(Win5) Error");
                IpatHelper.Logout();
                return;
            }

            //ログアウト処理実行
            IpatHelper.Logout();
        }
    }
}
