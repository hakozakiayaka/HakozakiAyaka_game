//=============================================================================
//
// �|�[�Y���� [pause.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "main.h"				//���C��
#include "scene.h"				//�V�[��
#include "renderer.h"			//�����_�����O
#include "scene2D.h"			//�V�[��2D
#include "manager.h"			//�}�l�[�W���[
#include "input.h"				//����
#include "fade.h"					//�t�F�[�h
#include "pause.h"				//�w�i
#include "sound.h"				//�T�E���h

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	 CPause::m_pTexture[PAUSE_TEXTURE] = {};		//�e�N�X�`���̃|�C���^
CScene2D * CPause::m_apScene2D[PAUSE_TEXTURE] = {};						//�|���S���Ǘ�
bool CPause::m_bPause = false;																	//�\�����Ă��Ȃ���Ԃɂ���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPause::CPause() : CScene(PAUSE_PRIORITY)
{
	m_PauseState = PAUSESTATE_NONE;
	m_PauseColor = PAUSECOLOR_NONE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPause::~CPause()
{	//���������Ȃ�
}

//=============================================================================
// �|���S���̐���
//=============================================================================
CPause *CPause::Create()
{
	CPause * pPause = NULL;

	//�|�[�Y�N���X�̓��I�m��
	if (pPause == NULL)
	{
		pPause = new CPause;
	}

	if (pPause != NULL)
	{
		pPause->Init();																	//������
		pPause->SetObjType(CScene::OBJTYPE_PAUSE);			//�I�u�W�F�N�g�^�C�v�̐ݒ�
	}

	//2��ڈȍ~�ŏ��̉�ʂ��|�[�Y�ɂȂ�Ȃ��悤�ɂ���
	m_bPause = false;

	return pPause;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPause::Init(void)
{
	for (int nCntPause = 0; nCntPause < PAUSE_TEXTURE; nCntPause++)
	{
		if (nCntPause == 0)
		{	//��ʑS�̂��������ɂȂ�i�}�X�N�j
			if (m_apScene2D[nCntPause] == NULL)
			{
				m_apScene2D[nCntPause] = new CScene2D(PAUSE_PRIORITY);
			}
			if (m_apScene2D[nCntPause] != NULL)
			{
				m_apScene2D[nCntPause]->Init();
				m_apScene2D[nCntPause]->SetObjType(CScene::OBJTYPE_PAUSE);				//�I�u�W�F�N�g�^�C�v�̐ݒ�
				m_apScene2D[nCntPause]->BindTexture(m_pTexture[nCntPause]);					//�e�N�X�`���̊��蓖��
				m_apScene2D[nCntPause]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);		//�T�C�Y�ݒ�
				m_apScene2D[nCntPause]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));			//�F�̐ݒ�
			}
		}
		else if (nCntPause == 1)
		{	//�|�[�Y���j���[�̔w�i
			if (m_apScene2D[nCntPause] == NULL)
			{
				m_apScene2D[nCntPause] = new CScene2D(PAUSE_PRIORITY);
			}
			if (m_apScene2D[nCntPause] != NULL)
			{
				m_apScene2D[nCntPause]->Init();
				m_apScene2D[nCntPause]->SetObjType(CScene::OBJTYPE_PAUSE);
				m_apScene2D[nCntPause]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
				m_apScene2D[nCntPause]->BindTexture(m_pTexture[nCntPause]);																				//�e�N�X�`���̊��蓖��
				m_apScene2D[nCntPause]->SetSize(400.0f, 400.0f);																										//�T�C�Y�ݒ�
			}
		}
		else
		{	//�Â���A���Ȃ����A�^�C�g���ɖ߂�
			if (m_apScene2D[nCntPause] == NULL)
			{
				m_apScene2D[nCntPause] = new CScene2D(PAUSE_PRIORITY);
			}
			if (m_apScene2D[nCntPause] != NULL)
			{
				m_apScene2D[nCntPause]->Init();
				m_apScene2D[nCntPause]->SetObjType(CScene::OBJTYPE_PAUSE);
				m_apScene2D[nCntPause]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 235.0f + (125.0f * (nCntPause - 2)), 0.0f));
				m_apScene2D[nCntPause]->BindTexture(m_pTexture[nCntPause]);																				//�e�N�X�`���̊��蓖��
				m_apScene2D[nCntPause]->SetSize(200.0f, 100.0f);																											//�T�C�Y�ݒ�
			}
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPause::Uninit(void)
{	//�w�i�j��
	for (int nCntPause = 0; nCntPause < PAUSE_TEXTURE; nCntPause++)
	{
		m_apScene2D[nCntPause]->Uninit();
		m_apScene2D[nCntPause] = NULL;
	}

	//�I�u�W�F�N�g�i�������g�j�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPause::Update(void)
{
	CInputKeyboard * pInputKeyboard = NULL;
	CFade::FADE fade = CFade::GetFade();

	//�W���C�R���̐ݒ�
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	if (pInputKeyboard == NULL)
	{
		pInputKeyboard = CManager::GetInputKeyboard();
	}

	if (m_bPause == true)
	{
		if (pInputKeyboard->GetTrigger(DIK_DOWN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && CDirectXInput::GetConnectionJoypad() == true) || (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
		{	// �L�[�{�[�h���L�[(��)�A�W���C�R���\���L�[���A�W���C�R��9�X�e�B�b�N��������
			CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				m_SelectNum = (m_SelectNum + 1) % 3;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		if (pInputKeyboard->GetTrigger(DIK_UP) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP && CDirectXInput::GetConnectionJoypad() == true) || (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
		{	// �L�[�{�[�h���L�[(��)�A�W���C�R���\���L�[���A�W���C�R��9�X�e�B�b�N��������
			CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				m_SelectNum = (m_SelectNum + 2) % 3;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}

		if (m_SelectNum == 0)
		{	//�Â���
			m_PauseColor = PAUSECOLOR_CONTINUE;

			// ����L�[�������ꂽ���ǂ���
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
			{	//�G���^�[�L�[�ƃW���C�R��B�{�^��������
				CSound::PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
				if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
				{
					m_PauseState = PAUSESTATE_CONTINUE;
				}
				CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
			}
		}
		if (m_SelectNum == 1)
		{	//���Ȃ���
			m_PauseColor = PAUSECOLOR_RETRY;

			// ����L�[�������ꂽ���ǂ���
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
			{	//�G���^�[�L�[�ƃW���C�R��B�{�^��������
				CSound::PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
				if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
				{
					if (fade != CFade::FADE_OUT)
					{
						m_PauseState = PAUSESTATE_RETRY;
					}
				}
				CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
			}
		}
		if (m_SelectNum == 2)
		{	//�^�C�g���ɖ߂�
			m_PauseColor = PAUSECOLOR_QUIT;

			// ����L�[�������ꂽ���ǂ���
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
			{	//�G���^�[�L�[�ƃW���C�R��B�{�^��������
				CSound::PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
				if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
				{
					if (fade != CFade::FADE_OUT)
					{
						m_PauseState = PAUSESTATE_QUIT;
					}
				}
				CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
			}
		}

		switch (m_PauseState)
		{	//�|�[�Y�̃X�e�[�g�Ǘ�
		case PAUSESTATE_NONE:
			break;

		case PAUSESTATE_CONTINUE:
			m_PauseState = PAUSESTATE_NONE;
			SetPause(false);
			break;

		case PAUSESTATE_RETRY:
			m_PauseState = PAUSESTATE_NONE;

			if (fade != CFade::FADE_OUT)
			{	// �t�F�[�h���[�h�ݒ�
				CFade::SetFade(CManager::MODE_GAME);
			}
			break;

		case PAUSESTATE_QUIT:
			m_PauseState = PAUSESTATE_NONE;

			if (fade != CFade::FADE_OUT)
			{	// �t�F�[�h���[�h�ݒ�
				CFade::SetFade(CManager::MODE_TITLE);
			}
			break;
		}

		switch (m_PauseColor)
		{	//���j���[�I�����̐F�Ǘ�
		case PAUSECOLOR_NONE:
			break;

		case PAUSECOLOR_CONTINUE:
			m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apScene2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			break;

		case PAUSECOLOR_RETRY:
			m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apScene2D[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			break;

		case PAUSECOLOR_QUIT:
			m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPause::Draw(void)
{
}

//=============================================================================
// �|�[�Y�̐ݒ�
//=============================================================================
void CPause::SetPause(bool bPause)
{
	m_bPause = bPause;
}

#if 1
//=============================================================================
// �e�N�X�`����ǂݍ���
//=============================================================================
HRESULT CPause::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//�f�o�C�X�̎擾
	CRenderer * pRenderer = CManager::GetRenderer();						//�����_�����O�N���X�̌Ăяo��

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "", &m_pTexture[0]);												//�Q�[����ʂ𔼓���
	D3DXCreateTextureFromFile(pDevice, PAUSE_PAUSEMENU, &m_pTexture[1]);			//���j���[�̔w�i
	D3DXCreateTextureFromFile(pDevice, PAUSE_CONTINUE, &m_pTexture[2]);				//�Â���
	D3DXCreateTextureFromFile(pDevice, PAUSE_RETRY, &m_pTexture[3]);						//���Ȃ���
	D3DXCreateTextureFromFile(pDevice, PAUSE_QUIT, &m_pTexture[4]);							//�^�C�g���ɖ߂�

	return S_OK;
}

//=============================================================================
// �e�N�X�`����j��
//=============================================================================
void CPause::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntPause = 0; nCntPause < PAUSE_TEXTURE; nCntPause++)
	{
		if (m_pTexture[nCntPause] != NULL)
		{
			m_pTexture[nCntPause]->Release();
			m_pTexture[nCntPause] = NULL;
		}
	}
}
#endif