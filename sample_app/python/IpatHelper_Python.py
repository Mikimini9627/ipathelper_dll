from ctypes import *
from ctypes import wintypes
from pathlib import *
from sys import *

global lib

KAISAI_SAPPORO = 0
KAISAI_HAKODATE = 1
KAISAI_FUKUSHIMA = 2
KAISAI_NIIGATA = 3
KAISAI_TOKYO = 4
KAISAI_NAKAYAMA = 5
KAISAI_CHUKYO = 6
KAISAI_KYOTO = 7
KAISAI_HANSHIN = 8
KAISAI_KOKURA = 9

KAISAI_SONODA = 10
KAISAI_HIMEJI = 11
KAISAI_NAGOYA = 12
KAISAI_MONBETSU	= 13
KAISAI_MORIOKA = 14
KAISAI_MIZUSAWA	= 15
KAISAI_URAWA = 16
KAISAI_FUNABASHI = 17
KAISAI_OI = 18
KAISAI_KAWASAKI	= 19
KAISAI_KASAMATSU = 20
KAISAI_KANAZAWA	= 21
KAISAI_KOCHI = 22
KAISAI_SAGA = 23
KAISAI_LONGCHAMP = 24
KAISAI_SHATIN = 25
KAISAI_SANTAANITA = 26
KAISAI_DEAUVILE = 27
KAISAI_CHURCHILLDOWNS = 28
KAISAI_ABDULAZIZ = 29
KAISAI_ASCOT = 30

HOUSHIKI_NORMAL = 0
HOUSHIKI_FORMATION = 1
HOUSHIKI_BOX = 2
HOUSHIKI_WHEEL_1ST = 3          # 軸1頭ながし(1着流し)/馬連・ワイド・枠連/三連複軸1頭/三連単1着。買い目「軸-相手」
HOUSHIKI_WHEEL_2ND = 4          # 2着ながし(馬単・三連単)。買い目「軸-相手」
HOUSHIKI_WHEEL_3RD = 5          # 3着ながし(三連単)。買い目「軸-相手」
HOUSHIKI_WHEEL_1ST_2ND = 6      # 軸2頭ながし(三連複)/1・2着ながし(三連単)
HOUSHIKI_WHEEL_1ST_3RD = 7      # 1・3着ながし(三連単)。買い目「1着軸-相手-3着軸」
HOUSHIKI_WHEEL_2ND_3RD = 8      # 2・3着ながし(三連単)。買い目「相手-2着軸-3着軸」
HOUSHIKI_WHEEL_MULTI_AXIS1 = 9  # 軸1頭ながしマルチ(馬単・三連単)。買い目「軸-相手」
HOUSHIKI_WHEEL_MULTI_AXIS2 = 10 # 軸2頭ながしマルチ(三連単)。買い目「軸-軸-相手」

SHIKIBETSU_WIN = 1
SHIKIBETSU_PLACE = 	2
SHIKIBETSU_BRACKETQUINELLA = 3
SHIKIBETSU_QUINELLA	= 4
SHIKIBETSU_QUINELLAPLACE = 5
SHIKIBETSU_EXACTA = 6
SHIKIBETSU_TRIO	= 7
SHIKIBETSU_TRIFECTA	= 8

ODDS_STATUS_NORMAL = 0
ODDS_STATUS_CANCEL = 1
ODDS_STATUS_UNACQUIRED = 2

# ST_RACECARD_DATA.RaceStatus の値
# UNKNOWN が 0 でないのは、0 が「発売中」でありゼロ初期化と区別する必要があるため。
RACE_STATUS_ON_SALE = 0         # 発売中
RACE_STATUS_CLOSED = 1          # 発売終了
RACE_STATUS_CANCELED = 2        # 発売中止
RACE_STATUS_BEFORE_SALE = 3     # 発売前
RACE_STATUS_UNKNOWN = 0xFF      # 取得できなかった

DAYTYPE_TODAY = 1
DAYTYPE_BEFORE = 2

BETFLAG_NORMAL = 1
BETFLAG_WIN5 = 2
BETFLAG_INTERNAL = 3

