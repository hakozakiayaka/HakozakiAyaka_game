//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include <time.h>
#include "main.h"				//���C��
#include "scene.h"				//�V�[��
#include "renderer.h"			//�����_�����O
#include "manager.h"			//�}�l�[�W���[
#include "number.h"			//�i���o�[
#include "score.h"				//�X�R�A

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
int CScore::m_nScore = 0;
int CScore::m_nScoreData[DUGIT_NUMBER] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScore::CScore() : CScene(6)
{
	for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{	//�X�R�A�̏�����
		m_nScoreData[nCntScore] = NULL;
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScore::~CScore()
{
	m_nScore = 0;
}

//=============================================================================
// ��������
//=============================================================================
CScore * CScore::Create(SCOREMODE mode)
{
	CScore * pScore = NULL;

	switch (mode)
	{
	case SCOREMODE_GAME:							//�Q�[��
		pScore = new CScoreGame;
		pScore->Init();
		break;

	case SCOREMODE_RANKING:					//�����L���O
		pScore = new CScoreRanking;
		pScore->Init();
		break;
	}

	return pScore;
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}

#if 1
//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void CScore::AddScore(int nValue)
{
	int nNum = 100000000;			//�����������炩����
	int nNum1 = 10000000;			//�����������炩����
	int nCntScore;

	m_nScore += nValue;

	for (nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{
		m_nScoreData[nCntScore] = m_nScore %  nNum / nNum1;
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}
}

//=============================================================================
// �Q�[���̃R���X�g���N�^
//=============================================================================
CScoreGame::CScoreGame()
{
	for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{	//�Q�[�����̃X�R�A������
		m_apNumber[nCntScore] = NULL;
	}
}

//=============================================================================
// �Q�[���̃f�X�g���N�^
//=============================================================================
CScoreGame::~CScoreGame()
{
	for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{	//�Q�[�����J��Ԃ����Ƃ��ɃX�R�A���c��Ȃ��悤�ɂ����
		m_apNumber[nCntScore] = 0;
	}
}

//=============================================================================
// �Q�[���̏���������
//=============================================================================
HRESULT CScoreGame::Init(void)
{
	for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{
		m_apNumber[nCntScore] = new CNumber;
		m_apNumber[nCntScore]->Create();																								//��������
		m_apNumber[nCntScore]->Init();																									//������
		m_apNumber[nCntScore]->SetPosition(D3DXVECTOR3(900.0f, 40.0f, 0.0f), nCntScore);			//�Q�[���X�R�A�̈ʒu��ݒ�
	}
	return S_OK;
}

//=============================================================================
// �Q�[���̏I������
//=============================================================================
void CScoreGame::Uninit(void)
{
	//�Q�[�����I�������烉���L���O�ɃX�R�A��n��
	CManager::SetScore(m_nScore);

	for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{	//�I������
		m_apNumber[nCntScore]->Uninit();

		if (m_apNumber[nCntScore] != NULL)
		{
			delete m_apNumber[nCntScore];			//�������̊J��
			m_apNumber[nCntScore] = NULL;
		}
	}

	//�������g��j��
	CScene::Release();
}

//=============================================================================
// �Q�[���̍X�V����
//=============================================================================
void CScoreGame::Update(void)
{
	for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{	//�e�N�X�`���̍X�V
		m_apNumber[nCntScore]->SetNumber(m_nScoreData[nCntScore]);
	}
}

//=============================================================================
// �Q�[���̕`�揈��
//=============================================================================
void CScoreGame::Draw(void)
{
	for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{	//�`�揈��
		m_apNumber[nCntScore]->Draw();
	}
}

//=============================================================================
// �����L���O�̃R���X�g���N�^
//=============================================================================
CScoreRanking::CScoreRanking()
{
	//rand�g��
	srand((unsigned int)time(0));

	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
		{
			m_apNumber[nCntRank][nCntScore] = NULL;
			m_nRankingData[nCntRank][nCntScore] = NULL;
		}
	}

	//�v�Z�p�̕ϐ��̏�����
	m_nChange = 0;
	m_nChange2 = 0;
	m_nNewRank = 5;
}

//=============================================================================
// �����L���O�̃f�X�g���N�^
//=============================================================================
CScoreRanking::~CScoreRanking()
{
}

//=============================================================================
// �����L���O�̏���������
//=============================================================================
HRESULT CScoreRanking::Init(void)
{
	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
		{
			m_apNumber[nCntRank][nCntScore] = CNumber::Create();																											//�i���o�[�̐���
			m_apNumber[nCntRank][nCntScore]->Init();																																	//������
			m_apNumber[nCntRank][nCntScore]->SetPosition(D3DXVECTOR3(500.0f, 180.0f + (110.0f * nCntRank), 0.0f), nCntScore);		//�ʒu�ݒ�
		}
	}

	m_nScore = 0;

	//�X�R�A�̌Ăяo��
	SetRanking(CManager::GetScore());

	return S_OK;
}

//=============================================================================
// �����L���O�̏I������
//=============================================================================
void CScoreRanking::Uninit(void)
{
	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
		{
			if (m_apNumber[nCntRank][nCntScore] != NULL)
			{	//�I������
				m_apNumber[nCntRank][nCntScore]->Uninit();
				delete m_apNumber[nCntRank][nCntScore];			//�������̊J��
				m_apNumber[nCntRank][nCntScore] = NULL;
			}
		}
	}

	//�������g��j��
	CScene::Release();
}

