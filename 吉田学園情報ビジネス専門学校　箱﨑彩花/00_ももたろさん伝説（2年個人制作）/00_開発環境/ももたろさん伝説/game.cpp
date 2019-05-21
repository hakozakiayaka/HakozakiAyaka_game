//=============================================================================
//
// �Q�[���̏��� [game.h]
// Author : �����ʉ�
//
//=============================================================================
#include "main.h"				//���C��
#include "scene.h"				//�V�[��
#include "renderer.h"			//�����_�����O
#include "scene2D.h"			//�V�[��2D
#include "manager.h"			//�}�l�[�W���[
#include "input.h"				//����
#include "player.h"				//�v���C���[
#include "bullet.h"				//�e
#include "explosion.h"			//����
#include "enemy.h"				//�G
#include "score.h"				//�X�R�A
#include "effect.h"				//�G�t�F�N�g
#include "bg.h"					//�w�i
#include "number.h"			//�i���o�[
#include "game.h"				//�Q�[��
#include "fade.h"					//�t�F�[�h
#include "pause.h"				//�|�[�Y
#include "life.h"					//���C�t

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CPlayer * CGame::m_pPlayer = NULL;																		//�v���C���[
CAnimal * CGame::m_pAnimal = NULL;																		//���Ƃ�
CEnemy * CGame::m_pEnemy = NULL;																		//�G�l�~�[
CNumber * CGame::m_pNumber = NULL;																	//�X�R�A
CPause * CGame::m_pPause = NULL;																		//�|�[�Y
CScore * CGame::m_pScore = NULL;																		//�X�R�A
int CGame::m_nCntTime = 0;																						//

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{	//���������Ȃ�
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(void)
{
	//�e�N�X�`���̊��蓖��
	CBg::Load();						//�w�i�e�N�X�`���̊��蓖��
	CPlayer::Load();					//�v���C���[�̃e�N�X�`���̊��蓖��
	CAnimal::Load();					//���Ƃ��̃e�N�X�`���̊��蓖��
	CEnemy::Load();					//�G�l�~�[�̃e�N�X�`���̊��蓖��
	CBullet::Load();					//�e�̃e�N�X�`���̊��蓖��
	CExplosion::Load();				//�����e�N�X�`���̊��蓖��
	CNumber::Load();				//�i���o�[�̃e�N�X�`���̊��蓖��
	CEffect::Load();					//�G�t�F�N�g�̃e�N�X�`���̊��蓖��
	CPause::Load();					//�|�[�Y�̃e�N�X�`���̊��蓖��

	//��������
	CBg::Create();																																										//�w�i
	m_pScore = CScore::Create(CScore::SCOREMODE_GAME);																							//�X�R�A
	m_pPause = CPause::Create();																																			//�|�[�Y
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(200.0f, 430.0f, 0.0f));																				//�v���C���[
	m_pAnimal = CAnimal::Create(D3DXVECTOR3(250.0f, 450.0f, 0.0f), CAnimal::ANIMALTYPE_DOG);								//���Ƃ��i�ŏ��̓C�k�j

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(1000.0f, 500.0f, 0.0f), CEnemy::ENEMYTYPE_RED);				//�ԋS
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(950.0f, 500.0f, 0.0f), CEnemy::ENEMYTYPE_RED);				//�ԋS

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(800.0f, 450.0f, 0.0f), CEnemy::ENEMYTYPE_BLUE);				//�S
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(600.0f, 400.0f, 0.0f), CEnemy::ENEMYTYPE_RED);				//�S
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(900.0f, 400.0f, 0.0f), CEnemy::ENEMYTYPE_YELLOW);		//�S

	return S_OK;
}

//=============================================================================
// �I������
//===========================================================================
void CGame::Uninit(void)
{
	CPause::Unload();					//�|�[�Y�̃e�N�X�`���̔j��
	CBg::Unload();							//�w�i�̃e�N�X�`���̔j��
	CNumber::Unload();				//�i���o�[�̃e�N�X�`���̔j��
	CEffect::Unload();					//�G�t�F�N�g�̃e�N�X�`���̔j��
	CExplosion::Unload();				//�����e�N�X�`���̔j��
	CBullet::Unload();					//�e�e�N�X�`���̔j��
	CAnimal::Unload();					//���Ƃ��e�N�X�`���̔j��
	CPlayer::Unload();					//�v���C���[�̃e�N�X�`���̔j��
	CEnemy::Unload();					//�G�l�~�[�̃e�N�X�`���̔j��

	if (m_pAnimal != NULL)
	{	//���Ƃ��̔j��
		m_pAnimal = NULL;
	}
	if (m_pEnemy != NULL)
	{	//�G�l�~�[�̔j��
		m_pEnemy = NULL;
	}
	if (m_pPlayer != NULL)
	{	//�v���C���[�̔j��
		m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}
	if (m_pScore != NULL)
	{	//�X�R�A�̔j��
		m_pScore->Uninit();
		m_pScore = NULL;
	}
	if (m_pPause != NULL)
	{	//�|�[�Y�̔j��
		m_pPause->Uninit();
		m_pPause = NULL;
	}

	CScene::ReleaseFadeAll();		//�t�F�[�h�ȊO�̃I�u�W�F�N�g�̔j��
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	CInputKeyboard * pInputKeyboard = NULL;								//�L�[�{�[�h�N���X�̌Ăяo��
	CManager::MODE pManager = CManager::GetMode();			//���[�h�̎擾
	CFade::FADE fade = CFade::GetFade();										//�t�F�[�h�̎擾
	bool bPause = CPause::GetPause();

	//�W���C�R���̐ݒ�
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	if (pInputKeyboard == NULL)
	{
		pInputKeyboard = CManager::GetInputKeyboard();
	}

	////�^�C���̃J�E���^�[
	//m_nCntTime++;

	//if (m_nCntTime % 60 == 0)
	//{
	//	m_pEnemy = CEnemy::Create(D3DXVECTOR3(1000.0f, 500.0f, 0.0f), CEnemy::ENEMYTYPE_RED);				//�ԋS
	//}
	//if (m_nCntTime % 120 == 0)
	//{
	//	m_pEnemy = CEnemy::Create(D3DXVECTOR3(900.0f, 500.0f, 0.0f), CEnemy::ENEMYTYPE_BLUE);				//�S
	//}
	//if (m_nCntTime % 240 == 0)
	//{
	//	m_pEnemy = CEnemy::Create(D3DXVECTOR3(700.0f, 300.0f, 0.0f), CEnemy::ENEMYTYPE_RED);				//�ԋS
	//}

	//�|�[�Y����
	if (pInputKeyboard->GetTrigger(DIK_P) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_START && CDirectXInput::GetConnectionJoypad() == true))
	{
		if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
		{
			bPause = bPause ? false : true;
			CPause::SetPause(bPause);
		}
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
	}

	if (m_pPause != NULL)
	{
		if (bPause == true)
		{
			m_pPause->Update();
		}
	}

	//�������Ƃ̘g�����ɕK�v�i�^�C�g���A�Q�[���A�A�Ƃ��j
	if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_PUSH)
	{
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_NONE);
	}
	else if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NONE)
	{
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_NOTPUSH);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
}