DECISIONFLAG_DEFAULT = 1
DECISIONFLAG_NORMAL = 2
DECISIONFLAG_DEADLINE = 3
DECISIONFLAG_CANCEL = 4
DECISIONFLAG_FLATMATESCANCEL = 5
DECISIONFLAG_HIT = 6
DECISIONFLAG_MISS = 7
DECISIONFLAG_BACK = 8
DECISIONFLAG_PARTCANCEL = 10
DECISIONFLAG_INVALID = 11
DECISIONFLAG_SALECANCEL = 12

WEEKDAY_SUNDAY = 1
WEEKDAY_MONDAY = 2
WEEKDAY_TUESDAY = 3
WEEKDAY_WEDNESDAY = 4
WEEKDAY_THURSDAY = 5
WEEKDAY_FRIDAY = 6
WEEKDAY_SATURDAY = 7

SUCCESS = 1
UNSUCCESS = 2
FAILED_CHUOU = 4
FAILED_CHIHOU = 8
FAILED_COMMUNICATE_CHUOU = 16
FAILED_COMMUNICATE_CHIHOU = 32
# サービス時間外(FAILED_CHUOU / FAILED_CHIHOU と併せて立つ)。
# 投票受付時間外が最も多い原因で、即座に再試行しても必ず失敗する。
FAILED_OUT_OF_SERVICE = 64

DEFAULT_RETRY_COUNT = 10
DEFAULT_WAIT_TIME = 1000
DEFAULT_CONFIRM_TIMEOUT = 10000

WIN5_AUTO_SELECT = 2    # WIN5 セレクト: 軸馬を指定し、残りはサーバが選ぶ
WIN5_AUTO_RANDOM = 3    # WIN5 ランダム: すべてサーバが選ぶ

LOG_LEVEL_TRACE = 0     # 詳細トレース。入出金失敗時の応答本文の抜粋はこのレベルのみ
LOG_LEVEL_INFO = 1      # 情報(既定)
LOG_LEVEL_WARN = 2      # 警告
LOG_LEVEL_ERROR = 3     # エラー。失敗した段階・画面ID・タイトルはこのレベル

# ログコールバックの型。DLL 側は __cdecl のため CFUNCTYPE(WINFUNCTYPE ではない)。
LOG_CALLBACK = CFUNCTYPE(None, c_int, c_char_p)

# ネイティブへ渡したコールバックは GC されるとクラッシュするため参照を保持する
_logCallbackRef = None
_logHandler = None

class ST_TICKET_DATA:
    def __init__(self):
        self.DayFlag = 0
        self.ReceiptNo = 0
        self.Hour = 0
        self.Minute = 0
        self.Kingaku = 0
        self.Payout = 0
        self.DetailCount = 0
        self.DetailData = []

class ST_PURCHASE_DATA:
    def __init__(self):
        self.AvailableBetCount = 0
        self.Balance = 0
        self.DayPurchase = 0
        self.DayHaraimodosi = 0
        self.TotalPurchase = 0
        self.TotalHaraimodosi = 0
        self.TicketCount = 0
        self.TicketData = []

class ST_ODDS_DATA:
    def __init__(self):
        self.Place = 0
        self.RaceNo = 0
        self.OddsTime = ""
        self.DetailCount = 0
        self.OddsDetail = []

class ST_RACECARD_DATA:
    def __init__(self):
        self.Place = 0
        self.RaceNo = 0
        self.OddsTime = ""
        self.EntryCount = 0
        self.EntryData = []
        self.RaceName = ""
        self.Deadline = ""                       # 発売締切時刻 "HH:MM"(取得不可時は空文字)
        self.RaceStatus = RACE_STATUS_UNKNOWN    # 発売状態(RACE_STATUS_*)

class ST_NOTICE_ITEM:
    def __init__(self):
        self.Title = ""     # タイトル
        self.Date = ""      # 日付テキスト
        self.Url = ""       # リンクURL
        self.Icon = ""      # アイコンファイル名
        self.Color = ""     # 日付表示色

class ST_NOTICE_DATA:
    def __init__(self):
        self.Message = ""   # 強制表示お知らせ本文(無い場合は空文字)
        self.NoticeNo = ""  # お知らせ番号
        self.NoticeType = ""# お知らせ種別
        self.ItemCount = 0  # お知らせ一覧の件数
        self.ItemData = []  # お知らせ一覧(ST_NOTICE_ITEM のリスト)

