# IpatHelper

**IpatHelper.dll** は [JRA](https://www.jra.go.jp/) の即PAT（I-PAT）投票機能を各種プログラムから呼び出すためのWindows用DLLモジュールです。  
中央競馬・地方競馬・海外競馬・WIN5 に対応しており、ログイン・入出金・馬券購入・購入履歴取得・オッズ取得・出馬表取得までの一連のフローを、シンプルな公開APIで操作できます。

> 個人でJV-Link関連の実装をしていたところ「投票モジュールを自分用に作っておきたいな」と思ったのが開発のきっかけです。  
> 最終的にはプログラミングを通して競馬に興味をもってもらうことを目的として公開しました。

---

## 📦 バイナリのダウンロード

ビルド済みバイナリは [こちら](https://github.com/Mikimini9627/ipathelper_dll/tree/main/builds) からダウンロードできます。  
実行環境に合わせて **x64 / x86** を選択してください。

公開APIの詳細については [関数仕様書](/builds/関数仕様書.md) を参照してください。

---

## ✨ 機能一覧

### ログイン / ログアウト
- 中央競馬・地方競馬の両サーバーへ並列ログイン
- `Login` / `Logout` で一括管理

### 入出金
- 登録口座からの入金 (`Deposit`) および出金 (`Withdraw`)
- 通信失敗時のリトライ回数を引数で指定可能（デフォルト: 10回）
- **自動入金フラグ** (`SetAutoDepositFlag`) を設定しておくと、馬券購入時に残高不足が検出された場合、あらかじめ指定した金額を自動入金してから購入に進みます

### 馬券購入状況の取得
- `GetPurchaseData` で残高・当日/累計の購入額・払戻額・購入済み馬券一覧を取得
- 取得後は必ず `ReleasePurchaseData` でメモリを解放してください

### 馬券購入
- `GetBetInstance` で購入情報を構築し、`Bet` で一括購入
- WIN5専用の `GetBetInstanceWin5` / `BetWin5` にも対応
- WIN5の**セレクト / ランダム購入**は `BetWin5Auto`（買い目はサーバが生成。軸馬の指定も可能）
- 購入方式: **通常 / フォーメーション / ボックス / ながし（軸1頭・軸2頭）/ マルチ**
- 式別: **単勝 / 複勝 / 枠連 / 馬連 / ワイド / 馬単 / 三連複 / 三連単** (すべて対応)
- 海外開催場に **アスコット** を追加。ながし・マルチは中央・地方・海外すべてで指定可能

### オッズ取得
- `GetOdds` で指定レース・式別のオッズを取得（**中央競馬・地方競馬に対応**）
- 単勝・複勝は基本オッズ、枠連〜三連単は全通りのオッズ表を取得
- 取得後は必ず `ReleaseOddsData` でメモリを解放してください

### 出馬表取得
- `GetRaceCard` で指定レースの出馬表（出走馬一覧）を取得（**中央競馬・地方競馬に対応**）
- 枠番・馬番・馬名・性齢・馬体重・騎手・斤量・調教師・単勝人気・単勝/複勝オッズを取得
- 文字列は UTF-8。取得後は必ず `ReleaseRaceCardData` でメモリを解放してください

### お知らせ取得
- `GetNotice` で現在有効なお知らせを取得（**中央競馬・地方競馬に対応**）
- 強制表示お知らせ本文に加え、お知らせ一覧（タイトル・日付・URL 等）を全件取得
- 文字列は UTF-8。取得後は必ず `ReleaseNoticeData` でメモリを解放してください

---

## 🌏 対応競馬場

### 中央競馬 (JRA)
札幌、函館、福島、新潟、東京、中山、中京、京都、阪神、小倉

### 地方競馬 (NAR)
園田、姫路、名古屋、門別、盛岡、水沢、浦和、船橋、大井、川崎、笠松、金沢、高知、佐賀

### 海外
ロンシャン、シャティン、サンタアニタ、ドーヴィル、チャーチルダウンズ、キングアブドゥルアジーズ、アスコット

---

## 🔧 公開API

```c
// ログイン
unsigned int Login(const char szINetId[], const char szId[], const char szPassword[], const char szPars[]);

// ログアウト
unsigned int Logout();

// 入金
unsigned int Deposit(const unsigned int unDepositValue, const unsigned short usRetryCount = 10);

// 出金
unsigned int Withdraw(const unsigned short usRetryCount = 10);

// 馬券購入状況の取得
unsigned int GetPurchaseData(ST_PURCHASE_DATA* pobjStatus);
void         ReleasePurchaseData(ST_PURCHASE_DATA* pobjStatus);

// 馬券購入
unsigned int GetBetInstance(const unsigned short usPlace, const unsigned char ucRaceNo,
                             const unsigned short usYear, const unsigned char ucMonth,
                             const unsigned char ucDay, const unsigned char ucHoushiki,
                             const unsigned char ucShikibetsu, const unsigned int nKingaku,
                             const char szKaime[], ST_BET_DATA* pobjBetData);
unsigned int Bet(const ST_BET_DATA pobjBetData[], const unsigned short usBetCount,
                 const unsigned short usWaitMilliSeconds = 500);

// WIN5購入
unsigned int GetBetInstanceWin5(const unsigned int unKingaku, const unsigned short usYear,
                                  const unsigned char ucMonth, const unsigned char ucDay,
                                  const char szKaime[], ST_BET_DATA_WIN5* pobjBetData);
unsigned int BetWin5(const ST_BET_DATA_WIN5 objBetData, const unsigned short usWaitMilliSeconds = 500);

// WIN5をセレクト/ランダムで購入する(買い目はサーバが生成する)
unsigned int BetWin5Auto(const unsigned char ucMode, const char szAxisUmaban[],
                          const unsigned short usBetCount, const unsigned int unKingaku,
                          const unsigned short usYear, const unsigned char ucMonth,
                          const unsigned char ucDay);

// 自動入金フラグの設定
unsigned int SetAutoDepositFlag(const bool bEnable, const unsigned int unDepositValue = 1000,
                                 const unsigned short usConfirmTimeout = 10000);

// オッズ取得(中央競馬・地方競馬に対応)
unsigned int GetOdds(const unsigned short usPlace, const unsigned char ucRaceNo,
                     const unsigned char ucShikibetsu, ST_ODDS_DATA* pobjOdds);
void         ReleaseOddsData(ST_ODDS_DATA* pobjOdds);

// 出馬表取得(中央競馬・地方競馬に対応)
unsigned int GetRaceCard(const unsigned short usPlace, const unsigned char ucRaceNo,
                         ST_RACECARD_DATA* pobjRaceCard);
void         ReleaseRaceCardData(ST_RACECARD_DATA* pobjRaceCard);

// お知らせ取得(中央競馬・地方競馬に対応)
unsigned int GetNotice(ST_NOTICE_DATA* pobjNotice);
void         ReleaseNoticeData(ST_NOTICE_DATA* pobjNotice);

// ログコールバックの登録(Releaseビルドでも取得可能。nullptrで解除)
void         SetLogCallback(LogCallback callback, int nMinLevel);
```

戻り値は `RETURN_VALUE` 列挙体のビットフラグです。

| 値 | 意味 |
|---|---|
| `SUCCESS` | 処理成功 |
| `UNSUCCESS` | 処理失敗 |
| `FAILED_CHUOU` | 中央競馬での処理失敗 |
| `FAILED_CHIHOU` | 地方競馬での処理失敗 |
| `FAILED_COMMUNICATE_CHUOU` | 中央競馬との通信失敗 |
| `FAILED_COMMUNICATE_CHIHOU` | 地方競馬との通信失敗 |

### 🪵 ログの取得

入出金はサーバレンダリングの HTML フォームのため `erc` / `erm` のようなエラーコードを返しません。
**失敗の原因を知るには `SetLogCallback` が唯一の手段です。**

```cpp
void __cdecl OnLog(int nLevel, const char* pszMessage)
{
    static const char* aszLevel[] = { "TRACE", "INFO", "WARN", "ERROR" };
    printf("[%s] %s\n", aszLevel[nLevel], pszMessage);  // pszMessage は UTF-8
}

SetLogCallback(OnLog, LOG_LEVEL_INFO);   // 調査時は LOG_LEVEL_TRACE
```

- 失敗した段階・画面 ID・画面タイトルは `LOG_LEVEL_ERROR` で通知されます。
- **サーバ側の拒否理由が載る応答本文の抜粋は `LOG_LEVEL_TRACE` のときのみ**通知されます
  （口座番号や残高を含み得るため、調査時のみ指定してください）。
- コールバックは DLL 内部ロックを保持したまま呼ばれます。**内部から本 DLL の API を
  呼び返さないでください**（デッドロックします）。
- 呼び出し規約は `__cdecl` です（C#: `[UnmanagedFunctionPointer(CallingConvention.Cdecl)]` /
  Python: `CFUNCTYPE` と `ctypes.CDLL`）。

詳細は [`builds/関数仕様書.md`](builds/関数仕様書.md) の «5.19 SetLogCallback» を参照してください。

---

## 🚀 クイックスタート

実装サンプルをリポジトリ内に用意しています（`sample_app/` 配下に C++ / C# / Python）。各言語ごとのサンプルを参考にしてください。  
主要言語向けにはラッパーライブラリを配布しているため、DLL を直接扱わずに導入できます。

**Python（PyPI）** — [ipathelper](https://pypi.org/project/ipathelper/)

```bash
pip install ipathelper
```

**C# / .NET（NuGet）** — [IpatHelperNet](https://www.nuget.org/packages/IpatHelperNet)

```bash
dotnet add package IpatHelperNet
```

どちらのパッケージにもネイティブ DLL（x64 / x86）が同梱されるため、DLL の個別配置は不要です。

---

## 💻 動作確認環境 / 開発環境

| 項目 | 内容 |
|---|---|
| 動作確認OS | Windows 11 Pro 64bit 日本語版 |
| 開発OS | Windows 11 Home 64bit |
| IDE | Visual Studio 2022 / Visual Studio Code / Eclipse |

---

## ⚠️ 注意事項

- `IpatHelper.dll` 本体のソースコードは非公開です
- 本モジュールおよびサンプルアプリの利用によって生じた損害について、作者は一切の責任を負いません
- スマートUMACAへの対応は今後追加予定です
