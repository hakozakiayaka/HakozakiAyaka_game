//=============================================================================
//
// �^�C������ [time.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "main.h"				//���C��
#include "scene.h"				//�V�[��
#include "renderer.h"			//�����_�����O
#include "scene2D.h"			//�V�[��2D
#include "manager.h"			//�}�l�[�W���[
#include "number.h"			//�i���o�[
#include "time.h"					//�^�C��

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
int CTime::m_nTime = 0;
int CTime::m_nTimeData[MAX_TIME] = {};

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TIMERIMIT		(60 * 10)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTime::CTime() : CScene(6)
{
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_apTime[nCntTime] = 0;
	}

	m_nTime = 0;
	m_nTimeState = TIMESTATE_NONE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTime::~CTime()
{
}

//=============================================================================
// ��������
//=============================================================================
CTime * CTime::Create(void)
{
	CTime * pTime = NULL;

	if (pTime == NULL)
	{
		pTime = new CTime;
	}
	if (pTime != NULL)
	{
		pTime->Init();
	}

	return pTime;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTime::Init(void)
{
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_apTime[nCntTime] = new CNumber;
		m_apTime[nCntTime]->Init();
		m_apTime[nCntTime]->SetPosition(D3DXVECTOR3(590.0f, 40.0f, 0.0f), nCntTime);
	}

	m_nTimeState = TIMESTATE_NORMAL;
	m_nTime = TIMERIMIT;
	AddTime();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTime::Uninit(void)
{
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_apTime[nCntTime]->Uninit();

		if (m_apTime[nCntTime] != NULL)
		{
			delete m_apTime[nCntTime];
			m_apTime[nCntTime] = NULL;
		}
	}

	//�������g��j��
	CScene::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTime::Update(void)
{
	switch (m_nTimeState)
	{
	case TIMESTATE_NORMAL:
		break;

	case TIMESTATE_FINISH:
		m_nTime = 0;
		m_nTimeState = TIMESTATE_NONE;
		break;
	}

	if (m_nTimeState == TIMESTATE_NORMAL)
	{
		m_nTime--;

		if ((m_nTime % 60) == 0)
		{
			for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
			{
				AddTime();
				m_apTime[nCntTime]->Update();
				m_apTime[nCntTime]->SetNumber(m_nTimeData[nCntTime]);
			}

			if (m_nTime == 0)
			{
				m_nTimeState = TIMESTATE_FINISH;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTime::Draw(void)
{
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_apTime[nCntTime]->Draw();
	}
}

//=============================================================================
// �^�C���̏���
//=============================================================================
void CTime::AddTime(void)
{
	int nNum = 1000;
	int nNum1 = 100;
	int nCntTime = 0;
	int nTime;

	nTime = m_nTime / 60;			//1�t���[���̌v�Z

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_nTimeData[nCntTime] = (nTime %  nNum) / nNum1;
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}
}