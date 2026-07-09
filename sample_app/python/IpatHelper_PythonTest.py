from IpatHelper_Python import *

def main():

    try:
        # モジュールのイニシャライズ
        returnValue = init()
        if returnValue == False:
            return

        # ログイン処理(各自自分のIDに変えてください)
        returnValue = login('********', '********', '****', '****')
        if (returnValue & 1) != 1:
            print("ログインに失敗しました。")
            return

        # オッズ取得(馬連・中央競馬/地方競馬に対応)。解放はラッパー内部で実施される
        oddsData = ST_ODDS_DATA()
        returnValue = get_odds(KAISAI_TOKYO, 11, SHIKIBETSU_QUINELLA, oddsData)
        if (returnValue & 1) == 1:
            print("オッズ更新時刻: " + oddsData.OddsTime + " / 明細数: " + str(oddsData.DetailCount))
            for detail in oddsData.OddsDetail:
                oddsText = "{:.1f}".format(detail.Odds / 10.0) if detail.Status == 0 else ("status=" + str(detail.Status))
                print("  " + str(detail.Horse1) + "-" + str(detail.Horse2) + " : " + oddsText)

        # 出馬表取得(中央競馬/地方競馬に対応)。解放はラッパー内部で実施される
        raceCard = ST_RACECARD_DATA()
        returnValue = get_race_card(KAISAI_TOKYO, 11, raceCard)
        if (returnValue & 1) == 1:
            print("オッズ更新時刻: " + raceCard.OddsTime + " / 出走頭数: " + str(raceCard.EntryCount))
            for entry in raceCard.EntryData:
                name = entry.HorseName.decode('utf-8')
                sex = entry.Sex.decode('utf-8')
                jockey = entry.JockeyName.decode('utf-8')
                win = "{:.1f}".format(entry.WinOdds / 10.0) if entry.WinOddsStatus == 0 else "-"
                print("  {:2d}番 {} {}{} 斤量{:.1f} 騎手:{} 単勝:{} 人気:{}".format(
                    entry.Umaban, name, sex, entry.Age, entry.Burden / 10.0, jockey, win, entry.WinPopular))

        # 馬券購入用のインスタンス取得
        betData = ST_BET_DATA()
        returnValue = get_bet_instance(KAISAI_NAKAYAMA, 11, 2020, 12, 27,
                        HOUSHIKI_FORMATION, SHIKIBETSU_TRIO, 100, "1,9-2,3,13-7,3,8,10", betData)
        if (returnValue & 1) != 1:
            print("馬券購入情報の取得に失敗しました。")
            return

        # 馬券購入処理実行
        betDataList = (ST_BET_DATA * 1)()
        betDataList[0] = betData
        returnValue = bet(betDataList, 1, 0)
        if (returnValue & 1) != 1:
            print("馬券購入に失敗しました。")
            return

        # 馬券購入用のインスタンス取得(WIN5)
        betDataWin5 = ST_BET_DATA_WIN5()
        returnValue = get_bet_instance_win5(100, 2020, 12, 27, "1,14-9,13-12-2-1,1,3,5", betDataWin5)
        if (returnValue & 1) != 1:
            print("馬券購入情報(WIN5)の取得に失敗しました。")
            return

        # 馬券購入処理実行(WIN5)
        returnValue = bet_win5(betDataWin5, 0)
        if (returnValue & 1) != 1:
            print("馬券購入(WIN5)に失敗しました。")
            return
    
    finally:

        # ログアウト処理
        logout()

        # モジュールのファイナライズ
        uninit()

if __name__ == '__main__':
    main()
    
