//=============================================================================
//
// �v���C���[���� [player.cpp]
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
#include "animal.h"				//���Ƃ�
#include "sound.h"				//�T�E���h

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene2D(4)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{	//���������Ȃ�
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = NULL;

	//�v���C���[�N���X�̓��I�m��
	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
	}
	if(pPlayer != NULL)
	{
		pPlayer->Init();
		pPlayer->SetPosition(pos);							//�ʒu�̐ݒ�
		pPlayer->m_bJump = true;									//�W�����v���Ă��Ȃ���Ԃɂ���

		//�e�N�X�`���̊��蓖��
		pPlayer->BindTexture(m_pTexture);
	}

	return pPlayer;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init()
{
	CBullet * pBullet = NULL;

	CScene2D::Init();

	//�I�u�W�F�N�g�̐ݒ�
	CScene2D::SetObjType(CScene::OBJTYPE_PLAYER);

	//�v���C���[�̃T�C�Y��ݒ�
	SetSize(70.0f, 70.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	m_pos = CScene2D::GetPosition();								//�ʒu���擾
	int nPatternAnim = CScene2D::GetPatternAnim();		//�A�j���[�V�����̎擾

	//�W���C�R���̐ݒ�
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	//�L�[�{�[�h�N���X�̌Ăяo��
	CInputKeyboard * pInputKeyboard = NULL;
	if (pInputKeyboard == NULL)
	{
		pInputKeyboard = CManager::GetInputKeyboard();
	}

	//�v���C���[�̈ړ�
	if (pInputKeyboard->GetPress(DIK_A) == true || (state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
	{	//�L�[�{�[�hA�L�[�A�W���C�R��9�X�e�B�b�N��������
		m_move.x += sinf(D3DX_PI * -0.5f) * PLAYER_SPEED;
		m_move.y += cosf(D3DX_PI * -0.5f) * PLAYER_SPEED;
	}
	if (pInputKeyboard->GetPress(DIK_D) == true || (state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
	{	//�L�[�{�[�hD�L�[�A�W���C�R��9�X�e�B�b�N��������
		m_move.x += sinf(D3DX_PI * 0.5f) * PLAYER_SPEED;
		m_move.y += cosf(D3DX_PI * 0.5f) * PLAYER_SPEED;
	}

	//�W�����v�̏���
	if (m_bJump == false)
	{	//�W�����v���Ă��Ȃ����
		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && CDirectXInput::GetConnectionJoypad() == true))
		{	//�X�y�[�X�L�[�A�W���C�R��A�{�^��������
			m_move.y = -PLAYER_JUMP;
			m_bJump = true;							//�W�����v���Ă�����
		}
	}

	m_move.y += GRAVITY;		//�d�͉��Z

	m_pos.x += m_move.x;			//���ړ�
	m_pos.y += m_move.y;			//����
	CSound::PlaySound(CSound::SOUND_LABEL_SE_JUMP);

	//����
	m_move.x += (0.0f - m_move.x) * PLAYER_INERTIA_SPEED;

	//�ړ��͈͂̏���
	if (m_pos.x >= 1000.0f)
	{	//�E�[�s����
		m_pos.x = 1000.0f;
	}
	if (m_pos.x <= 20)
	{	//���[�ɍs����
		m_pos.x = 20;
	}
	if (m_pos.y <= 20)
	{	//��s����
		m_pos.y = 20;
	}
	if (m_pos.y >= PLAYER_FIELD_RANGE)
	{	//���s����
		m_pos.y = PLAYER_FIELD_RANGE;
		m_bJump = false;									//�n�ʂɕt������W�����v���Ă��Ȃ���Ԃɖ߂�
	}

	//�ݒ肵���ʒu�𔽉f
	SetPosition(m_pos);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �e�N�X�`����ǂݍ���
//=============================================================================
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//�f�o�C�X�̎擾
	CRenderer * pRenderer = CManager::GetRenderer();						//�����_�����O�N���X�̌Ăяo��

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, PLAYER_NAME, &m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`����j��
//=============================================================================
void CPlayer::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}