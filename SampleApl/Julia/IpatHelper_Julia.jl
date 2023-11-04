if Sys.WORD_SIZE == 64
    LIB_NAME = ".\\x64\\IpatHelper.dll"
else
    LIB_NAME = ".\\x86\\IpatHelper.dll"
end

const KAISAI_SAPPORO = 0
const KAISAI_HAKODATE = 1
const KAISAI_FUKUSHIMA = 2
const KAISAI_NIIGATA = 3
const KAISAI_TOKYO = 4
const KAISAI_NAKAYAMA = 5
const KAISAI_CHUKYO = 6
const KAISAI_KYOTO = 7
const KAISAI_HANSHIN = 8
const KAISAI_KOKURA = 9

const KAISAI_SONODA = 10
const KAISAI_HIMEJI = 11
const KAISAI_NAGOYA = 12
const KAISAI_MONBETSU = 13
const KAISAI_MORIOKA = 14
const KAISAI_MIZUSAWA = 15
const KAISAI_URAWA = 16
const KAISAI_FUNABASHI = 17
const KAISAI_OI = 18
const KAISAI_KAWASAKI = 19
const KAISAI_KASAMATSU = 20
const KAISAI_KANAZAWA = 21
const KAISAI_KOCHI = 22
const KAISAI_SAGA = 23
const KAISAI_LONGCHAMP = 24
const KAISAI_SHATIN = 25
const KAISAI_SANTAANITA = 26
const KAISAI_DEAUVILE = 27
const KAISAI_CHURCHILLDOWNS = 28

const HOUSHIKI_NORMAL = 0
const HOUSHIKI_FORMATION = 1
const HOUSHIKI_BOX = 2

const SHIKIBETSU_WIN = 1
const SHIKIBETSU_PLACE = 2
const SHIKIBETSU_BRACKETQUINELLA = 3
const SHIKIBETSU_QUINELLAPLACE = 4
const SHIKIBETSU_QUINELLA = 5
const SHIKIBETSU_EXACTA = 6
const SHIKIBETSU_TRIO = 7
const SHIKIBETSU_TRIFECTA = 8

const SUCCESS = 1
const UNSUCCESS = 2
const FAILED_CHUOU = 4
const FAILED_CHIHOU = 8
const FAILED_COMMUNICATE_CHUOU = 16
const FAILED_COMMUNICATE_CHIHOU = 32

struct ST_TICKET_DATA_DETAIL_INTERNAL
    DecisionFlag::UInt8
    BetFlag::UInt8
    Kaisai::UInt16
    RaceNo::UInt8
    Week::UInt8
    Youbi::UInt8
    Method::UInt8
    Type::UInt8
    HorseNo1::UInt32
    HorseNo2::UInt32
    HorseNo3::UInt32
    HorseNo4::UInt32
    HorseNo5::UInt32
    Multi::UInt8
end

struct ST_TICKET_DATA_INTERNAL
    DayFlag::UInt8
    ReceiptNo::UInt8
    Hour::UInt8
    Minute::UInt8
    Kingaku::UInt32
    Payout::UInt32
    DetailCount::UInt32
    DetailData::Ptr{ST_TICKET_DATA_DETAIL_INTERNAL}
end

struct ST_PURCHASE_DATA_INTERNAL
    AvailableBetCount::UInt32
    Balance::UInt32
    DayPurchase::UInt32
    DayHaraimodosi::UInt32
    TotalPurchase::UInt32
    TotalHaraimodosi::UInt32
    TicketCount::UInt32
    TicketData::Ptr{ST_TICKET_DATA_INTERNAL}
end

struct ST_BET_DATA_INTERNAL
    Place::UInt16
    RaceNo::UInt8
    Youbi::UInt8
    Kaikata::UInt8
    Shikibetsu::UInt8
    Kingaku::UInt32
    Umaban1::UInt32
    Umaban2::UInt32
    Umaban3::UInt32
    TotalAmount::UInt32
