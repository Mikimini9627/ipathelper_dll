# IpatHelper

**IpatHelper.dll** は [JRA](https://www.jra.go.jp/) の即PAT投票機能を各種プログラムから呼び出すためのWindows用DLLモジュールです。  
中央競馬・地方競馬の両方に対応しており、ログインから馬券購入まで一連のフローをシンプルなAPIで操作できます。

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
- 購入方式: **通常 / フォーメーション / ボックス**
- 式別: **単勝 / 複勝 / 枠連 / ワイド / 馬連 / 馬単 / 三連複 / 三連単** (すべて対応)

---

## 🌏 対応競馬場

### 中央競馬 (JRA)
札幌、函館、福島、新潟、東京、中山、中京、京都、阪神、小倉

### 地方競馬 (NAR)
園田、姫路、名古屋、門別、盛岡、水沢、浦和、船橋、大井、川崎、笠松、金沢、高知、佐賀

### 海外
ロンシャン、シャティン、サンタアニタ、ドーヴィル、チャーチルダウンズ、キングアブドゥルアジーズ

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

// 自動入金フラグの設定
unsigned int SetAutoDepositFlag(const bool bEnable, const unsigned int unDepositValue = 1000,
                                 const unsigned short usConfirmTimeout = 10000);
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

---

## 🚀 クイックスタート

実装サンプルをリポジトリ内に用意しています。各言語ごとのサンプルを参考にしてください。  
Pythonを使う場合は [PyPI](https://pypi.org/project/ipathelper/) からもインストール可能です。

```bash
pip install ipathelper
```

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