#構造体マーシャリング用クラス
class ST_TICKET_DATA_DETAIL(Structure):
    _fields_ = [("DecisionFlag", c_byte), ("BetFlag", c_byte), ("Kaisai", c_ushort), ("RaceNo", c_byte), \
        ("Week", c_byte), ("Method", c_byte), ("Type", c_byte), ("HorseNo1", c_uint), 
        ("HorseNo2", c_uint), ("HorseNo3", c_uint), ("HorseNo4", c_uint), ("HorseNo5", c_uint), ("Multi", c_byte)]

class ST_TICKET_DATA_INTERNAL(Structure):
    _fields_ = [("DayFlag", c_byte), ("ReceiptNo", c_byte), ("Hour", c_byte), ("Minute", c_byte), \
        ("Kingaku", c_uint), ("Payout", c_uint), ("DetailCount", c_uint), ("DetailData", c_void_p)]

class ST_PURCHASE_DATA_INTERNAL(Structure):
    _fields_ = [("AvailableBetCount", c_ushort), ("Balance", c_uint), ("DayPurchase", c_uint),\
         ("DayHaraimodosi", c_uint), ("TotalPurchase", c_uint), ("TotalHaraimodosi", c_uint), ("TicketCount", c_uint), ("TicketData", c_void_p)]

class ST_BET_DATA(Structure):
    _fields_ = [("Place", c_ushort), ("RaceNo", c_byte), ("Youbi", c_byte), ("Kaikata", c_byte),\
         ("Shikibetsu", c_byte), ("Kingaku", c_uint), ("Umaban", c_uint * 3), ("TotalAmount", c_long),\
         ("Multi", c_byte)]  # Multi: マルチかどうか(0:通常 1:マルチ)

class ST_BET_DATA_WIN5(Structure):
    _fields_ = [("Kingaku", c_uint), ("Youbi", c_byte), ("Umaban", c_uint * 5)]

class ST_ODDS_DETAIL(Structure):
    _fields_ = [("Type", c_byte), ("Horse1", c_byte), ("Horse2", c_byte), ("Horse3", c_byte), \
        ("Status", c_byte), ("Odds", c_uint), ("OddsHigh", c_uint)]

class ST_ODDS_DATA_INTERNAL(Structure):
    _fields_ = [("Place", c_ushort), ("RaceNo", c_byte), ("OddsTime", c_char * 8), \
        ("DetailCount", c_uint), ("DetailData", c_void_p)]

class ST_ENTRY_DETAIL(Structure):
    # 文字列フィールド(HorseName/Sex/JockeyName/TrainerName)はUTF-8のbytes。
    # 利用時は .decode('utf-8') で文字列化する。
    _fields_ = [("Wakuban", c_byte), ("Umaban", c_byte), \
        ("HorseName", c_char * 64), ("Sex", c_char * 8), ("Age", c_byte), \
        ("WeightStatus", c_byte), ("Weight", c_ushort), \
        ("WeightDiffCode", c_byte), ("WeightDiff", c_ushort), ("Apprentice", c_byte), \
        ("JockeyName", c_char * 48), ("Burden", c_ushort), ("TrainerName", c_char * 48), \
        ("WinPopular", c_ushort), ("WinOddsStatus", c_byte), ("WinOdds", c_uint), \
        ("PlaceOddsStatus", c_byte), ("PlaceOddsLow", c_uint), ("PlaceOddsHigh", c_uint)]

class ST_RACECARD_DATA_INTERNAL(Structure):
    # ネイティブ側が直接書き込む領域のため、順序・型が DLL 側の ST_RACECARD_DATA と
    # 一致していないとメモリ破壊になる。
    _fields_ = [("Place", c_ushort), ("RaceNo", c_byte), ("OddsTime", c_char * 8), \
        ("EntryCount", c_uint), ("EntryData", c_void_p), ("RaceName", c_char * 128), \
        ("Deadline", c_char * 8), ("RaceStatus", c_ubyte)]

class ST_NOTICE_ITEM_INTERNAL(Structure):
    _fields_ = [("Title", c_char * 512), ("Date", c_char * 64), ("Url", c_char * 1024), \
        ("Icon", c_char * 128), ("Color", c_char * 32)]