end

struct ST_BET_DATA_WIN5_INTERNAL
    Kingaku::UInt32
    Youbi::UInt8
    Umaban1::UInt32
    Umaban2::UInt32
    Umaban3::UInt32
    Umaban4::UInt32
    Umaban5::UInt32
end

mutable struct ST_TICKET_DATA_DETAIL
    DecisionFlag::UInt8
    BetFlag::UInt8
    Kaisai::UInt16
    RaceNo::UInt8
    Week::UInt8
    Youbi::UInt8
    Method::UInt8
    Type::UInt8
    HorseNo::Array{UInt32, 1}
    Multi::UInt8
end

mutable struct ST_TICKET_DATA
    DayFlag::UInt32
    ReceiptNo::UInt32
    Hour::UInt32
    Minute::UInt32
    Kingaku::UInt32
    Payout::UInt32
    DetailCount::UInt32
    DetailData::Array{ST_TICKET_DATA_DETAIL, 1}

    # コンストラクタ
    ST_TICKET_DATA() = new(0, 0, 0, 0, 0, 0, 0, Array{ST_TICKET_DATA_DETAIL, 1}())
end

mutable struct ST_PURCHASE_DATA
    AvailableBetCount::UInt32
    Balance::UInt32
    DayPurchase::UInt32
    DayHaraimodosi::UInt32
    TotalPurchase::UInt32
    TotalHaraimodosi::UInt32
    TicketCount::UInt32
    TicketData::Array{ST_TICKET_DATA, 1}

    # コンストラクタ
    ST_PURCHASE_DATA() = new(0, 0, 0, 0, 0, 0, 0, Array{ST_TICKET_DATA, 1}())
end

mutable struct ST_BET_DATA
    Place::UInt16
    RaceNo::UInt8
    Youbi::UInt8
    Kaikata::UInt8
    Shikibetsu::UInt8
    Kingaku::UInt32
    Umaban::Array{UInt32, 1}
    TotalAmount::UInt32

    # コンストラクタ
    ST_BET_DATA() = new(0, 0, 0, 0, 0, 0, Array{UInt32, 1}(), 0)
end

mutable struct ST_BET_DATA_WIN5
    Kingaku::UInt32
    Youbi::UInt8
    Umaban::Array{UInt32, 1}

    # コンストラクタ
    ST_BET_DATA_WIN5() = new(0, 0, Array{UInt32, 1}())
end

"""
Login
---
ログイン処理実行
"""
function Login(i_net_id::String, id::String, password::String, p_ars::String)::Int32

    # デリゲートを生成する(ログイン関数)
    return ccall((:Login, LIB_NAME), Int32, (Cstring, Cstring, Cstring, Cstring, ), i_net_id, id, password, p_ars,)

end

"""
Logout
---
ログアウト処理実行
"""
function Logout()::Int32

    # デリゲートを生成する(ログアウト関数)
    return ccall((:Logout, LIB_NAME), Int32, (),)
    
end

"""
Deposit
---
入金処理実行
"""
function Deposit(depositValue::Int64)::Int32

    # デリゲートを生成する(入金関数)
    return ccall((:Deposit, LIB_NAME), Int32, (UInt16, ), depositValue, )
    
end

"""
Withdraw
---
出金処理実行
"""
function Withdraw()::Int32

    # デリゲートを生成する(出金関数)
    return ccall((:Withdraw, LIB_NAME), Int32, (),)
    
end

