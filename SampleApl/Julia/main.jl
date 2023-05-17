include(".\\IpatHelper_Julia.jl")

#ログイン処理(各自自分のIDに変えてください)
result = Login("********", "********", "****", "****")
if (result & 1) != 1
    println("ログインに失敗しました。")
    exit()
end

# 馬券購入用のインスタンス取得
bet_data = ST_BET_DATA()
result = GetBetInstance(KAISAI_NIIGATA, 11, 2022, 8, 14,
                HOUSHIKI_NORMAL, SHIKIBETSU_PLACE, 100, "1", bet_data)
if (result & 1) != 1
    Logout()
    println("馬券購入情報の取得に失敗しました。")
    exit()
end

# 馬券購入処理実行
bet_data_list = [bet_data] 
result = Bet(bet_data_list, 0)
if (result & 1) != 1
    Logout()
    println("馬券購入に失敗しました。")
    exit()
end

# 馬券購入用のインスタンス取得(WIN5)
bet_data_win5 = ST_BET_DATA_WIN5()
result = GetBetInstanceWin5(100, 2022, 8, 14, "1-1-1-1-1", bet_data_win5)
if (result & 1) != 1
    Logout()
    println("馬券購入情報(WIN5)の取得に失敗しました。")
    exit()
end

# 馬券購入処理実行(WIN5)
result = BetWin5(bet_data_win5, 0)
if (result & 1) != 1
    Logout()
    println("馬券購入(WIN5)に失敗しました。")
    exit()
end

# ログアウト処理
Logout()