class ST_NOTICE_DATA_INTERNAL(Structure):
    # ネイティブ側が直接書き込む領域のため、順序・型が DLL 側の ST_NOTICE_DATA と
    # 一致していないとメモリ破壊になる。
    _fields_ = [("Message", c_char * 2048), ("NoticeNo", c_char * 16), \
        ("NoticeType", c_char * 8), ("ItemCount", c_uint), ("ItemData", c_void_p)]

def init():
    '''
        モジュールのイニシャライズ
    '''

    global lib

    #Get the directory where the running file resides
    dirName = str(Path(__file__).parent)

    #Check dll exists
    if maxsize > 2 ** 32:
        libPath = Path(dirName + "\\x64\\IpatHelper.dll")
    else:
        libPath = Path(dirName + "\\x86\\IpatHelper.dll")

    if libPath.exists() == False:
        return False

    # 公開関数はすべて __cdecl。WinDLL(=windll) は StdCall のため x86 で規約が食い違う。
    lib = cdll.LoadLibrary(str(libPath))

    lib.SetLogCallback.restype = None
    lib.SetLogCallback.argtypes = [LOG_CALLBACK, c_int]

    lib.Login.restype = c_uint
    lib.Login.argtypes = [c_char_p, c_char_p, c_char_p, c_char_p]

    lib.Logout.restype = c_uint
    lib.Logout.argtypes = []

    lib.Deposit.restype = c_uint
    lib.Deposit.argtypes = [c_uint, c_ushort]

    lib.Withdraw.restype = c_uint
    lib.Withdraw.argtypes = [c_ushort]

    lib.GetPurchaseData.restype = c_uint
    lib.GetPurchaseData.argtypes = [c_void_p]

    lib.ReleasePurchaseData.restype = None
    lib.ReleasePurchaseData.argtypes = [POINTER(ST_PURCHASE_DATA_INTERNAL)]

    lib.GetBetInstance.restype = c_uint
    lib.GetBetInstance.argtypes = [c_ushort, c_byte, c_ushort, c_byte, c_byte, c_byte, c_byte, c_uint, c_char_p, c_void_p]

    lib.Bet.restype = c_uint
    lib.Bet.argtypes = [c_void_p, c_ushort, c_ushort]

    lib.GetBetInstanceWin5.restype = c_uint
    lib.GetBetInstanceWin5.argtypes = [c_uint, c_ushort, c_byte, c_byte, c_char_p, c_void_p]

    lib.BetWin5.restype = c_uint
    lib.BetWin5.argtypes = [ST_BET_DATA_WIN5, c_ushort]

    lib.BetWin5Auto.restype = c_uint
    lib.BetWin5Auto.argtypes = [c_byte, c_char_p, c_ushort, c_uint, c_ushort, c_byte, c_byte]

    lib.SetAutoDepositFlag.restype = c_uint
    lib.SetAutoDepositFlag.argtypes = [c_bool, c_uint, c_ushort]

    lib.GetOdds.restype = c_uint
    lib.GetOdds.argtypes = [c_ushort, c_byte, c_byte, c_void_p]

    lib.ReleaseOddsData.restype = None
    lib.ReleaseOddsData.argtypes = [POINTER(ST_ODDS_DATA_INTERNAL)]

    lib.GetRaceCard.restype = c_uint
    lib.GetRaceCard.argtypes = [c_ushort, c_byte, c_void_p]

    lib.ReleaseRaceCardData.restype = None
    lib.ReleaseRaceCardData.argtypes = [POINTER(ST_RACECARD_DATA_INTERNAL)]

    lib.GetNotice.restype = c_uint
    lib.GetNotice.argtypes = [c_void_p]

    lib.ReleaseNoticeData.restype = None
    lib.ReleaseNoticeData.argtypes = [POINTER(ST_NOTICE_DATA_INTERNAL)]

    if maxsize > 2 ** 32:
        windll.kernel32.FreeLibrary.argtypes = [wintypes.HMODULE]

def uninit():
    '''
        モジュールのファイナライズ
    '''

    global lib

    libraryHandle = lib._handle
    del lib

    windll.kernel32.FreeLibrary(libraryHandle)