"""
GetPurchaseData
---
購入状況取得処理実行
"""
function GetPurchaseData(purchase_data::ST_PURCHASE_DATA)::Int32

    # デリゲートを生成する(購入状況取得関数)
    get_purchase_data = (p_purcharse_data) -> ccall((:GetPurchaseData, LIB_NAME), Int32, (Ptr{ST_PURCHASE_DATA_INTERNAL},), p_purcharse_data,)

    # デリゲートを生成する(購入情報解放関数)
    release_purchase_data = (purchase_data) -> ccall((:ReleasePurchaseData, LIB_NAME), Cvoid, (ST_PURCHASE_DATA_INTERNAL,), purchase_data,)

    # マーシャリング用の構造体を生成
    array_purcharse_data_internal = [ST_PURCHASE_DATA_INTERNAL(0, 0, 0, 0, 0, 0, 0, C_NULL)]

    # ポインターに変換する
    p_purcharse_data = Base.unsafe_convert(Ptr{ST_PURCHASE_DATA_INTERNAL}, array_purcharse_data_internal)

    # 購入状況を取得する
    result = get_purchase_data(p_purcharse_data)

    # 配列の先頭要素を抜き出す
    purcharse_data_internal = array_purcharse_data_internal[1]

    if (result & 1) != 1
        release_purchase_data(purcharse_data_internal)
        return result
    end

    # チケットデータ以外を引数に設定する
    purchase_data.AvailableBetCount = purcharse_data_internal.AvailableBetCount
    purchase_data.Balance = purcharse_data_internal.Balance
    purchase_data.DayHaraimodosi = purcharse_data_internal.DayHaraimodosi
    purchase_data.DayPurchase = purcharse_data_internal.DayPurchase
    purchase_data.TicketCount = purcharse_data_internal.TicketCount
    purchase_data.TotalHaraimodosi = purcharse_data_internal.TotalHaraimodosi
    purchase_data.TotalPurchase = purcharse_data_internal.TotalPurchase

    # チケットデータをポインタから配列に変換する
    array_ticket_data_internal = unsafe_wrap(Array{ST_TICKET_DATA_INTERNAL}, 
        purcharse_data_internal.TicketData, purcharse_data_internal.TicketCount, own=false)

    # チケット情報を解析する
    array_ticket_data = Array{ST_TICKET_DATA, 1}()
    for ticket_data_internal in array_ticket_data_internal

        # 格納用のチケット情報を生成する
        ticket_data = ST_TICKET_DATA()

        # チケット情報を格納する
        ticket_data.DayFlag = ticket_data_internal.DayFlag
        ticket_data.ReceiptNo = ticket_data_internal.ReceiptNo
        ticket_data.Hour = ticket_data_internal.Hour
        ticket_data.Minute = ticket_data_internal.Minute
        ticket_data.Kingaku = ticket_data_internal.Kingaku
        ticket_data.Payout = ticket_data_internal.Payout
        ticket_data.DetailCount = ticket_data_internal.DetailCount

        # 詳細データをポインタから配列に変換する
        array_detail_data_internal = unsafe_wrap(Array{ST_TICKET_DATA_DETAIL_INTERNAL},
         ticket_data_internal.DetailData, ticket_data_internal.DetailCount, own=false)
        
        # 詳細情報を解析する
        array_detail_data = Array{ST_TICKET_DATA_DETAIL, 1}()
        for detail_data_internal in array_detail_data_internal

            # 格納用の詳細情報を生成する
            detail_data = ST_TICKET_DATA_DETAIL(0, 0, 0, 0, 0, 0, 0, 0, Array{Int32, 1}(), 0)

            # 詳細情報を格納する
            detail_data.DecisionFlag = detail_data_internal.DecisionFlag
            detail_data.BetFlag = detail_data_internal.BetFlag
            detail_data.Kaisai = detail_data_internal.Kaisai
            detail_data.RaceNo = detail_data_internal.RaceNo
            detail_data.Week = detail_data_internal.Week
            detail_data.Youbi = detail_data_internal.Youbi
            detail_data.Method = detail_data_internal.Method
            detail_data.Type = detail_data_internal.Type
            push!(detail_data.HorseNo, detail_data_internal.HorseNo1)
            push!(detail_data.HorseNo, detail_data_internal.HorseNo2)
            push!(detail_data.HorseNo, detail_data_internal.HorseNo3)
            push!(detail_data.HorseNo, detail_data_internal.HorseNo4)
            push!(detail_data.HorseNo, detail_data_internal.HorseNo5)
            detail_data.Multi = detail_data_internal.Multi

            push!(array_detail_data, detail_data)
        end

        # チケット情報に詳細情報を設定する
        ticket_data.DetailData = array_detail_data

        # チケット情報をリストに追加する
        push!(array_ticket_data, ticket_data)
    end

    # 引数に値を設定する
    purchase_data.TicketData = array_ticket_data

    # 購入情報を解放する
    release_purchase_data(purcharse_data_internal)

    return result

