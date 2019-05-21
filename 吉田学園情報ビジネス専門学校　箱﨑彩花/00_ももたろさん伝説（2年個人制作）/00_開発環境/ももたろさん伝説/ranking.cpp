//=============================================================================
//
// �����L���O���� [ranking.h]
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
#include "ranking.h"			//�����L���O
#include "bg.h"					//�w�i
#include "logo.h"					//���S
#include "fade.h"					//�t�F�[�h
#include "sound.h"				//�T�E���h
#include "score.h"				//�X�R�A
#include "number.h"			//�i���o�[

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
int CRanking::m_nCntTime = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRanking::CRanking()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRanking::~CRanking()
{	//���������Ȃ�
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRanking::Init(void)
{
	CNumber::Load();
	CBg::Load();						//�w�i�e�N�X�`���̊��蓖��
	CLogo::Load();

	//�e�����̐���
	CBg::Create();						//�w�i�̐���
	CLogo::Create();
	CScore::Create(CScore::SCOREMODE_RANKING);		//�X�R�A

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRanking::Uninit(void)
{
	CNumber::Unload();
	CBg::Unload();									//�w�i�̃e�N�X�`���̔j��
	CLogo::Unload();								//���S�̃e�N�X�`���̔j��

	CScene::ReleaseFadeAll();				//�t�F�[�h�ȊO�̃I�u�W�F�N�g�̔j��
}

//=============================================================================
// �X�V����
//=============================================================================
void CRanking::Update(void)
{
	CInputKeyboard * pInputKeyboard = NULL;								 //�L�[�{�[�h�N���X�̌Ăяo��
	CManager::MODE pManager = CManager::GetMode();			 //���[�h���擾����
	CFade::FADE fade = CFade::GetFade();

	//�W���C�R���̐ݒ�
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	//��ʐ؂�ւ��̃J�E���^�[
	m_nCntTime++;

	if (pInputKeyboard == NULL)
	{
		pInputKeyboard = CManager::GetInputKeyboard();
	}

	if (pInputKeyboard->GetPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
	{	//�G���^�[�L�[�A�W���C�R��B�{�^���A5�b�Ԃ�����
		if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
		}
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);

		if (fade != CFade::FADE_OUT)
		{
			CFade::SetFade(CManager::MODE_TITLE);
		}
	}
	if (m_nCntTime % 180 == 0)
	{	//��ʐ؂�ւ��i�����L���O����^�C�g���j
		if (fade != CFade::FADE_OUT)
		{
			CFade::SetFade(CManager::MODE_TITLE);
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
void CRanking::Draw(void)
{
}