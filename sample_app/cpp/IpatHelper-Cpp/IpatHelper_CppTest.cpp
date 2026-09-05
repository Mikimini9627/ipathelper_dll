#include "IpatHelper.h"
#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

// 戻り値は RETURN_VALUE のビットフラグ。SUCCESS が立っているかで成否を判定する
static bool isSuccess(unsigned int unReturn)
{
	return (unReturn & (unsigned int)RETURN_VALUE::SUCCESS) != 0;
}

// DLL 内部のログを受け取るコールバック。入出金はサーバがエラーコードを返さないため、
// 失敗の原因を知るにはこのコールバックが唯一の手段になる。
// 呼び出し規約は __cdecl。コールバックの中から本 DLL の API を呼び返さないこと(デッドロックする)。
static void __cdecl onLog(int nLevel, const char* pszMessage)
{
	static const char* aszLevel[] = { "TRACE", "INFO", "WARN", "ERROR" };
	cout << "[" << aszLevel[nLevel] << "] " << pszMessage << endl; // pszMessage は UTF-8
}

int main()
{
	// DLL が返す文字列 (馬名・レース名等) は UTF-8。既定のコンソール (CP932) の
	// ままだと UTF-8 バイト列がそのまま解釈され文字化けするため、出力コードページを
	// UTF-8 に切り替える。日本語が表示できるフォント (MS ゴシック等) も必要。
	SetConsoleOutputCP(CP_UTF8);

	// ログの取得を開始する(調査時は LOG_LEVEL_TRACE)
	SetLogCallback(onLog, LOG_LEVEL_INFO);

	unsigned int unReturn = 0;

	// ログイン処理(各自自分のIDに変えてください)
	unReturn = Login("********", "********", "****", "****");
	if (!isSuccess(unReturn)) {
		if (unReturn & (unsigned int)RETURN_VALUE::FAILED_OUT_OF_SERVICE) {
			// 投票受付時間外またはメンテナンス中。即座に再試行しても必ず失敗する
			cout << "Login Error (out of service)" << endl;
		}
		else {
			cout << "Login Error" << endl;
		}
		SetLogCallback(nullptr, LOG_LEVEL_INFO);
		return 1;
	}

	// お知らせ取得。取得後は必ず ReleaseNoticeData で解放する
	ST_NOTICE_DATA objNotice = { 0 };
	unReturn = GetNotice(&objNotice);
	if (isSuccess(unReturn)) {
		if (objNotice.szMessage[0] != '\0') {
			cout << "Notice: " << objNotice.szMessage << endl; // 強制表示お知らせ(UTF-8)
		}
		for (unsigned int i = 0; i < objNotice.unItemCount; i++) {
			const ST_NOTICE_ITEM& item = objNotice.pobjItem[i];
			cout << "  " << item.szDate << " " << item.szTitle << " " << item.szUrl << endl;
		}
	}
	ReleaseNoticeData(&objNotice);

	// オッズ取得(馬連・中央競馬/地方競馬/海外競馬に対応)。取得後は必ず ReleaseOddsData で解放する
	// 海外開催は中央競馬へのログインが必要で、枠が無いため枠連は指定できない
	ST_ODDS_DATA objOdds = { 0 };
	unReturn = GetOdds((unsigned short)KAISAI::TOKYO, 11, (unsigned char)SHIKIBETSU::QUINELLA, &objOdds);
	if (isSuccess(unReturn)) {
		cout << "Odds Time: " << objOdds.szOddsTime << " / Count: " << objOdds.unDetailCount << endl;
		for (unsigned int i = 0; i < objOdds.unDetailCount; i++) {
			const ST_ODDS_DETAIL& detail = objOdds.pobjDetail[i];
			cout << "  " << (int)detail.ucHorse1 << "-" << (int)detail.ucHorse2 << " : ";
			if (detail.ucStatus == 0) {
				cout << (detail.unOdds / 10.0) << endl; // 実際の倍率 = unOdds / 10.0
			}
			else {
				cout << "status=" << (int)detail.ucStatus << endl; // 1:cancel 2:unacquired
			}
		}
	}
	ReleaseOddsData(&objOdds);

	// 出馬表取得(中央競馬/地方競馬/海外競馬に対応)。取得後は必ず ReleaseRaceCardData で解放する
	// 文字列(szHorseName等)はUTF-8。コンソール表示時は環境の文字コードに注意する
	// 海外開催は取得できる項目が少なく、馬番・馬名・単勝人気・単勝/複勝オッズとレース名のみ
	// (枠番・性齢・馬体重・騎手・斤量・調教師は 0 または空文字になる)
	ST_RACECARD_DATA objRaceCard = { 0 };
	unReturn = GetRaceCard((unsigned short)KAISAI::TOKYO, 11, &objRaceCard);
	if (isSuccess(unReturn)) {
		cout << "Race Name: " << objRaceCard.szRaceName << endl;
		// ucRaceStatus は RACE_STATUS_ON_SALE(0) / CLOSED(1) / CANCELED(2) / BEFORE_SALE(3) / UNKNOWN(0xFF)
		cout << "Deadline: " << objRaceCard.szDeadline << " / Status: " << (int)objRaceCard.ucRaceStatus << endl;
		cout << "Odds Time: " << objRaceCard.szOddsTime << " / Entries: " << objRaceCard.unEntryCount << endl;
		for (unsigned int i = 0; i < objRaceCard.unEntryCount; i++) {
			const ST_ENTRY_DETAIL& entry = objRaceCard.pobjEntry[i];
			cout << "  " << (int)entry.ucUmaban << " " << entry.szHorseName
				<< " " << entry.szSex << (int)entry.ucAge
				<< " burden=" << (entry.usBurden / 10.0)
				<< " jockey=" << entry.szJockeyName
				<< " win=";
			if (entry.ucWinOddsStatus == 0) {
				cout << (entry.unWinOdds / 10.0); // 実際の倍率 = unWinOdds / 10.0
			}
			else {
				cout << "-"; // 1:発売中止 2:未取得
			}
			cout << " popular=" << (int)entry.usWinPopular << endl;
		}
	}
	ReleaseRaceCardData(&objRaceCard);

	// 馬券購入用のインスタンス取得
	// 金額は100円単位。1回の送信あたりの合計購入金額は MAX_TOTAL_AMOUNT_PER_SEND(1,000,000円)が上限。
	// 買い目の馬番は1〜18(海外は1〜24)。範囲外や方式・式別と列数が合わない買い目は失敗する。
	ST_BET_DATA objBetData = { 0 };
	unReturn = GetBetInstance((unsigned short)KAISAI::NAKAYAMA, 11, 2020, 12, 27,
		(unsigned char)HOUSHIKI::FORMATION, (unsigned char)SHIKIBETSU::TRIO, 100, "9-13-7,3,8,10", &objBetData);
	if (!isSuccess(unReturn)) {
		cout << "Get Bet Instance Error" << endl;
		Logout();
		SetLogCallback(nullptr, LOG_LEVEL_INFO);
		return 1;
	}

	// 馬券購入処理実行
	// 第3引数は分割送信の「間隔」(ms)でタイムアウトではない。既定は DEFAULT_BET_INTERVAL(500ms)。
	vector<ST_BET_DATA> vctBetData = {};
	vctBetData.push_back(objBetData);
	unReturn = Bet(vctBetData.data(), (unsigned short)vctBetData.size());
	if (!isSuccess(unReturn)) {
		cout << "Bet Error" << endl;
		Logout();
		SetLogCallback(nullptr, LOG_LEVEL_INFO);
		return 1;
	}

	// ながし・マルチの購入例(中央・地方・海外すべてで指定可能)
	// 三連単軸1頭ながしマルチ 軸=9 / 相手=3,7,8,10 (中山 11R、100円)。
	// マルチ指定時は生成された objMulti.ucMulti に 1 が設定され、unTotalAmount に合計額が入る。
	ST_BET_DATA objMulti = { 0 };
	unReturn = GetBetInstance((unsigned short)KAISAI::NAKAYAMA, 11, 2020, 12, 27,
		(unsigned char)HOUSHIKI::WHEEL_MULTI_AXIS1, (unsigned char)SHIKIBETSU::TRIFECTA,
		100, "9-3,7,8,10", &objMulti);
	if (isSuccess(unReturn)) {
		cout << "Multi: multi=" << (int)objMulti.ucMulti
			<< " total=" << objMulti.unTotalAmount << " yen" << endl;
		vector<ST_BET_DATA> vctMulti = { objMulti };
		Bet(vctMulti.data(), (unsigned short)vctMulti.size());
	}

	// 馬券購入用のインスタンス取得(WIN5)
	ST_BET_DATA_WIN5 objBetDataWin5 = { 0 };
	unReturn = GetBetInstanceWin5(100, 2020, 12, 27, "14-9,13-12-2-1,3,4,5", &objBetDataWin5);
	if (!isSuccess(unReturn)) {
		cout << "Get Bet Instance(Win5) Error" << endl;
		Logout();
		SetLogCallback(nullptr, LOG_LEVEL_INFO);
		return 1;
	}

	// 馬券購入処理実行(Win5)
	unReturn = BetWin5(objBetDataWin5);
	if (!isSuccess(unReturn)) {
		cout << "Bet(Win5) Error" << endl;
		Logout();
		SetLogCallback(nullptr, LOG_LEVEL_INFO);
		return 1;
	}

	// WIN5のセレクト/ランダム購入(中央競馬のみ)。
	// 買い目はサーバが生成してそのまま購入されるため、内容を事前に確認することはできない。
	// 実際に購入されるので、有効化する前に必ず利用者の確認を取ること。
	//
	// unReturn = BetWin5Auto((unsigned char)WIN5_AUTO_SELECT, "3,0,7,0,12", 5, 100, 2020, 12, 27);

	// ログアウト処理実行
	Logout();

	// コールバックを解除してから終了する(DLLを明示的にアンロードする場合は必須)
	SetLogCallback(nullptr, LOG_LEVEL_INFO);

	return 0;
}