end

"""
GetBetInstance
---
馬券購入用インスタンス取得処理
"""
function GetBetInstance(kaisai::Int64, race_no::Int64, year::Int64, month::Int64,
     day::Int64, houshiki::Int64, shikibetsu::Int64, kingaku::Int64, kaime::String, bet_data::ST_BET_DATA)::Int32

    # デリゲートを生成する(馬券購入用インスタンス取得関数)
    get_bet_instance = (kaisai, race_no, year, month, day, houshiki, shikibetsu, kingaku, kaime, p_bet_instance,) -> ccall((:GetBetInstance, LIB_NAME), 
        Int32, (UInt16, UInt8, UInt16, UInt8, UInt8, UInt8, UInt8, UInt32, Cstring,
        Ptr{ST_BET_DATA_INTERNAL}, ), kaisai, race_no, year, month, day, houshiki, shikibetsu, kingaku, kaime, p_bet_instance,)

    # マーシャリング用の構造体を生成
    array_bet_instance = [ST_BET_DATA_INTERNAL(0, 0, 0, 0, 0, 0, 0, 0, 0, 0)]

    # ポインターに変換する
    p_bet_instance = Base.unsafe_convert(Ptr{ST_BET_DATA_INTERNAL}, array_bet_instance)

    # 馬券購入用インスタンス取得
    result = get_bet_instance(kaisai, race_no, year, 
        month, day, houshiki, shikibetsu, kingaku, kaime, p_bet_instance)
    if (result & 1) != 1
        return result
    end

    # データをポインタから配列に変換する
    array_bet_instance = unsafe_wrap(Array{ST_BET_DATA_INTERNAL}, p_bet_instance, 1, own=false)

    # 先頭の要素を取り出す
    bet_data_internal = array_bet_instance[1]

    # 引数に値を設定する
    bet_data.Kaikata = bet_data_internal.Kaikata
    bet_data.Kingaku = bet_data_internal.Kingaku
    bet_data.Place = bet_data_internal.Place
    bet_data.RaceNo =bet_data_internal.RaceNo
    bet_data.Shikibetsu = bet_data_internal.Shikibetsu
    bet_data.TotalAmount = bet_data_internal.TotalAmount
    push!(bet_data.Umaban, bet_data_internal.Umaban1)
    push!(bet_data.Umaban, bet_data_internal.Umaban2)
    push!(bet_data.Umaban, bet_data_internal.Umaban3)
    bet_data.Youbi = bet_data_internal.Youbi

    return result
    
end

"""
Bet
---
通常投票処理
"""
function Bet(bet_data_list::Array{ST_BET_DATA, 1}, wait_time::Int64)::Int32

    # デリゲートを生成する(通常投票関数)
    bet = (bet_data_list, length, wait_time, ) -> ccall((:Bet, LIB_NAME), Int32, (Ptr{ST_BET_DATA_INTERNAL},
        UInt16, UInt16, ), bet_data_list, length, wait_time, )

    # 構造体配列をマーシャリング用構造体配列に変換する
    bet_data_internal_list = Array{ST_BET_DATA_INTERNAL, 1}()
    for elem in bet_data_list

        push!(bet_data_internal_list, ST_BET_DATA_INTERNAL(elem.Place, elem.RaceNo, 
            elem.Youbi, elem.Kaikata, elem.Shikibetsu, elem.Kingaku, elem.Umaban[1], 
            elem.Umaban[2], elem.Umaban[3], elem.TotalAmount))

    end

    # デリゲートを生成する(通常投票関数)
    return bet(bet_data_internal_list, length(bet_data_list), wait_time)
    