//=============================================================================
// �����L���O�̍X�V����
//=============================================================================
void CScoreRanking::Update(void)
{
	//rand�g������
	int nColRand = rand() % 10 + 1;
	float fColRand = nColRand * 0.1f;

	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
		{
			if (m_nNewRank < 5)
			{
				m_apNumber[m_nNewRank][nCntScore]->SetColor(D3DXCOLOR(1.0f, fColRand, fColRand, 1.0f));
			}
		}
	}
}

//=============================================================================
// �����L���O�̕`�揈��
//=============================================================================
void CScoreRanking::Draw(void)
{
	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
		{	//�`�揈��
			m_apNumber[nCntRank][nCntScore]->Draw();
		}
	}
}

//=============================================================================
// �����L���O�̐ݒ菈��
//=============================================================================
void CScoreRanking::SetRanking(int nScore)
{
	int nNum = 100000000;
	int nNum1 = 10000000;

	m_nScore = nScore;

	//�n�C�X�R�A�ƌ��݂̃n�C�X�R�A���ׂ�
	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		if (CManager::m_nHighScore[nCntRank] < m_nScore)
		{
			m_nChange = CManager::m_nHighScore[nCntRank];		//�O��̃n�C�X�R�A�����u��
			CManager::m_nHighScore[nCntRank] = m_nScore;			//���u���̃n�C�X�R�A�Ɣ�ׂāA����̃n�C�X�R�A����

			//���ʂ̍X�V���L�^
			m_nNewRank = nCntRank;

			//���ʂ̓���ւ�
			for (int nCntSortRank = nCntRank + 1; nCntSortRank < RANKING_NUMBER; nCntSortRank++)
			{
				m_nChange2 = CManager::m_nHighScore[nCntSortRank];				//�������������ʂ̎��̏��ʂ����u��
				CManager::m_nHighScore[nCntSortRank] = m_nChange;				//�󂢂��Ƃ����1��̏��ʂ���
				m_nChange = m_nChange2;																//�ŏI�I�ȃX�R�A�̑��
			}
			break;
		}
	}

	//�����L���O��ʂ̃X�R�A�X�V
	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
		{
			m_nRankingData[nCntRank][nCntScore] = (CManager::m_nHighScore[nCntRank] % nNum) / nNum1;
			m_apNumber[nCntRank][nCntScore]->SetNumber(m_nRankingData[nCntRank][nCntScore]);

			nNum = nNum / 10;
			nNum1 = nNum1 / 10;

			if (nCntScore == DUGIT_NUMBER - 1)
			{	//�i���I������珉��������
				nNum = 100000000;
				nNum1 = 10000000;
			}
		}
	}

	//�X�R�A�̏�����
	CManager::SetScore(0);
}

#endif