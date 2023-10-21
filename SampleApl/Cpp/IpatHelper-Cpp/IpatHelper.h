#ifndef _IPAT_HELPER_H
#define _IPAT_HELPER_H

#define DEPOSIT_DEFAULT_VALUE	1000	// ���������̃f�t�H���g�l(ms)
#define DEFAULT_CONFIRM_TIMEOUT	10000	// �����������̃f�t�H���g�^�C���A�E�g(ms)
#define DEFAULT_BET_TIMEOUT		500		// �n���w���Ԋu�̃f�t�H���g�l

#define WIN5_RACE_COUNT				5	// WIN5�̃��[�X��
#define UMABAN_COLUMN_COUNT			3	// �t�H�[���[�V�����ł̗�
#define UMABAN_TICKET_COLUMN_COUNT	5	// �t�H�[���[�V�����ł̗�(WIN5���܂߂�)

#ifdef	__cplusplus
extern	"C" {
#endif

	/// <summary>
	/// �j��
	/// </summary>
	enum class WEEK_DAY {

		/// <summary>
		/// ���j��
		/// </summary>
		SUNDAY = 1,

		/// <summary>
		/// ���j��
		/// </summary>
		MONDAY,

		/// <summary>
		/// �Ηj��
		/// </summary>
		TUESDAY,

		/// <summary>
		/// ���j��
		/// </summary>
		WEDNESDAY,

		/// <summary>
		/// �ؗj��
		/// </summary>
		THURSDAY,

		/// <summary>
		/// ���j��
		/// </summary>
		FRIDAY,

		/// <summary>
		/// �y�j��
		/// </summary>
		SATURDAY
	};

	/// <summary>
	/// �m��t���O
	/// </summary>
	enum class DECISIONFLAG {

		DEFAULT = 1,
		NORMAL,
		DEADLINE,
		CANCEL,
		FLATMATESCANCEL,
		HIT,
		MISS,
		BACK,
		PARTCANCEL,
		INVALID,
		SALECANCEL
	};

	/// <summary>
	/// �w���t���O
	/// </summary>
	enum class BET_FLAG {

		/// <summary>
		/// �ʏ�
		/// </summary>
		NORMAL,

		/// <summary>
		/// WIN%
		/// </summary>
		WIN5,

		/// <summary>
		/// �C�O
		/// </summary>
		INTERNATIONAL
	};

	/// <summary>
	/// �J�Ï�
	/// </summary>
	enum class KAISAI {

		/// <summary>
		/// �D�y
		/// </summary>
		SAPPORO,

		/// <summary>
		/// ����
		/// </summary>
		HAKODATE,

		/// <summary>
		/// ����
		/// </summary>
		FUKUSHIMA,

		/// <summary>
		/// �V��
		/// </summary>
		NIIGATA,

		/// <summary>
		/// ����
		/// </summary>
		TOKYO,

		/// <summary>
		/// ���R
		/// </summary>
		NAKAYAMA,

		/// <summary>
		/// ����
		/// </summary>
		CHUKYO,

		/// <summary>
		/// ���s
		/// </summary>
		KYOTO,

		/// <summary>
		/// ��_
		/// </summary>
		HANSHIN,

		/// <summary>
		/// ���q
		/// </summary>
		KOKURA,

		/// <summary>
		/// ���c
		/// </summary>
		SONODA,

		/// <summary>
		/// �P�H
		/// </summary>
		HIMEJI,

		/// <summary>
		/// ���É�
		/// </summary>
		NAGOYA,

		/// <summary>
		/// ���
		/// </summary>
		MONBETSU,

		/// <summary>
		/// ����
		/// </summary>
		MORIOKA,

		/// <summary>
		/// ����
		/// </summary>
		MIZUSAWA,

		/// <summary>
		/// �Y�a
		/// </summary>
		URAWA,

		/// <summary>
		/// �D��
		/// </summary>
		FUNABASHI,

		/// <summary>
		/// ���
		/// </summary>
		OI,

		/// <summary>
		/// ���
		/// </summary>
		KAWASAKI,

		/// <summary>
		/// �}��
		/// </summary>
		KASAMATSU,

		/// <summary>
		/// ����
		/// </summary>
		KANAZAWA,

		/// <summary>
		/// ���m
		/// </summary>
		KOCHI,

		/// <summary>
		/// ����
		/// </summary>
		SAGA,

		/// <summary>
		/// �����V����
		/// </summary>
		LONGCHAMP,

		/// <summary>
		/// ���C�_��
		/// </summary>
		MEYDAN,

		/// <summary>
		/// �V���e�B��
		/// </summary>
		SHATIN,

		/// <summary>
		/// �h�[���B��
		/// </summary>
		DEAUVILE,

		/// <summary>
		/// �`���[�`���_�E���Y
		/// </summary>
		CHURCHILLDOWNS
	};

	/// <summary>
	/// ����
	/// </summary>
	enum class HOUSHIKI {

		/// <summary>
		/// �ʏ�
		/// </summary>
		NORMAL,

		/// <summary>
		/// �t�H�[���[�V����
		/// </summary>
		FORMATION,

		/// <summary>
		/// �{�b�N�X
		/// </summary>
		BOX
	};

	/// <summary>
	/// ����
	/// </summary>
	enum class SHIKIBETSU {

		/// <summary>
		/// �P��
		/// </summary>
		WIN = 1,

		/// <summary>
		/// ����
		/// </summary>
		PLACE,

		/// <summary>
		/// �g�A
		/// </summary>
		BRACKETQUINELLA,

		/// <summary>
		/// ���C�h
		/// </summary>
		QUINELLAPLACE,

		/// <summary>
		/// �n�A
		/// </summary>
		QUINELLA,

		/// <summary>
		/// �n�P
		/// </summary>
		EXACTA,

		/// <summary>
		/// �O�A��
		/// </summary>
		TRIO,

		/// <summary>
		/// �O�A�P
		/// </summary>
		TRIFECTA
	};

	/// <summary>
	/// �w�������
	/// </summary>
	enum class DAY_TYPE {

		/// <summary>
		/// ����
		/// </summary>
		TODAY = 1,

		/// <summary>
		/// �O��
		/// </summary>
		BEFORE
	};

	/// <summary>
	/// �߂�l
	/// </summary>
	enum class RETURN_VALUE {

		/// <summary>
		/// �����ɐ���
		/// </summary>
		SUCCESS = 0b00000001,

		/// <summary>
		/// �����Ɏ��s
		/// </summary>
		UNSUCCESS = 0b00000010,

		/// <summary>
		/// �������n�ł̏����Ɏ��s
		/// </summary>
		FAILED_CHUOU = 0b00000100,

		/// <summary>
		/// �n�����n�ł̏����Ɏ��s
		/// </summary>
		FAILED_CHIHOU = 0b00001000,

		/// <summary>
		/// �ʐM�Ɏ��s(IPAT���X�|���X�G���[)
		/// </summary>
		FAILED_COMMUNICATE = 0b00010000
	};

	/// <summary>
	/// �n���ڍ׏��
	/// </summary>
	struct ST_TICKET_DATA_DETAIL {

		/// <summary>
		/// �m��t���O
		/// </summary>
		unsigned char ucDecisionFlag;

		/// <summary>
		/// �w���t���O
		/// </summary>
		unsigned char ucBetFlag;

		/// <summary>
		/// �J�Ï�
		/// </summary>
		unsigned short usKaisai;

		/// <summary>
		/// ���[�X�ԍ�
		/// </summary>
		unsigned char ucRaceNo;

		/// <summary>
		/// �T
		/// </summary>
		unsigned char ucWeek;

		/// <summary>
		/// �j��
		/// </summary>
		unsigned char ucYoubi;

		/// <summary>
		/// ����
		/// </summary>
		unsigned char ucMethod;

		/// <summary>
		/// ����
		/// </summary>
		unsigned char ucType;

		/// <summary>
		/// ������
		/// </summary>
		unsigned int unHorse[UMABAN_TICKET_COLUMN_COUNT];

		/// <summary>
		/// �}���`���ǂ���
		/// </summary>
		unsigned char ucMulti;
	};

	/// <summary>
	/// �n����{���
	/// </summary>
	struct ST_TICKET_DATA {

		/// <summary>
		/// �w�����t���O
		/// </summary>
		unsigned char ucDayFlag;

		/// <summary>
		/// ���No
		/// </summary>
		unsigned char ucReceiptNo;

		/// <summary>
		/// ����(H)
		/// </summary>
		unsigned char ucHour;

		/// <summary>
		/// ����(M)
		/// </summary>
		unsigned char ucMinute;

		/// <summary>
		/// ���z
		/// </summary>
		unsigned int unKingaku;

		/// <summary>
		/// �����߂�
		/// </summary>
		unsigned int unPayout;

		/// <summary>
		/// �ڍ׏��
		/// </summary>
		unsigned int unDetailCount;

		/// <summary>
		/// �ڍ׏��
		/// </summary>
		ST_TICKET_DATA_DETAIL* pobjDetail;
	};

	/// <summary>
	/// �n���w������
	/// </summary>
	struct ST_PURCHASE_DATA {

		/// <summary>
		/// �c�w���\��
		/// </summary>
		unsigned short usRemainBetCount;

		/// <summary>
		/// �c��
		/// </summary>
		unsigned int unBalance;

		/// <summary>
		/// ����w�����z
		/// </summary>
		unsigned int unDayPurchase;

		/// <summary>
		/// ������ߋ��z
		/// </summary>
		unsigned int unDayPayout;

		/// <summary>
		/// ���v�w�����z
		/// </summary>
		unsigned int unTotalPurchase;

		/// <summary>
		/// ���v���ߋ��z
		/// </summary>
		unsigned int unTotalPayout;

		/// <summary>
		/// �n�����
		/// </summary>
		unsigned int unTicketCount;

		/// <summary>
		/// �n���w������
		/// </summary>
		ST_TICKET_DATA* pobjTicketData;
	};

	/// <summary>
	/// �n���w�����
	/// </summary>
	struct ST_BET_DATA {

		/// <summary>
		/// �J�Ï�
		/// </summary>
		unsigned short usPlace;

		/// <summary>
		/// ���[�X�ԍ�
		/// </summary>
		unsigned char ucRaceNo;

		/// <summary>
		/// �j��
		/// </summary>
		unsigned char ucYoubi;

		/// <summary>
		/// ����
		/// </summary>
		unsigned char ucHoushiki;

		/// <summary>
		/// ����
		/// </summary>
		unsigned char ucShikibetsu;

		/// <summary>
		/// ���z
		/// </summary>
		unsigned int unKingaku;

		/// <summary>
		/// �n��
		/// </summary>
		unsigned int unUmaban[UMABAN_COLUMN_COUNT];

		/// <summary>
		/// ���v�w���z
		/// </summary>
		unsigned int unTotalAmount;
	};

	/// <summary>
	/// �n���w�����(WIN5)
	/// </summary>
	struct ST_BET_DATA_WIN5 {

		/// <summary>
		/// �w�����z
		/// </summary>
		unsigned int unKingaku;

		/// <summary>
		/// �j��
		/// </summary>
		unsigned char ucYoubi;

		/// <summary>
		/// �n��
		/// </summary>
		unsigned int unUmaban[WIN5_RACE_COUNT];
	};

	/// <summary>
	/// I-PAT�փ��O�C�����܂��B
	/// </summary>
	/// <param name="szINetId">I-NET ID</param>
	/// <param name="szId">���O�C��ID</param>
	/// <param name="szPassword">�p�X���[�h</param>
	/// <param name="szPars">P-ARS�ԍ�</param>
	/// <returns></returns>
	unsigned int Login(
		const char szINetId[],
		const char szId[],
		const char szPassword[],
		const char szPars[]
	);

	/// <summary>
	/// I-PAT���烍�O�A�E�g���܂��B
	/// </summary>
	/// <returns></returns>
	unsigned int Logout(
	);

	/// <summary>
	/// �o�^��������������܂��B
	/// </summary>
	/// <param name="unDepositValue">�����z</param>
	/// <returns></returns>
	unsigned int Deposit(
		const unsigned int unDepositValue
	);

	/// <summary>
	/// �o�^�����֏o�����܂��B
	/// </summary>
	/// <returns></returns>
	unsigned int Withdraw(
	);

	/// <summary>
	/// <para>�n���w���������擾���܂��B</para>
	/// <para>�g�p��͕K��ReleasePurchaseData���g�p���ĉ�����Ă��������B</para>
	/// </summary>
	/// <param name="pobjStatus">
	/// <para>�n���w������</para>
	/// <para>ST_PURCHASE_DATA�͗Ⴆ�Έȉ��̂悤�ȍ\���ƂȂ��Ă��܂��B</para>
	/// <para>ST_PURCHASE_DATA</para>
	/// <para>����ST_TICKET_DATA[1]</para>
	/// <para>��  ����ST_TICKET_DATA_DETAIL[1]</para>
	/// <para>��  ����ST_TICKET_DATA_DETAIL[2]</para>
	/// <para>����ST_TICKET_DATA[2]</para>
	/// <para>��  ����ST_TICKET_DATA_DETAIL[1]</para>
	/// <para>��  ����ST_TICKET_DATA_DETAIL[2]</para>
	/// <para>��  ����ST_TICKET_DATA_DETAIL[3]</para>
	/// <para>����ST_TICKET_DATA[3]</para>
	/// <para>��  ����ST_TICKET_DATA_DETAIL[1]</para>
	/// <para>����ST_TICKET_DATA[4]</para>
	/// <para>    ����ST_TICKET_DATA_DETAIL[1]</para>
	/// <para>    ����ST_TICKET_DATA_DETAIL[2]</para>
	/// <para>    ����ST_TICKET_DATA_DETAIL[3]</para>
	/// <para>    ����ST_TICKET_DATA_DETAIL[4]</para>
	/// <para>    ����ST_TICKET_DATA_DETAIL[5]</para>
	/// </param>
	/// <returns></returns>
	unsigned int GetPurchaseData(
		ST_PURCHASE_DATA* pobjStatus
	);

	/// <summary>
	/// <para>�n���w��������������܂��B</para>
	/// <para>GetPurchaseData�̉ۂɈ˂炸�K�����s���Ă��������B</para>
	/// </summary>
	/// <param name="objStatus">�n���w������</param>
	void ReleasePurchaseData(
		ST_PURCHASE_DATA objStatus
	);

	/// <summary>
	/// �n���w�������擾���܂��B
	/// </summary>
	/// <param name="usPlace">�J�Ï�</param>
	/// <param name="ucRaceNo">���[�X�ԍ�</param>
	/// <param name="usYear">�J�ÔN</param>
	/// <param name="ucMonth">�J�Ì�</param>
	/// <param name="ucDay">�J�Ó�</param>
	/// <param name="ucHoushiki">����</param>
	/// <param name="ucShikibetsu">����</param>
	/// <param name="nKingaku">���z</param>
	/// <param name="szKaime">������</param>
	/// <param name="pobjBetData">�n���w�����</param>
	/// <returns></returns>
	unsigned int GetBetInstance(
		const unsigned short usPlace,
		const unsigned char ucRaceNo,
		const unsigned short usYear,
		const unsigned char ucMonth,
		const unsigned char ucDay,
		const unsigned char ucHoushiki,
		const unsigned char ucShikibetsu,
		const unsigned int nKingaku,
		const char szKaime[],
		ST_BET_DATA* pobjBetData
	);

	/// <summary>
	/// <para>�n�����w�����܂��B</para>
	/// <para>GetBetInstance�Ŏ擾�����\���̂̔z����w�肷�邱�Ƃňꊇ�ōw�����邱�Ƃ��\�ł��B</para>
	/// <para>�z��̗v�f���Ƃɍw�����s���܂����A�Ԋu���Z���ꍇ�w���Ɏ��s����\��������܂��B</para>
	/// <para>�l�b�g���[�N���ɂ���ĊԊu�͈قȂ�܂����AusWaitMilliSeconds�ɔC�ӂ̐��l���w�肷�邱�ƂŒ������\�ł��B</para>
	/// </summary>
	/// <param name="pobjBetData">�n���w�����(�z��)</param>
	/// <param name="usBetCount">�z��</param>
	/// <param name="usWaitMilliSeconds">�n���w���Ԋu(ms)</param>
	/// <returns></returns>
	unsigned int Bet(
		const ST_BET_DATA pobjBetData[],
		const unsigned short usBetCount,
		const unsigned short usWaitMilliSeconds = DEFAULT_BET_TIMEOUT
	);

	/// <summary>
	/// �n���w�����(WIN5)���擾���܂��B
	/// </summary>
	/// <param name="unKingaku">�w�����z</param>
	/// <param name="usYear">�J�ÔN</param>
	/// <param name="ucMonth">�J�Ì�</param>
	/// <param name="ucDay">�J�Ó�</param>
	/// <param name="szKaime">������</param>
	/// <param name="pobjBetData">�n���w�����(WIN5)</param>
	/// <returns></returns>
	unsigned int GetBetInstanceWin5(
		const unsigned int unKingaku,
		const unsigned short usYear,
		const unsigned char ucMonth,
		const unsigned char ucDay,
		const char szKaime[],
		ST_BET_DATA_WIN5* pobjBetData
	);

	/// <summary>
	/// <para>�n��(WIN5)���w�����܂��B</para>
	/// <para>GetBetInstanceWin5�Ŏ擾�����\���̂��w�肷�邱�Ƃňꊇ�ōw�����邱�Ƃ��\�ł��B</para>
	/// <para>�g�ݍ��킹���Ƃɍw�����s���܂����A�Ԋu���Z���ꍇ�w���Ɏ��s����\��������܂��B</para>
	/// <para>�l�b�g���[�N���ɂ���ĊԊu�͈قȂ�܂����AusWaitMilliSeconds�ɔC�ӂ̐��l���w�肷�邱�ƂŒ������\�ł��B</para>
	/// </summary>
	/// <param name="objBetData">�n���w�����(WIN5)</param>
	/// <param name="usWaitMilliSeconds">�n���w���Ԋu</param>
	/// <returns></returns>
	unsigned int BetWin5(
		const ST_BET_DATA_WIN5 objBetData,
		const unsigned short usWaitMilliSeconds = DEFAULT_BET_TIMEOUT
	);

	/// <summary>
	/// <para>���������ݒ���s���܂��B</para>
	/// <para>�����������������ǂ�����usConfirmTimeout(ms)��ɍēx�m�F���܂��B</para>
	/// <para>�w������̂ɏ\���ȓ���������Ă���ꍇ�̂ݍw���Ɉڂ�܂��B</para>
	/// </summary>
	/// <param name="bEnable">�L���ɂ��邩�ǂ���</param>
	/// <param name="unDepositValue">���������z</param>
	/// <param name="usConfirmTimeout">�m�F�^�C���A�E�g</param>
	/// <returns></returns>
	unsigned int SetAutoDepositFlag(
		const bool bEnable,
		const unsigned int unDepositValue = DEPOSIT_DEFAULT_VALUE,
		const unsigned short usConfirmTimeout = DEFAULT_CONFIRM_TIMEOUT
	);

#ifdef __cplusplus
}
#endif

#endif