end

"""
GetBetInstanceWin5
---
馬券(WIN5)購入用インスタンス取得処理
"""
function GetBetInstanceWin5(kingaku::Int64, year::Int64, month::Int64, 
            day::Int64, kaime::String, bet_data::ST_BET_DATA_WIN5)::Int32

    # デリゲートを生成する(馬券購入用インスタンス取得関数)
    get_bet_instance = (kingaku, year, month, day, kaime, p_bet_instance, ) -> ccall((:GetBetInstanceWin5, LIB_NAME), Int32, (UInt32, UInt16,
                        UInt8, UInt8, Cstring, Ptr{ST_BET_DATA_WIN5_INTERNAL}, ), kingaku, year, month, day, kaime, p_bet_instance,)

    # マーシャリング用の構造体を生成
    array_bet_instance = [ST_BET_DATA_WIN5_INTERNAL(0, 0, 0, 0, 0, 0, 0)]

    # ポインターに変換する
    p_bet_instance = Base.unsafe_convert(Ptr{ST_BET_DATA_WIN5_INTERNAL}, array_bet_instance)

    # 馬券購入用インスタンス取得
    result = get_bet_instance(kingaku, year, month, day, kaime, p_bet_instance)
    if (result & 1) != 1
        return result
    end

    # データをポインタから配列に変換する
    array_bet_instance = unsafe_wrap(Array{ST_BET_DATA_WIN5_INTERNAL}, p_bet_instance, 1, own=false)

    # 先頭の要素を取り出す
    bet_data_internal = array_bet_instance[1]

    # 引数に値を設定する
    bet_data.Kingaku = bet_data_internal.Kingaku
    bet_data.Youbi = bet_data_internal.Youbi
    push!(bet_data.Umaban, bet_data_internal.Umaban1)
    push!(bet_data.Umaban, bet_data_internal.Umaban2)
    push!(bet_data.Umaban, bet_data_internal.Umaban3)
    push!(bet_data.Umaban, bet_data_internal.Umaban4)
    push!(bet_data.Umaban, bet_data_internal.Umaban5)

    return result
    
end

"""
BetWin5
---
馬券購入処理実行(WIN5)
"""
function BetWin5(bet_data::ST_BET_DATA_WIN5, wait_time::Int64)::Int32

    # デリゲートを生成する(WIN5投票関数)
    bet = (bet_data, wait_time, ) -> ccall((:BetWin5, LIB_NAME), Int32, (ST_BET_DATA_WIN5_INTERNAL, UInt16, ), bet_data, wait_time, )

    # 構造体をマーシャリング用構造体に変換する
    bet_data_internal = ST_BET_DATA_WIN5_INTERNAL(bet_data.Kingaku, bet_data.Youbi, 
        bet_data.Umaban[1], bet_data.Umaban[2], bet_data.Umaban[3], bet_data.Umaban[4], bet_data.Umaban[5])

    return bet(bet_data_internal, wait_time)
    
end

"""
SetAutoDepositFlag
---
自動入金フラグ設定
"""
function SetAutoDepositFlag(enable::Bool, deposit_value::Int32, confirm_timeout::Int32)::Int32

    # デリゲートを生成する(自動入金フラグ設定関数)
    return ccall((:SetAutoDepositFlag, LIB_NAME), Int32, (Bool, UInt32, UInt16, ), enable, deposit_value, confirm_timeout, )
    
end