def set_log_callback(handler, minLevel : int = LOG_LEVEL_INFO) -> None:
    '''
        DLL内部のログを受け取るハンドラを登録する(Noneで解除)

        handler は handler(level: int, message: str) の形で呼ばれる。
        入出金はサーバがエラーコードを返さないため、失敗の原因を知るには
        このログが唯一の手掛かりになる。失敗した段階・画面ID・タイトルは
        LOG_LEVEL_ERROR で通知されるが、サーバ側の拒否理由が載る応答本文の抜粋は
        LOG_LEVEL_TRACE を指定したときのみ通知される(口座番号や残高を含み得る)。

        注意: ハンドラはDLL内部ロックを保持したまま呼ばれるため、
        ハンドラ内から本モジュールのAPIを呼び返さないこと(デッドロックする)。
        またログイン中は中央・地方の2スレッドから同時に呼ばれる。
    '''

    global lib, _logCallbackRef, _logHandler

    _logHandler = handler

    if handler is None:
        # 解除時はDLL側が排他ロックを取るため、戻った時点で実行中の呼び出しは無い
        lib.SetLogCallback(None, minLevel)
        _logCallbackRef = None
        return

    def _onLog(level, message):
        # message は UTF-8 の null 終端文字列
        try:
            text = message.decode('utf-8', 'replace') if message else ''
            _logHandler(level, text)
        except Exception:
            pass    # ハンドラ側の例外をネイティブへ伝播させない

    _logCallbackRef = LOG_CALLBACK(_onLog)
    lib.SetLogCallback(_logCallbackRef, minLevel)

def login(iNetId : str, id : str, password : str, pars : str) -> int:
    '''
        ログイン処理実行
    '''

    global lib

    return lib.Login(iNetId.encode('utf-8'), id.encode('utf-8'), password.encode('utf-8'), pars.encode('utf-8'))

def logout() -> int:
    '''
        ログアウト処理実行
    '''

    global lib

    return lib.Logout()

def deposit(depositValue : int, retryCount : int = DEFAULT_RETRY_COUNT) -> int:
    '''
        入金処理実行
    '''

    global lib

    return lib.Deposit(depositValue, retryCount)

def withdraw(retryCount : int = DEFAULT_RETRY_COUNT) -> int:
    '''
        出金処理実行
    '''

    global lib

    return lib.Withdraw(retryCount)

