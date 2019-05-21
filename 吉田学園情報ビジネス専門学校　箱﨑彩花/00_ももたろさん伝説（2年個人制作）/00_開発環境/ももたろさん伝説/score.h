//=============================================================================
//
// �X�R�A���� [score.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _SCORE_H_		//��d�C���N���[�h�h�~
#define _SCORE_H_

#include	"main.h"		//���C��
#include	"scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScore;
class CNumber;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DUGIT_NUMBER		(8)
#define RANKING_NUMBER	(5)

//*****************************************************************************
// �X�R�A�N���X
//*****************************************************************************
class CScore : public CScene
{
public:
	typedef enum
	{
		SCOREMODE_NONE = 0,
		SCOREMODE_GAME,
		SCOREMODE_RANKING,
		SCOREMODE_MAX
	} SCOREMODE;

	CScore();																		//�R���X�g���N�^
	virtual ~CScore();														//�f�X�g���N�^
	virtual HRESULT Init(void) = 0;									//����������
	virtual void Uninit(void) = 0;										//�I������
	virtual void Update(void) = 0;										//�X�V����
	virtual void Draw(void) = 0;										//�`�揈��

	void SetScore(int nScore);											//�X�R�A�̐ݒ�
	int GetScore(void);														//�X�R�A���擾

	//�ÓI�����o�֐�
	static void AddScore(int nValue);								//�X�R�A�̉��Z
	static CScore * Create(SCOREMODE mode);				//�X�R�A�̐���

protected:
	static int m_nScore;													//�X�R�A�������
	static int m_nScoreData[DUGIT_NUMBER];				//�v�Z�p�̕ϐ�
};

//*****************************************************************************
// �Q�[���̃X�R�A�N���X
//*****************************************************************************
class CScoreGame : public CScore
{
public:
	CScoreGame();															//�R���X�g���N�^
	~CScoreGame();															//�f�X�g���N�^
	HRESULT Init(void);													//����������
	void Uninit(void);															//�I������
	void Update(void);														//�X�V����
	void Draw(void);															//�`�揈��

private:
	CNumber * m_apNumber[DUGIT_NUMBER];			//[ �X�R�A�̌��� ]
};

//*****************************************************************************
// �����L���O�̃X�R�A�N���X
//*****************************************************************************
class CScoreRanking : public CScore
{
public:
	CScoreRanking();														//�R���X�g���N�^
	~CScoreRanking();														//�f�X�g���N�^
	HRESULT Init(void);													//����������
	void Uninit(void);															//�I������
	void Update(void);														//�X�V����
	void Draw(void);															//�`�揈��
	void SetRanking(int nScore);											//�X�R�A�̐ݒ�

private:
	CNumber * m_apNumber[RANKING_NUMBER][DUGIT_NUMBER];			//[ �X�R�A�̌��� ]
	int m_nChange;
	int m_nChange2;
	int m_nRankingData[RANKING_NUMBER][DUGIT_NUMBER];
	int m_nNewRank;																							//�V�����X�R�A��_��
};

#endif