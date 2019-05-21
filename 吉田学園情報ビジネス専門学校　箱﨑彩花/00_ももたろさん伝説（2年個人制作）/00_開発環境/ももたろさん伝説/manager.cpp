//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include	"manager.h"		//�}�l�[�W���[
#include "main.h"			//���C��
#include "renderer.h"		//�����_�����O
#include "scene.h"			//�V�[��
#include "scene2D.h"		//�V�[��2D
#include "input.h"			//����
#include "game.h"			//�Q�[��
#include "title.h"				//�^�C�g��
#include "tutorial.h"		//�`���[�g���A��
#include "result.h"			//���U���g
#include "ranking.h"		//�����L���O
#include "fade.h"				//�t�F�[�h
#include "sound.h"			//�T�E���h

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CRenderer * CManager::m_pRenderer = NULL;																				//�����_�����O
CInputKeyboard * CManager::m_pInputKeyboard = NULL;																//�L�[�{�[�h
CDirectXInput * CManager::m_pDirectXInput = NULL;																		//�W���C�R��
CFade * CManager::m_pFade = NULL;																								//�t�F�[�h
CTitle * CManager::m_pTitle = NULL;																								//�^�C�g��
CTutorial * CManager::m_pTutorial = NULL;																						//�`���[�g���A��
CGame * CManager::m_pGame = NULL;																							//�Q�[��
CResult * CManager::m_pResult = NULL;																							//���U���g
CRanking * CManager::m_pRanking = NULL;																					//�����L���O
CSound * CManager::m_pSound = NULL;																							//�T�E���h
int CManager::m_nScore = 0;																												//�X�R�A�̏�����
int CManager::m_nHighScore[RANKING_NUMBER] = { 50000, 40000, 30000, 20000, 10000 };		//�X�R�A�̏����l

//���[�h�̐ݒ�
CManager::MODE  CManager::m_mode = MODE_GAME;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{	//���������Ȃ�
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�����_�����O�N���X�̐���
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
	}

	//�����_�����O�̏���������
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Init(hWnd, TRUE);
	}

	//�T�E���h�N���X�̐���
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
	}

	//�T�E���h�N���X�̏���������
	if (m_pSound != NULL)
	{
		m_pSound->Init(hWnd);
	}

	//�L�[�{�[�h�N���X�̐���
	if (m_pInputKeyboard == NULL)
	{
		m_pInputKeyboard = new CInputKeyboard;
	}

	//�L�[�{�[�h�̏���������
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Init(hInstance, hWnd);
	}

	//�W���C�R���N���X�̐���
	if (m_pDirectXInput == NULL)
	{
		m_pDirectXInput = new CDirectXInput;
	}

	//�W���C�R���̏���������
	if (m_pDirectXInput != NULL)
	{
		m_pDirectXInput->Init(hInstance, hWnd);
	}

	//�t�F�[�h�N���X�̐���
	if (m_pFade == NULL)
	{
		m_pFade = new CFade;
	}

	//�t�F�[�h�̏���������
	if (m_pFade != NULL)
	{
		m_pFade->Init();
	}

	//���[�h�̐ݒ�
	CManager::SetMode(m_mode);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{	//������������Ă���

	//�t�F�[�h�N���X�̔j��
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		m_pFade = NULL;
	}

	//�S�ẴI�u�W�F�N�g�̔j��
	CScene::ReleaseAll();

	//�T�E���h�N���X�̔j��
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
	}

	//�W���C�R���N���X�̔j��
	if (m_pDirectXInput != NULL)
	{
		m_pDirectXInput->Uninit();
		delete m_pDirectXInput;
		m_pDirectXInput = NULL;
	}

	//�L�[�{�[�h�N���X�̔j��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//�����_�����O�N���X�̔j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	//�L�[�{�[�h�̍X�V�����i�����΂�ŏ��ɌĂяo���j
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	//�W���C�R���̍X�V�����i�����΂�ŏ��ɌĂяo���j
	if (m_pDirectXInput != NULL)
	{
		m_pDirectXInput->Update();
	}

	// �����_�����O�̍X�V����
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	switch (m_mode)
	{	//�X�V����
	case MODE_TITLE:
		m_pTitle->Update();
		break;

	case MODE_TUTORIAL:
		m_pTutorial->Update();
		break;

	case MODE_GAME:
		m_pGame->Update();
		break;

	case CManager::MODE_GAMECLEAR:
		m_pResult->Update();
		break;

	case CManager::MODE_GAMEOVER:
		m_pResult->Update();
		break;

	case MODE_RANKING:
		m_pRanking->Update();
		break;
	}

	//�t�F�[�h�̍X�V
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	// �����_�����O�̕`�揈��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}

	switch (m_mode)
	{	//�`�揈��
	case MODE_TITLE:
		m_pTitle->Draw();
		break;

	case MODE_TUTORIAL:
		m_pTutorial->Draw();
		break;

	case MODE_GAME:
		m_pGame->Draw();
		break;

	case CManager::MODE_GAMECLEAR:
		m_pResult->Draw();
		break;

	case CManager::MODE_GAMEOVER:
		m_pResult->Draw();
		break;

	case MODE_RANKING:
		m_pRanking->Draw();
		break;
	}

	//�t�F�[�h�̕`�揈��
	if (m_pFade != NULL)
	{
		m_pFade->Draw();
	}
}

//=============================================================================
// ���[�h�̐ݒ�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{	//�I������
	case MODE_TITLE:
		m_pTitle->Uninit();
		//�T�E���h�̒�~
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM000);
		break;

	case MODE_TUTORIAL:
		m_pTutorial->Uninit();
		//�T�E���h�̒�~
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM001);
		break;

	case MODE_GAME:
		m_pGame->Uninit();
		m_pGame = NULL;
		//�T�E���h�̒�~
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM002);
		break;

	case CManager::MODE_GAMECLEAR:
		m_pResult->Uninit();
		//�T�E���h�̒�~
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM003);
		break;

	case CManager::MODE_GAMEOVER:
		m_pResult->Uninit();
		//�T�E���h�̒�~
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM004);
		break;

	case MODE_RANKING:
		m_pRanking->Uninit();
		//�T�E���h�̒�~
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM005);
		break;
	}

	m_mode = mode;

	switch (mode)
	{	//���͏���
	case MODE_TITLE:
		m_pTitle->Init();
		//�T�E���h�Đ�
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM000);
		break;

	case MODE_TUTORIAL:
		m_pTutorial->Init();
		//�T�E���h�Đ�
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM001);
		break;

	case MODE_GAME:
		m_pGame = new CGame;
		m_pGame->Init();
		//�T�E���h�Đ�
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM002);
		break;

	case CManager::MODE_GAMECLEAR:
		m_pResult->Init();
		//�T�E���h�Đ�
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM003);
		break;

	case CManager::MODE_GAMEOVER:
		m_pResult->Init();
		//�T�E���h�Đ�
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM004);
		break;

	case MODE_RANKING:
		m_pRanking->Init();
		//�T�E���h�Đ�
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM005);
		break;
	}
}