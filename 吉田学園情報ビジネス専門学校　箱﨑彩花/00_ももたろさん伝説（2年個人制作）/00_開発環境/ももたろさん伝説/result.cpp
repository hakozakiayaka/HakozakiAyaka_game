//=============================================================================
//
// ���U���g�̏��� [result.h]
// Author : �����ʉ�
//
//=============================================================================
#include "main.h"				//���C��
#include "scene.h"				//�V�[��
#include "renderer.h"			//�����_�����O
#include "scene2D.h"			//�V�[��2D
#include "manager.h"			//�}�l�[�W���[
#include "input.h"				//����
#include "result.h"				//�^�C�g��
#include "bg.h"					//�w�i
#include "fade.h"					//�t�F�[�h
#include "logo.h"					//���S
#include "sound.h"				//�T�E���h

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult::CResult()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult::~CResult()
{	//���������Ȃ�
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init(void)
{
	CBg::Load();						//�w�i�e�N�X�`���̊��蓖��
	CLogo::Load();					//���S�e�N�X�`���̊��蓖��

	//�e�����̐���
	CBg::Create();						//�w�i
	CLogo::Create();					//���S

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
	CBg::Unload();									//�w�i�̃e�N�X�`���̔j��
	CLogo::Unload();								//���S�̃e�N�X�`���̔j��

	CScene::ReleaseFadeAll();				//�t�F�[�h�ȊO�̃I�u�W�F�N�g�̔j��
}

//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update(void)
{
	CInputKeyboard * pInputKeyboard = NULL;								//�L�[�{�[�h�N���X�̌Ăяo��
	CManager::MODE pManager = CManager::GetMode();			//���[�h���擾����
	CFade::FADE fade = CFade::GetFade();										//�t�F�[�h�̌Ăяo��

	//�W���C�R���̐ݒ�
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	if (pInputKeyboard == NULL)
	{
		pInputKeyboard = CManager::GetInputKeyboard();
	}

	if (pInputKeyboard->GetPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
	{
		if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
		}
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);

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
void CResult::Draw(void)
{
}