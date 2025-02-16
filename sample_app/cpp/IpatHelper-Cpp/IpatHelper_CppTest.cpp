#include "IpatHelper.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	unsigned int unReturn = 0;
	
	//���O�C������(�e��������ID�ɕς��Ă�������)
	unReturn = Login("********", "********", "****", "****");
	if ((unReturn & 1) != 1) {
		cout << "Login Error" << endl;
		return 1;
	}

	//�n���w���p�̃C���X�^���X�擾
	ST_BET_DATA objBetData = { 0 };
	unReturn = GetBetInstance((unsigned char)KAISAI::NAKAYAMA, 11, 2020, 12, 27,
		(unsigned char)HOUSHIKI::FORMATION, (unsigned char)SHIKIBETSU::TRIO, 100, "9-13-7,3,8,10", &objBetData);
	if ((unReturn & 1) != 1) {
		cout << "Get Bet Instance Error" << endl;
		Logout();
		return 1;
	}

	//�n���w���������s
	vector<ST_BET_DATA> vctBetData = {};
	vctBetData.push_back(objBetData);
	unReturn = Bet(vctBetData.data(), (unsigned short)vctBetData.size());
	if ((unReturn & 1) != 1) {
		cout << "Bet Error" << endl;
		Logout();
		return 1;
	}

	//�n���w���p�̃C���X�^���X�擾(WIN5)
	ST_BET_DATA_WIN5 objBetDataWin5 = { 0 };
	unReturn = GetBetInstanceWin5(100, 2020, 12, 27, "14-9,13-12-2-1,3,4,5", &objBetDataWin5);
	if ((unReturn & 1) != 1) {
		cout << "Get Bet Instance(Win5) Error" << endl;
		Logout();
		return 1;
	}

	//�n���w���������s(Win5)
	unReturn = BetWin5(objBetDataWin5);
	if ((unReturn & 1) != 1) {
		cout << "Bet(Win5) Error" << endl;
		Logout();
		return 1;
	}

	//���O�A�E�g�������s
	Logout();

	return 0;
}