def get_purchase_data(purchaseData : ST_PURCHASE_DATA) -> int:
    '''
        購入状況取得処理実行
    '''

    global lib

    # 内部的な構造体のインスタンスを生成する
    tempPurchaseData = ST_PURCHASE_DATA_INTERNAL()

    # 購入状況を取得する
    returnValue = lib.GetPurchaseData(byref(tempPurchaseData))
    if (returnValue & 1) != 1:
        return returnValue
    
    # 返却用のデータに値を設定
    purchaseData.TicketCount = tempPurchaseData.TicketCount
    purchaseData.AvailableBetCount = tempPurchaseData.AvailableBetCount
    purchaseData.Balance = tempPurchaseData.Balance
    purchaseData.DayPurchase = tempPurchaseData.DayPurchase
    purchaseData.DayHaraimodosi = tempPurchaseData.DayHaraimodosi
    purchaseData.TotalPurchase = tempPurchaseData.TotalPurchase
    purchaseData.TotalHaraimodosi = tempPurchaseData.TotalHaraimodosi
    purchaseData.TicketCount = tempPurchaseData.TicketCount

    if tempPurchaseData.TicketCount <= 0:
        lib.ReleasePurchaseData(byref(tempPurchaseData))
        return returnValue

    # 馬券データ(全て)を格納するためのバッファを確保
    allTicketBytes = bytearray(string_at(tempPurchaseData.TicketData, \
        sizeof(ST_TICKET_DATA_INTERNAL) * tempPurchaseData.TicketCount))
    
    for i in range(tempPurchaseData.TicketCount):
        # 1つ分の構造体データを格納するバッファを確保して情報を格納する
        oneTicketBytes = bytearray(sizeof(ST_TICKET_DATA_INTERNAL))
        for j in range(sizeof(ST_TICKET_DATA_INTERNAL)):   
            oneTicketBytes[j] = allTicketBytes[j + i * sizeof(ST_TICKET_DATA_INTERNAL)]

        # 馬券データ(1個)をインスタンスに変換
        oneTicketData = ST_TICKET_DATA_INTERNAL.from_buffer(oneTicketBytes, 0)

        # 返却用の馬券データ(1個)を生成
        tempTicketData = ST_TICKET_DATA()

        # 返却用のデータに値を設定
        tempTicketData.DayFlag = oneTicketData.DayFlag
        tempTicketData.DetailCount = oneTicketData.DetailCount
        tempTicketData.Hour = oneTicketData.Hour
        tempTicketData.Minute = oneTicketData.Minute
        tempTicketData.Kingaku = oneTicketData.Kingaku
        tempTicketData.Payout = oneTicketData.Payout
        tempTicketData.ReceiptNo = oneTicketData.ReceiptNo

        if oneTicketData.DetailCount <= 0:
            lib.ReleasePurchaseData(byref(tempPurchaseData))
            return returnValue

        # 詳細データ(全て)を格納するためのバッファを確保    
        allDetailBytes = bytearray(string_at(oneTicketData.DetailData, \
            sizeof(ST_TICKET_DATA_DETAIL) * oneTicketData.DetailCount))

        for j in range(oneTicketData.DetailCount):
            # 1つ分の構造体データを格納するバッファを確保して情報を格納する
            oneDetailBytes = bytearray(sizeof(ST_TICKET_DATA_DETAIL))
            for k in range(sizeof(ST_TICKET_DATA_DETAIL)):
                oneDetailBytes[k] = allDetailBytes[k + j * sizeof(ST_TICKET_DATA_DETAIL)]

            # 詳細データ(1個)をインスタンスに変換
            tempTicketData.DetailData.append(ST_TICKET_DATA_DETAIL.from_buffer(oneDetailBytes, 0))
        
        # 馬券データを引数に追加する
        purchaseData.TicketData.append(tempTicketData)
    
    lib.ReleasePurchaseData(byref(tempPurchaseData))

    return returnValue

def get_bet_instance(kaisai : int, raceNo : int, year : int, month : int, day : int, \
                    houshiki : int, shikibetsu : int, kingaku : int, kaime : str, betData : ST_BET_DATA) -> int:
    '''
        馬券購入用インスタンス取得処理
    '''
    
    global lib

    return lib.GetBetInstance(kaisai, raceNo, year, month, day, houshiki, shikibetsu, kingaku, kaime.encode('utf-8'), byref(betData))

def get_bet_instance_win5(kingaku : int, year : int, month : int, day : int, kaime : str, betData : ST_BET_DATA_WIN5) -> int:
    '''
        馬券購入用インスタンス取得処理(WIN5)
    '''
    
    global lib

    return lib.GetBetInstanceWin5(kingaku, year, month, day, kaime.encode('utf-8'), byref(betData))

def bet(betDataList : list, listCount : int, waitMiliSeconds  : int = DEFAULT_WAIT_TIME) -> int:
    '''
        馬券購入処理実行
    '''

    global lib
    
    return lib.Bet(betDataList, listCount, waitMiliSeconds)

def bet_win5(betData : ST_BET_DATA_WIN5, waitMiliSeconds : int = DEFAULT_WAIT_TIME) -> int:
    '''
        馬券購入処理実行(WIN5)
    '''

    global lib

    return lib.BetWin5(betData, waitMiliSeconds)

def bet_win5_auto(mode : int, axisUmaban : str, betCount : int, kingaku : int,
                  year : int, month : int, day : int) -> int:
    '''
        WIN5を「セレクト」または「ランダム」で購入する(中央競馬のみ)

        買い目はサーバが生成する。生成された買い目はそのまま購入されるため、
        内容を事前に確認する手段は無い。実際に購入が行われる。

        mode        : WIN5_AUTO_SELECT(2) / WIN5_AUTO_RANDOM(3)
        axisUmaban  : セレクト時の軸馬番。5レース分をカンマ区切りで指定する(例 "3,0,7,0,12")。
                      0のレースはサーバが選ぶ。すべて0は指定できない。ランダム時は None 可。
        betCount    : 生成させる点数(1〜50)
        kingaku     : 1点あたりの購入金額(円。100円単位)
    '''

    global lib

    axis = axisUmaban.encode('utf-8') if axisUmaban else None
    return lib.BetWin5Auto(mode, axis, betCount, kingaku, year, month, day)

