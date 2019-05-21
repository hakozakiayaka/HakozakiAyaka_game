//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _MANEGER_H_		//��d�C���N���[�h�h�~
#define _MANEGER_H_

#include	"main.h"				//���C��
#include "score.h"				//�X�R�A

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;					//�����_�����O
class CInputKeyboard;		//�L�[�{�[�h
class CDirectXInput;			//�W���C�R��
class CFade;						//�t�F�[�h
class CTitle;							//�^�C�g��
class CTutorial;					//�`���[�g���A��
class CGame;						//�Q�[��
class CResult;						//���U���g
class CRanking;					//�����L���O
class CSound;						//�T�E���h
class CScore;						//�X�R�A

//*****************************************************************************
// �}�l�[�W���[�N���X
//*****************************************************************************
class CManager
{
public:
	typedef enum
	{	//���[�h�̎��
		MODE_TITLE = 0,																										//�^�C�g��
		MODE_TUTORIAL,																										//�`���[�g���A��
		MODE_GAME,																												//�Q�[��
		MODE_GAMECLEAR,																									//�Q�[���N���A
		MODE_GAMEOVER,																									//�Q�[���I�[�o�[
		MODE_RANKING,																										//�����L���O
		MODE_MAX																												//���[�h�̍ő吔
	} MODE;

	CManager();																													//�R���X�g���N�^
	~CManager();																													//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);						//����������
	void Uninit(void);																												//�I������
	void Update(void);																											//�X�V����
	void Draw(void);																												//�`�揈��

	//�ÓI�����o�֐�
	static void SetMode(MODE mode);																				//���[�h�̐ݒ菈��
	static void SetScore(int nScore) { m_nScore = nScore; }												//�X�R�A�̐ݒ菈��

	//�ÓI�����o�ϐ�
	static CRenderer * GetRenderer(void) { return m_pRenderer; }										//�����_�����O�N���X�ɒl��Ԃ�
	static CInputKeyboard * GetInputKeyboard(void) { return m_pInputKeyboard; }			//�L�[�{�[�h�N���X�ɒl��Ԃ�
	static CDirectXInput * GetDirectXInput(void) { return m_pDirectXInput; }					//�W���C�R���N���X�ɒl��Ԃ�
	static CFade * GetFade(void) { return m_pFade; }															//�t�F�[�h�N���X�ɒl��Ԃ�
	static CTitle * GetTitle(void) { return m_pTitle; }															//�^�C�g���N���X�ɒl��Ԃ�
	static CTutorial * GetTutorial(void) { return m_pTutorial; }												//�`���[�g���A���N���X�ɒl��Ԃ�
	static CGame * GetGame(void) { return m_pGame; }														//�Q�[���N���X�ɒl��Ԃ�
	static CResult * GetResult(void) { return m_pResult; }													//���U���g�N���X�ɒl��Ԃ�
	static CRanking * GetRanking(void) { return m_pRanking; }											//�����L���O�N���X�ɒl��Ԃ�
	static CSound * GetSound(void) { return m_pSound; }													//�T�E���h�N���X�ɒl��Ԃ�
	static MODE GetMode(void) { return m_mode; }															//���[�h�̎擾
	static int GetScore(void) { return m_nScore; }																//�X�R�A�̎擾

	static int m_nHighScore[RANKING_NUMBER];

private:
	//�ÓI�����o�ϐ�
	static MODE m_mode;																									//���[�h�̐ݒ�
	static CRenderer * m_pRenderer;																					//�����_�����O�N���X�̎擾
	static CInputKeyboard * m_pInputKeyboard;																	//�L�[�{�[�h�N���X�̎擾
	static CDirectXInput * m_pDirectXInput;																		//�W���C�R���N���X�̎擾
	static CFade * m_pFade;																									//�t�F�[�h�N���X�̎擾
	static CTitle * m_pTitle;																									//�^�C�g���N���X�̎擾
	static CTutorial * m_pTutorial;																						//�`���[�g���A���N���X�̎擾
	static CGame * m_pGame;																								//�Q�[���N���X�̎擾
	static CResult * m_pResult;																							//���U���g�N���X�̎擾
	static CRanking * m_pRanking;																						//�����L���O�N���X�̎擾
	static CSound * m_pSound;																							//�T�E���h�N���X�̎擾
	static int  m_nScore;

};

#endif