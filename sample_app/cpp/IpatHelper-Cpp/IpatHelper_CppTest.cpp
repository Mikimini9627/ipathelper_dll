#include "IpatHelper.h"
#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

int main()
{
	// DLL が返す文字列 (馬名・レース名等) は UTF-8。既定のコンソール (CP932) の
	// ままだと UTF-8 バイト列がそのまま解釈され文字化けするため、出力コードページを
	// UTF-8 に切り替える。日本語が表示できるフォント (MS ゴシック等) も必要。
	SetConsoleOutputCP(CP_UTF8);

	unsigned int unReturn = 0;

	// ログイン処理(各自自分のIDに変えてください)
	unReturn = Login("********", "********", "****", "****");
	if ((unReturn & 1) != 1) {
		cout << "Login Error" << endl;
		return 1;
	}

	// オッズ取得(馬連・中央競馬/地方競馬に対応)。取得後は必ず ReleaseOddsData で解放する
	ST_ODDS_DATA objOdds = { 0 };
	unReturn = GetOdds((unsigned short)KAISAI::TOKYO, 11, (unsigned char)SHIKIBETSU::QUINELLA, &objOdds);
	if ((unReturn & 1) == 1) {
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

	// 出馬表取得(中央競馬/地方競馬に対応)。取得後は必ず ReleaseRaceCardData で解放する
	// 文字列(szHorseName等)はUTF-8。コンソール表示時は環境の文字コードに注意する
	ST_RACECARD_DATA objRaceCard = { 0 };
	unReturn = GetRaceCard((unsigned short)KAISAI::TOKYO, 11, &objRaceCard);
	if ((unReturn & 1) == 1) {
		cout << "Race Name: " << objRaceCard.szRaceName << endl;
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
	ST_BET_DATA objBetData = { 0 };
	unReturn = GetBetInstance((unsigned char)KAISAI::NAKAYAMA, 11, 2020, 12, 27,
		(unsigned char)HOUSHIKI::FORMATION, (unsigned char)SHIKIBETSU::TRIO, 100, "9-13-7,3,8,10", &objBetData);
	if ((unReturn & 1) != 1) {
		cout << "Get Bet Instance Error" << endl;
		Logout();
		return 1;
	}

	// 馬券購入処理実行
	vector<ST_BET_DATA> vctBetData = {};
	vctBetData.push_back(objBetData);
	unReturn = Bet(vctBetData.data(), (unsigned short)vctBetData.size());
	if ((unReturn & 1) != 1) {
		cout << "Bet Error" << endl;
		Logout();
		return 1;
	}

	// ながし・マルチの購入例(最新DLL対応: 中央・地方・海外すべてで指定可能)
	// 三連単軸1頭ながしマルチ 軸=9 / 相手=3,7,8,10 (中山 11R、100円)。
	// マルチ指定時は生成された objMulti.ucMulti に 1 が設定され、unTotalAmount に合計額が入る。
	ST_BET_DATA objMulti = { 0 };
	unReturn = GetBetInstance((unsigned char)KAISAI::NAKAYAMA, 11, 2020, 12, 27,
		(unsigned char)HOUSHIKI::WHEEL_MULTI_AXIS1, (unsigned char)SHIKIBETSU::TRIFECTA,
		100, "9-3,7,8,10", &objMulti);
	if ((unReturn & 1) == 1) {
		cout << "Multi: multi=" << (int)objMulti.ucMulti
			<< " total=" << objMulti.unTotalAmount << " yen" << endl;
		vector<ST_BET_DATA> vctMulti = { objMulti };
		Bet(vctMulti.data(), (unsigned short)vctMulti.size());
	}

	// 馬券購入用のインスタンス取得(WIN5)
	ST_BET_DATA_WIN5 objBetDataWin5 = { 0 };
	unReturn = GetBetInstanceWin5(100, 2020, 12, 27, "14-9,13-12-2-1,3,4,5", &objBetDataWin5);
	if ((unReturn & 1) != 1) {
		cout << "Get Bet Instance(Win5) Error" << endl;
		Logout();
		return 1;
	}

	// 馬券購入処理実行(Win5)
	unReturn = BetWin5(objBetDataWin5);
	if ((unReturn & 1) != 1) {
		cout << "Bet(Win5) Error" << endl;
		Logout();
		return 1;
	}

	// ログアウト処理実行
	Logout();

	return 0;
}