def set_auto_deposit_flag(enable : bool, depositValue : int, confirmTimeout : int = DEFAULT_CONFIRM_TIMEOUT) -> int:
    '''
        自動入金機能フラグ設定
    '''

    global lib

    return lib.SetAutoDepositFlag(enable, depositValue, confirmTimeout)

def get_odds(place : int, raceNo : int, shikibetsu : int, oddsData : ST_ODDS_DATA) -> int:
    '''
        オッズ取得処理実行(中央競馬・地方競馬・海外競馬に対応)
        単勝・複勝は基本オッズ、枠連〜三連単は全通りのオッズ表を取得する。
        ネイティブ側で確保されたメモリは本関数内で解放する。
    '''

    global lib

    # 内部的な構造体のインスタンスを生成する
    tempOddsData = ST_ODDS_DATA_INTERNAL()

    # オッズを取得する
    returnValue = lib.GetOdds(place, raceNo, shikibetsu, byref(tempOddsData))

    # 返却用のデータに値を設定
    oddsData.Place = tempOddsData.Place
    oddsData.RaceNo = tempOddsData.RaceNo
    oddsData.OddsTime = tempOddsData.OddsTime.decode('ascii', errors='ignore')
    oddsData.DetailCount = tempOddsData.DetailCount

    # 取得失敗・明細なしはここで解放して戻る
    if (returnValue & 1) != 1 or tempOddsData.DetailCount <= 0 or not tempOddsData.DetailData:
        lib.ReleaseOddsData(byref(tempOddsData))
        return returnValue

    # オッズ明細(全て)を格納するためのバッファを確保(解放前に取り出す)
    allDetailBytes = bytearray(string_at(tempOddsData.DetailData, \
        sizeof(ST_ODDS_DETAIL) * tempOddsData.DetailCount))

    for i in range(tempOddsData.DetailCount):
        # 1つ分の構造体データを格納するバッファを確保して情報を格納する
        oneDetailBytes = bytearray(sizeof(ST_ODDS_DETAIL))
        for j in range(sizeof(ST_ODDS_DETAIL)):
            oneDetailBytes[j] = allDetailBytes[j + i * sizeof(ST_ODDS_DETAIL)]

        # オッズ明細(1個)をインスタンスに変換して追加する
        oddsData.OddsDetail.append(ST_ODDS_DETAIL.from_buffer(oneDetailBytes, 0))

    lib.ReleaseOddsData(byref(tempOddsData))

    return returnValue

