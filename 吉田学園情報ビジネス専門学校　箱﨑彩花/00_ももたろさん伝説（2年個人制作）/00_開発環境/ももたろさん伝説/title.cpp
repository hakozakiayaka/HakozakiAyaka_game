//=============================================================================
//
// �^�C�g���̏��� [title.h]
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
#include "title.h"					//�^�C�g��
#include "bg.h"					//�w�i
#include "logo.h"					//���S
#include "fade.h"					//�t�F�[�h
#include "sound.h"				//�T�E���h
#include "animal.h"				//���Ƃ�

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
int CTitle::m_nCntTime = 0;						//��ʐ؂�ւ��̃J�E���^�[

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{	//���������Ȃ�
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	CBg::Load();						//�w�i�e�N�X�`���̊��蓖��
	CLogo::Load();					//���S�e�N�X�`���̊��蓖��
	CAnimal::Load();					//���Ƃ��e�N�X�`���̊��蓖��

	//�e�����̐���
	CBg::Create();																													//�w�i
	CLogo::Create();																												//���S
	CAnimal::Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f), CAnimal::ANIMALTYPE_KIJI);		//���Ƃ��i�L�W�j

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	CBg::Unload();									//�w�i�̃e�N�X�`���̔j��
	CLogo::Unload();								//���S�̃e�N�X�`���̔j��
	CAnimal::Unload();							//���Ƃ��̃e�N�X�`���̔j��

	CScene::ReleaseFadeAll();				//�t�F�[�h�ȊO�̃I�u�W�F�N�g�̔j��
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
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

	//��ʐ؂�ւ��̃J�E���^�[
	m_nCntTime++;

	if (pInputKeyboard->GetPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
	{	//�G���^�[�L�[�ƃW���C�R��B�{�^��������
		if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
		}
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);

		if (fade != CFade::FADE_OUT)
		{
			CFade::SetFade(CManager::MODE_TUTORIAL);
		}
	}
	else if (m_nCntTime % 300 == 0)
	{	//5�b�Ԍo�������A�����L���O��ʂɈڍs
		if (fade != CFade::FADE_OUT)
		{
			CFade::SetFade(CManager::MODE_RANKING);
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
void CTitle::Draw(void)
{
}