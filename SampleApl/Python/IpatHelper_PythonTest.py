from IpatHelper_Python import *

def main():

    #モジュールのイニシャライズ
    returnValue = InitializeModule()
    if returnValue == False:
        return

    #ログイン処理(各自自分のIDに変えてください)
    returnValue = Login('********', '********', '****', '****')
    if (returnValue & 1) != 1:
        UninitializeModule()
        print("ログインに失敗しました。")
        return

    #馬券購入用のインスタンス取得
    betData = ST_BET_DATA()
    returnValue = GetBetInstance(KAISAI_NAKAYAMA, 11, 2020, 12, 27,
                    HOUSHIKI_FORMATION, SHIKIBETSU_TRIO, 100, "9-13-7,3,8,10", betData)
    if (returnValue & 1) != 1:
        Logout()
        UninitializeModule()
        print("馬券購入情報の取得に失敗しました。")
        return

    #馬券購入処理実行
    betDataList = (ST_BET_DATA * 1)()
    betDataList[0] = betData
    returnValue = Bet(betDataList, 1, 0)
    if (returnValue & 1) != 1:
        Logout()
        UninitializeModule()
        print("馬券購入に失敗しました。")
        return

    #馬券購入用のインスタンス取得(WIN5)
    betDataWin5 = ST_BET_DATA_WIN5()
    returnValue = GetBetInstanceWin5(100, 2020, 12, 27, "14-9,13-12-2-1,1,3,5", betDataWin5)
    if (returnValue & 1) != 1:
        Logout()
        UninitializeModule()
        print("馬券購入情報(WIN5)の取得に失敗しました。")
        return

    #馬券購入処理実行(WIN5)
    returnValue = BetWin5(betDataWin5, 0)
    if (returnValue & 1) != 1:
        Logout()
        UninitializeModule()
        print("馬券購入(WIN5)に失敗しました。")
        return

    #ログアウト処理
    Logout()

    #モジュールのファイナライズ
    UninitializeModule()

if __name__ == '__main__':
    main()
    