def get_race_card(place : int, raceNo : int, raceCard : ST_RACECARD_DATA) -> int:
    '''
        出馬表取得処理実行(中央競馬・地方競馬・海外競馬に対応)
        各出走馬の枠番・馬番・馬名・性齢・馬体重・騎手・斤量・調教師・
        単勝人気・単勝/複勝オッズを取得する。
        ネイティブ側で確保されたメモリは本関数内で解放する。
        EntryData の各要素は ST_ENTRY_DETAIL で、馬名等の文字列フィールドは
        UTF-8 の bytes のため利用時に .decode('utf-8') する。
    '''

    global lib

    # 内部的な構造体のインスタンスを生成する
    tempRaceCardData = ST_RACECARD_DATA_INTERNAL()

    # 出馬表を取得する
    returnValue = lib.GetRaceCard(place, raceNo, byref(tempRaceCardData))

    # 返却用のデータに値を設定
    raceCard.Place = tempRaceCardData.Place
    raceCard.RaceNo = tempRaceCardData.RaceNo
    raceCard.OddsTime = tempRaceCardData.OddsTime.decode('ascii', errors='ignore')
    raceCard.EntryCount = tempRaceCardData.EntryCount
    # レース名はUTF-8のbytesのためutf-8でデコードする
    raceCard.RaceName = tempRaceCardData.RaceName.decode('utf-8', errors='ignore')
    # 発売締切時刻("HH:MM")と発売状態。海外開催でも取得できる
    raceCard.Deadline = tempRaceCardData.Deadline.decode('ascii', errors='ignore')
    raceCard.RaceStatus = tempRaceCardData.RaceStatus

    # 取得失敗・明細なしはここで解放して戻る
    if (returnValue & 1) != 1 or tempRaceCardData.EntryCount <= 0 or not tempRaceCardData.EntryData:
        lib.ReleaseRaceCardData(byref(tempRaceCardData))
        return returnValue

    # 出走馬明細(全て)を格納するためのバッファを確保(解放前に取り出す)
    allEntryBytes = bytearray(string_at(tempRaceCardData.EntryData, \
        sizeof(ST_ENTRY_DETAIL) * tempRaceCardData.EntryCount))

    for i in range(tempRaceCardData.EntryCount):
        # 1つ分の構造体データを格納するバッファを確保して情報を格納する
        oneEntryBytes = bytearray(sizeof(ST_ENTRY_DETAIL))
        for j in range(sizeof(ST_ENTRY_DETAIL)):
            oneEntryBytes[j] = allEntryBytes[j + i * sizeof(ST_ENTRY_DETAIL)]

        # 出走馬明細(1個)をインスタンスに変換して追加する
        raceCard.EntryData.append(ST_ENTRY_DETAIL.from_buffer(oneEntryBytes, 0))

    lib.ReleaseRaceCardData(byref(tempRaceCardData))

    return returnValue

def get_notice(notice : ST_NOTICE_DATA) -> int:
    '''
        お知らせ取得処理実行
        ログイン済みのセッションが必要(中央優先、失敗時は地方へフォールバック)。
        お知らせが無い場合は Message が空文字・ItemCount が 0 で成功を返す。
        ネイティブ側で確保されたメモリは本関数内で解放する。
    '''

    global lib

    # 内部的な構造体のインスタンスを生成する
    tempNoticeData = ST_NOTICE_DATA_INTERNAL()

    # お知らせを取得する
    returnValue = lib.GetNotice(byref(tempNoticeData))

    # 返却用のデータに値を設定(文字列はUTF-8のbytes)
    notice.Message = tempNoticeData.Message.decode('utf-8', errors='ignore')
    notice.NoticeNo = tempNoticeData.NoticeNo.decode('utf-8', errors='ignore')
    notice.NoticeType = tempNoticeData.NoticeType.decode('utf-8', errors='ignore')
    notice.ItemCount = tempNoticeData.ItemCount

    # 取得失敗・一覧なしはここで解放して戻る
    if (returnValue & SUCCESS) != SUCCESS or tempNoticeData.ItemCount <= 0 or not tempNoticeData.ItemData:
        lib.ReleaseNoticeData(byref(tempNoticeData))
        return returnValue

    # お知らせ一覧(全て)を格納するためのバッファを確保(解放前に取り出す)
    allItemBytes = bytearray(string_at(tempNoticeData.ItemData, \
        sizeof(ST_NOTICE_ITEM_INTERNAL) * tempNoticeData.ItemCount))

    for i in range(tempNoticeData.ItemCount):
        # 1つ分の構造体データを格納するバッファを確保して情報を格納する
        oneItemBytes = bytearray(sizeof(ST_NOTICE_ITEM_INTERNAL))
        for j in range(sizeof(ST_NOTICE_ITEM_INTERNAL)):
            oneItemBytes[j] = allItemBytes[j + i * sizeof(ST_NOTICE_ITEM_INTERNAL)]

        rawItem = ST_NOTICE_ITEM_INTERNAL.from_buffer(oneItemBytes, 0)

        item = ST_NOTICE_ITEM()
        item.Title = rawItem.Title.decode('utf-8', errors='ignore')
        item.Date = rawItem.Date.decode('utf-8', errors='ignore')
        item.Url = rawItem.Url.decode('utf-8', errors='ignore')
        item.Icon = rawItem.Icon.decode('utf-8', errors='ignore')
        item.Color = rawItem.Color.decode('utf-8', errors='ignore')
        notice.ItemData.append(item)

    lib.ReleaseNoticeData(byref(tempNoticeData))

    return returnValue
