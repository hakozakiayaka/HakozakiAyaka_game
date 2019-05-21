//=============================================================================
//
// �`���[�g���A������ [tutorial.h]
// Author : �����ʉ�
//
//=============================================================================
#include "main.h"				//���C��
#include "scene.h"				//�V�[��
#include "renderer.h"			//�����_�����O
#include "scene2D.h"			//�V�[��2D
#include "manager.h"			//�}�l�[�W���[
#include "input.h"				//����
#include "game.h"				//�Q�[��
#include "tutorial.h"			//�`���[�g���A��
#include "bg.h"					//�w�i
#include "logo.h"					//���S
#include "fade.h"					//�t�F�[�h
#include "sound.h"				//�T�E���h
#include "player.h"				//�v���C���[
#include "animal.h"				//���Ƃ�
#include "bullet.h"				//�e
#include "explosion.h"			//����
#include "effect.h"				//�G�t�F�N�g

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{	//���������Ȃ�
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTutorial::Init(void)
{
	CBg::Load();						//�w�i�e�N�X�`���̊��蓖��
	CLogo::Load();					//���S�e�N�X�`���̊��蓖��
	CPlayer::Load();					//�v���C���[�̃e�N�X�`�����蓖��
	CAnimal::Load();					//���Ƃ��e�N�X�`���̊��蓖��
	CBullet::Load();					//�e�̃e�N�X�`���̊��蓖��
	CExplosion::Load();				//�����e�N�X�`���̊��蓖��
	CEffect::Load();					//�G�t�F�N�g�̃e�N�X�`���̊��蓖��

	//�e�����̐���
	CBg::Create();																																	//�w�i�̐���
	CLogo::Create();																																//���S
	CAnimal::Create(D3DXVECTOR3(250.0f, 450.0f, 0.0f), CAnimal::ANIMALTYPE_DOG);				//���Ƃ�
	CPlayer::Create(D3DXVECTOR3(200.0f, 430.0f, 0.0f));											//�v���C���[

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTutorial::Uninit(void)
{
	CBg::Unload();									//�w�i�̃e�N�X�`���̔j��
	CLogo::Unload();								//���S�̃e�N�X�`���̔j��
	CPlayer::Unload();							//�v���C���[�̃e�N�X�`���̔j��
	CAnimal::Unload();							//���Ƃ��̃e�N�X�`���̔j��
	CBullet::Unload();							//�e�e�N�X�`���̔j��
	CExplosion::Unload();						//�����e�N�X�`���̔j��
	CEffect::Unload();							//�G�t�F�N�g�̃e�N�X�`���̔j��

	CScene::ReleaseFadeAll();				//�t�F�[�h�ȊO�̃I�u�W�F�N�g�̔j��
}

//=============================================================================
// �X�V����
//=============================================================================
void CTutorial::Update(void)
{
	CInputKeyboard * pInputKeyboard = NULL;								 //�L�[�{�[�h�N���X�̌Ăяo��
	CManager::MODE pManager = CManager::GetMode();			 //���[�h���擾����
	CFade::FADE fade = CFade::GetFade();										//�t�F�[�h�̎擾

	//�W���C�R���̐ݒ�
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	if (pInputKeyboard == NULL)
	{
		pInputKeyboard = CManager::GetInputKeyboard();
	}

	if (pInputKeyboard->GetPress(DIK_P) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
	{	//�G���^�[�L�[�ƃW���C�R��B�{�^��������
		if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
		}
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);

		if (fade != CFade::FADE_OUT)
		{
			CFade::SetFade(CManager::MODE_GAME);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTutorial::Draw(void)
{
}