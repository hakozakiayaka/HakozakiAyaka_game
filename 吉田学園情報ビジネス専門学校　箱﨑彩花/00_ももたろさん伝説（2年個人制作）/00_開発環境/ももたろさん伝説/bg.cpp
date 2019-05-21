//=============================================================================
//
// �w�i���� [bg.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "main.h"				//���C��
#include "scene.h"				//�V�[��
#include "renderer.h"			//�����_�����O
#include "scene2D.h"			//�V�[��2D
#include "manager.h"			//�}�l�[�W���[
#include "input.h"				//����
#include "bg.h"					//�w�i

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	 CBg::m_pTexture[MAX_TEXTURE] = {};		//�e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBg::CBg() : CScene(BG_PRIORITY)
{
	m_bgState = BGSTATE_NONE;
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCntBg = 0; nCntBg < MAX_TEXTURE; nCntBg++)
	{
		m_apScene2D[nCntBg] = NULL;
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBg::~CBg()
{	//���������Ȃ�
}

//=============================================================================
// �w�i�̐���
//=============================================================================
CBg *CBg::Create()
{
	CBg *pBg = NULL;

	//�w�i�N���X�̓��I�m��
	if (pBg == NULL)
	{
		pBg = new CBg;
	}

	//�w�i�̏���������
	if (pBg != NULL)
	{
		pBg->Init();
	}

	return pBg;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBg::Init(void)
{
	CManager::MODE BgMode = CManager::GetMode();

	switch (BgMode)
	{
	case CManager::MODE_TITLE:
		if (m_apScene2D[0] == NULL)
		{
			m_apScene2D[0] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();
			m_apScene2D[0]->BindTexture(m_pTexture[0]);								//�e�N�X�`���̊��蓖��
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[0]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		break;

	case CManager::MODE_TUTORIAL:
		if (m_apScene2D[0] == NULL)
		{	//��
			m_apScene2D[0] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();
			m_apScene2D[0]->BindTexture(m_pTexture[1]);					//�e�N�X�`���̊��蓖��
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[0]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		if (m_apScene2D[1] == NULL)
		{	//�R
			m_apScene2D[1] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[1] != NULL)
		{
			m_apScene2D[1]->Init();
			m_apScene2D[1]->BindTexture(m_pTexture[2]);					//�e�N�X�`���̊��蓖��
			m_apScene2D[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[1]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		if (m_apScene2D[2] == NULL)
		{	//�n��
			m_apScene2D[2] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[2] != NULL)
		{
			m_apScene2D[2]->Init();
			m_apScene2D[2]->BindTexture(m_pTexture[4]);					//�e�N�X�`���̊��蓖��
			m_apScene2D[2]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[2]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		if (m_apScene2D[3] == NULL)
		{	//��O�̑�
			m_apScene2D[3] = new CScene2D(5);
		}
		if (m_apScene2D[3] != NULL)
		{
			m_apScene2D[3]->Init();
			m_apScene2D[3]->BindTexture(m_pTexture[8]);					//�e�N�X�`���̊��蓖��
			m_apScene2D[3]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[3]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		if (m_apScene2D[4] == NULL)
		{	//�`���[�g���A��1����
			m_apScene2D[4] = new CScene2D(3);
		}
		if (m_apScene2D[4] != NULL)
		{
			m_apScene2D[4]->Init();
			m_apScene2D[4]->BindTexture(m_pTexture[9]);					//�e�N�X�`���̊��蓖��
			m_apScene2D[4]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[4]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		if (m_apScene2D[5] == NULL)
		{	//�`���[�g���A��2����
			m_apScene2D[5] = new CScene2D(6);
		}
		if (m_apScene2D[5] != NULL)
		{
			m_apScene2D[5]->Init();
			m_apScene2D[5]->BindTexture(m_pTexture[10]);					//�e�N�X�`���̊��蓖��
			m_apScene2D[5]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[5]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		break;

	case CManager::MODE_GAME:
		if (m_apScene2D[0] == NULL)
		{	//��
			m_apScene2D[0] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();
			m_apScene2D[0]->BindTexture(m_pTexture[1]);					//�e�N�X�`���̊��蓖��
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[0]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		if (m_apScene2D[1] == NULL)
		{	//�R
			m_apScene2D[1] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[1] != NULL)
		{
			m_apScene2D[1]->Init();
			m_apScene2D[1]->BindTexture(m_pTexture[2]);					//�e�N�X�`���̊��蓖��
			m_apScene2D[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[1]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		if (m_apScene2D[2] == NULL)
		{	//�n��
			m_apScene2D[2] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[2] != NULL)
		{
			m_apScene2D[2]->Init();
			m_apScene2D[2]->BindTexture(m_pTexture[4]);					//�e�N�X�`���̊��蓖��
			m_apScene2D[2]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[2]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		if (m_apScene2D[3] == NULL)
		{	//��O�̑�
			m_apScene2D[3] = new CScene2D(5);
		}
		if (m_apScene2D[3] != NULL)
		{
			m_apScene2D[3]->Init();
			m_apScene2D[3]->BindTexture(m_pTexture[8]);					//�e�N�X�`���̊��蓖��
			m_apScene2D[3]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[3]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		if (m_apScene2D[4] == NULL)
		{	//�S����
			m_apScene2D[4] = new CScene2D(4);
		}
		if (m_apScene2D[4] != NULL)
		{
			m_apScene2D[4]->Init();
			m_apScene2D[4]->BindTexture(m_pTexture[11]);					//�e�N�X�`���̊��蓖��
			m_apScene2D[4]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[4]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		break;

	case CManager::MODE_GAMECLEAR:
		if (m_apScene2D[0] == NULL)
		{	//�N���A
			m_apScene2D[0] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();
			m_apScene2D[0]->BindTexture(m_pTexture[5]);					//�e�N�X�`���̊��蓖��
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[0]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
			m_apScene2D[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}
		break;

	case CManager::MODE_GAMEOVER:
		if (m_apScene2D[0] == NULL)
		{	//�I�[�o�[
			m_apScene2D[0] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();
			m_apScene2D[0]->BindTexture(m_pTexture[6]);					//�e�N�X�`���̊��蓖��
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[0]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
			m_apScene2D[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}
		break;

	case CManager::MODE_RANKING:
		if (m_apScene2D[0] == NULL)
		{	//�I�[�o�[
			m_apScene2D[0] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();
			m_apScene2D[0]->BindTexture(m_pTexture[7]);					//�e�N�X�`���̊��蓖��
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[0]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		break;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBg::Uninit(void)
{	//�w�i�j��
	for (int nCntBg = 0; nCntBg < MAX_TEXTURE; nCntBg++)
	{
		m_apScene2D[nCntBg]->Uninit();
		m_apScene2D[nCntBg] = NULL;
	}

	//�I�u�W�F�N�g�i�������g�j�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBg::Update(void)
{
	CManager::MODE BgMode = CManager::GetMode();
	CInputKeyboard * pInputKeyboard = NULL;								 //�L�[�{�[�h�N���X�̌Ăяo��
	//D3DXVECTOR3 pos = CBg::GetPos();
	float nSpeed = 10.0f;

	//�W���C�R���̐ݒ�
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	if (pInputKeyboard == NULL)
	{
		pInputKeyboard = CManager::GetInputKeyboard();
	}

	if (BgMode == CManager::MODE_TUTORIAL)
	{
		if (pInputKeyboard->GetPress(DIK_LEFT) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT && CDirectXInput::GetConnectionJoypad() == true))
		{	//�G���^�[�L�[�ƃW���C�R���\���L�[���{�^��������
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				//CSound::PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);

			m_apScene2D[5]->BindTexture(m_pTexture[10]);					//�e�N�X�`���̊��蓖��
			m_apScene2D[5]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[5]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		if (BgMode == CManager::MODE_GAME)
		{
			m_BgMove++;

			m_apScene2D[1]->SetBgMove(m_BgMove, 0.00005f);				//��
			m_apScene2D[2]->SetBgMove(m_BgMove, 0.0005f);				//�R
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
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBg::Draw(void)
{
}

#if 1
//=============================================================================
// �e�N�X�`����ǂݍ���
//=============================================================================
HRESULT CBg::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//�f�o�C�X�̎擾
	CRenderer * pRenderer = CManager::GetRenderer();						//�����_�����O�N���X�̌Ăяo��

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, BG_TITLE, &m_pTexture[0]);							//�^�C�g��
	D3DXCreateTextureFromFile(pDevice, BG_SKY, &m_pTexture[1]);								//��
	D3DXCreateTextureFromFile(pDevice, BG_MOUNTAIN, &m_pTexture[2]);					//�R
	D3DXCreateTextureFromFile(pDevice, BG_FOREST, &m_pTexture[3]);						//��
	D3DXCreateTextureFromFile(pDevice, BG_FIELD, &m_pTexture[4]);							//�n��
	D3DXCreateTextureFromFile(pDevice, BG_GAMECLEAR, &m_pTexture[5]);				//�Q�[���N���A
	D3DXCreateTextureFromFile(pDevice, BG_GAMEOVER, &m_pTexture[6]);					//�Q�[���I�[�o�[
	D3DXCreateTextureFromFile(pDevice, BG_RANKING, &m_pTexture[7]);						//�����L���O
	D3DXCreateTextureFromFile(pDevice, BG_FRONTWEED, &m_pTexture[8]);				//��O�̑�
	D3DXCreateTextureFromFile(pDevice, BG_TUTORIAL01, &m_pTexture[9]);				//�`���[�g���A��1����
	D3DXCreateTextureFromFile(pDevice, BG_TUTORIAL02, &m_pTexture[10]);				//�`���[�g���A��2����
	D3DXCreateTextureFromFile(pDevice, BG_STONE, &m_pTexture[11]);						//�S����

	return S_OK;
}

//=============================================================================
// �e�N�X�`����j��
//=============================================================================
void CBg::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntBg = 0; nCntBg < MAX_TEXTURE; nCntBg++)
	{
		if (m_pTexture[nCntBg] != NULL)
		{
			m_pTexture[nCntBg]->Release();
			m_pTexture[nCntBg] = NULL;
		}
	}
}
#endif