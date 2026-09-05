# IpatHelper

**IpatHelper.dll** は [JRA](https://www.jra.go.jp/) の即PAT（I-PAT）投票機能を各種プログラムから呼び出すためのWindows用DLLモジュールです。  
中央競馬・地方競馬・海外競馬・WIN5 に対応しており、ログイン・入出金・馬券購入・購入履歴取得・オッズ取得・出馬表取得・お知らせ取得までの一連のフローを、シンプルな公開APIで操作できます。

> 個人でJV-Link関連の実装をしていたところ「投票モジュールを自分用に作っておきたいな」と思ったのが開発のきっかけです。  
> 最終的にはプログラミングを通して競馬に興味をもってもらうことを目的として公開しました。

---

## 📦 バイナリのダウンロード

ビルド済みバイナリは [リリースページ](https://github.com/Mikimini9627/ipathelper_dll/releases/latest) からダウンロードできます。  
実行環境に合わせて **x64 / x86** の zip を選択してください（`IpatHelper.dll` と `IpatHelper.lib` を同梱しています）。

最新のビルド成果物は [`builds/`](https://github.com/Mikimini9627/ipathelper_dll/tree/master/builds) からも直接参照できます。

公開APIの詳細については [関数仕様書](/builds/関数仕様書.md) を参照してください。

---

## ✨ 機能一覧

### ログイン / ログアウト
- 中央競馬・地方競馬の両サーバーへ並列ログイン
- `Login` / `Logout` で一括管理
- 投票受付時間外やメンテナンス中は `FAILED_OUT_OF_SERVICE` が併せて立ちます。この場合は即座に再試行しても必ず失敗するため、時間をおいて再試行してください

### 入出金
- 登録口座からの入金 (`Deposit`) および全額出金 (`Withdraw`)
- 指示の完了後、**残高への反映を確認できた場合のみ成功**を返します（反映待ちのタイムアウトは `SetAutoDepositFlag` の `usConfirmTimeout`、デフォルト: 10,000ms）
- リトライ回数 (`usRetryCount`、デフォルト: 10回) が適用されるのは**実行前の準備段階のみ**です。入出金の実行そのものは、応答を受信できなくてもサーバ側で成立している可能性があるため再送しません（二重入出金の防止）
- **PayPay（コード決済アプリ）を登録口座にしている会員は利用できません**。通信を行わず `UNSUCCESS` を返します。PayPay **銀行** は従来どおり利用できます（別物です）
- **自動入金フラグ** (`SetAutoDepositFlag`) を設定しておくと、馬券購入時に残高不足が検出された場合、あらかじめ指定した金額を自動入金してから購入に進みます

### 馬券購入状況の取得
- `GetPurchaseData` で残高・当日/累計の購入額・払戻額・購入済み馬券一覧を取得
- 応答の一部を解析できなかった明細は `ucDecisionFlag` が `DECISION_FLAG_PARSE_FAILED`（0）になり、**他の明細は正常に返されます**（1件も解析できなかった場合のみ関数自体が失敗します）
- 同じ構造体を使い回す場合、次の取得前に必ず `ReleasePurchaseData` を呼んでください（未解放のまま再取得するとリークします）

### 馬券購入
- `GetBetInstance` で購入情報を構築し、`Bet` で一括購入
- WIN5専用の `GetBetInstanceWin5` / `BetWin5` にも対応
- WIN5の**セレクト / ランダム購入**は `BetWin5Auto`（**中央競馬のみ**。点数 1〜50、軸馬は5レース分をカンマ区切りで指定し、`0` のレースはサーバが選びます）。**買い目はサーバが生成してそのまま購入されるため、内容を事前に確認することはできません**
- 購入方式: **通常 / フォーメーション / ボックス / ながし（1着・2着・3着・軸2頭）/ マルチ**
- 式別: **単勝 / 複勝 / 枠連 / 馬連 / ワイド / 馬単 / 三連複 / 三連単** (すべて対応)
- 金額は **100円単位**。**1回の送信あたりの合計購入金額は 1,000,000 円が上限**です（I-PAT 側と同じ上限）
- 買い目の馬番は **1〜18（海外は 1〜24）**、枠番は 1〜8。範囲外の馬番や、方式・式別と列数が合わない買い目は黙って無視せず `UNSUCCESS` で失敗します
- `Bet` / `BetWin5` の `usWaitMilliseconds`（デフォルト: 500ms）は**分割送信の間隔**であり、タイムアウトではありません。購入に失敗する場合は値を大きくして調整してください
- 海外開催場に **アスコット** を追加。ながし・マルチは中央・地方・海外すべてで指定可能

### オッズ取得
- `GetOdds` で指定レース・式別のオッズを取得（**中央競馬・地方競馬・海外競馬に対応**）
- 単勝・複勝は基本オッズ、枠連〜三連単は全通りのオッズ表を取得
- オッズは **10倍の整数**で格納されます（例: 12.3倍 → `123`）。複勝・ワイドは下限を `unOdds`、上限を `unOddsHigh` に格納します
- 海外開催は**中央競馬へのログインが必要**で、海外競馬に枠は無いため**枠連を指定すると `UNSUCCESS`** になります
- 応援馬券はオッズの式別ではないため指定できません。単勝・複勝を個別に取得してください
- 取得後は必ず `ReleaseOddsData` でメモリを解放してください

### 出馬表取得
- `GetRaceCard` で指定レースの出馬表（出走馬一覧）を取得（**中央競馬・地方競馬・海外競馬に対応**）
- 枠番・馬番・馬名・性齢・馬体重・騎手・斤量・調教師・単勝人気・単勝/複勝オッズを取得
- あわせて**レース名**（`szRaceName`）・**発売締切時刻**（`szDeadline`）・**発売状態**（`ucRaceStatus`: 発売中 / 発売終了 / 発売中止 / 発売前）を取得（追加の通信は発生せず、**海外開催でも取得可能**）
- 海外開催は**中央競馬へのログインが必要**で、取得できる項目が国内より少なく、**馬番・馬名・単勝人気・単勝/複勝オッズとレース名のみ**です（枠番・性齢・馬体重・騎手・斤量・調教師は 0 または空文字になります）
- 文字列は UTF-8。取得後は必ず `ReleaseRaceCardData` でメモリを解放してください

### お知らせ取得
- `GetNotice` で現在有効なお知らせを取得（ログイン済みのセッションが必要。中央優先、失敗時は地方へフォールバックします）
- 強制表示お知らせ本文に加え、お知らせ一覧（タイトル・日付・URL 等）を全件取得
- お知らせが無い場合は本文が空文字・件数 0 で**成功**を返します
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

// 入金(PayPay(コード決済アプリ)を登録口座にしている場合は非対応。PayPay銀行は可)
unsigned int Deposit(const unsigned int unDepositValue, const unsigned short usRetryCount = 10);

// 全額出金(同上)
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
// usWaitMilliseconds は分割送信の「間隔」(ms)。タイムアウトではない
unsigned int Bet(const ST_BET_DATA pobjBetData[], const unsigned short usBetCount,
                 const unsigned short usWaitMilliseconds = 500);

// WIN5購入
unsigned int GetBetInstanceWin5(const unsigned int unKingaku, const unsigned short usYear,
                                  const unsigned char ucMonth, const unsigned char ucDay,
                                  const char szKaime[], ST_BET_DATA_WIN5* pobjBetData);
unsigned int BetWin5(const ST_BET_DATA_WIN5 objBetData, const unsigned short usWaitMilliseconds = 500);

// WIN5をセレクト/ランダムで購入する(中央競馬のみ。買い目はサーバが生成し、そのまま購入される)
unsigned int BetWin5Auto(const unsigned char ucMode, const char szAxisUmaban[],
                          const unsigned short usBetCount, const unsigned int unKingaku,
                          const unsigned short usYear, const unsigned char ucMonth,
                          const unsigned char ucDay);

// 自動入金フラグの設定
unsigned int SetAutoDepositFlag(const bool bEnable, const unsigned int unDepositValue = 1000,
                                 const unsigned short usConfirmTimeout = 10000);

// オッズ取得(中央競馬・地方競馬・海外競馬に対応。海外は枠連不可)
unsigned int GetOdds(const unsigned short usPlace, const unsigned char ucRaceNo,
                     const unsigned char ucShikibetsu, ST_ODDS_DATA* pobjOdds);
void         ReleaseOddsData(ST_ODDS_DATA* pobjOdds);

// 出馬表取得(中央競馬・地方競馬・海外競馬に対応)
unsigned int GetRaceCard(const unsigned short usPlace, const unsigned char ucRaceNo,
                         ST_RACECARD_DATA* pobjRaceCard);
void         ReleaseRaceCardData(ST_RACECARD_DATA* pobjRaceCard);

// お知らせ取得(ログイン済みセッションが必要。中央優先、失敗時は地方へフォールバック)
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
| `FAILED_OUT_OF_SERVICE` | サービス時間外（`FAILED_CHUOU` / `FAILED_CHIHOU` と併せて立ちます） |

判定はビット演算で行ってください。

```cpp
unsigned int ret = Bet(betData, 1);

if (ret & (unsigned int)RETURN_VALUE::SUCCESS) {
    // 購入成功
}
if (ret & (unsigned int)RETURN_VALUE::FAILED_OUT_OF_SERVICE) {
    // 投票受付時間外またはメンテナンス中。時間をおいて再試行する
}
```

> `FAILED_OUT_OF_SERVICE` は投票受付時間外が最も多い原因で、メンテナンス中とは区別できません。
> JRA の発売時間は季節や開催により変動するため、DLL 側では時刻による事前チェックを行っていません。

### 🧵 呼び出し規約とスレッド安全性

- 公開関数・コールバックはすべて **`__cdecl`** です。x86 版を使う場合は呼び出し側で明示してください
  （C#: `[DllImport("IpatHelper.dll", CallingConvention = CallingConvention.Cdecl)]` /
  Python: `ctypes.WinDLL` ではなく **`ctypes.CDLL`**）。
- 通信を伴う公開関数は DLL 内部で直列化されます。複数スレッドから同時に呼び出しても壊れませんが、
  先行する呼び出しが完了するまでブロックします（投票・入出金は残高反映待ちを含むため数分に及ぶことがあります）。
- `GetBetInstance` / `GetBetInstanceWin5` は通信を行わない入力変換のため、通信中でも並行して呼び出せます。
- 例外が DLL の境界を越えることはありません（内部で捕捉され `UNSUCCESS` になります）。
- `SetAutoDepositFlag` の `bEnable` は C++ の `bool`（1バイト）です。C# では `[MarshalAs(UnmanagedType.I1)]` を指定してください。

### 🪵 ログの取得

入出金はサーバがエラーコードを返さないため、戻り値だけでは失敗の理由が分かりません。
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

### ♻️ DLL のアンロード手順

`FreeLibrary`（C# の `NativeLibrary.Free` / `AssemblyLoadContext` のアンロード、Java の JNI アンロード、
Python の DLL 解放を含む）で **DLL を明示的にアンロードする場合は、次の順序を守ってください。**

1. すべての API 呼び出しが戻っていることを確認する（他スレッドで実行中の呼び出しが 1 つも無い状態にする）
2. `Logout()` を呼ぶ
3. `SetLogCallback(nullptr, ...)` でコールバックを解除する
4. `FreeLibrary` する

- 実行中の呼び出しが残ったままアンロードした場合の動作は**未定義**です。
- `SetLogCallback` は戻った時点で実行中のコールバックが存在しないことを保証します。解除せずにアンロードすると、
  解放済みのコードへコールバックする可能性があります（C# のデリゲートが GC された場合も同様です）。
- `Logout` を省略してもハンドルは解放されますが、サーバ側のセッションが残ります。

> **プロセス終了時にこの手順は不要です。** OS がプロセスごと解放します。

---

## 🚀 クイックスタート

実装サンプルをリポジトリ内に用意しています（`sample_app/` 配下に C++ / C# / Java / Python）。各言語ごとのサンプルを参考にしてください。  
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
| 対応OS | Windows 10 以降（64bit / 32bit） |
| 動作確認OS | Windows 11 Pro 64bit 日本語版 |
| 開発OS | Windows 11 Home 64bit |
| IDE | Visual Studio 2022 / Visual Studio Code / Eclipse |
| 依存ライブラリ | なし（Windows 標準機能のみを使用） |

---

## ⚠️ 注意事項

- `IpatHelper.dll` 本体のソースコードは非公開です
- 本モジュールおよびサンプルアプリの利用によって生じた損害について、作者は一切の責任を負いません
- スマートUMACAへの対応は今後追加予定です
