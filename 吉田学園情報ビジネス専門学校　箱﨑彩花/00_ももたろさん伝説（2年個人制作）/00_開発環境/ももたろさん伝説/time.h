//=============================================================================
//
// �^�C������ [time.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _TIME_H_		//��d�C���N���[�h�h�~
#define _TIME_H_

#include	"main.h"		//���C��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TIME			(3)

//*****************************************************************************
// �X�R�A�N���X
//*****************************************************************************
class CTime : public CScene
{
public:
	//�^�C���̏��
	typedef enum
	{
		TIMESTATE_NONE = 0,
		TIMESTATE_NORMAL,											//�ʏ���
		TIMESTATE_FINISH,												//�I�����
		TIMESTATE_MAX
	} TIMESTATE;

	CTime();																		//�R���X�g���N�^
	~CTime();																	//�f�X�g���N�^
	HRESULT Init(void);													//����������
	void Uninit(void);															//�I������
	void Update(void);														//�X�V����
	void Draw(void);															//�`�揈��
	void AddTime(void);													//�^�C���̏���

	//�ÓI�����o�֐�
	static CTime * Create(void);										//�X�R�A�̐���

private:
	CNumber * m_apTime[MAX_TIME];
	static int m_nTime;
	static int m_nTimeData[MAX_TIME];
	int m_nTimeState;												//��ԊǗ��̃J�E���^�[
};

#endif