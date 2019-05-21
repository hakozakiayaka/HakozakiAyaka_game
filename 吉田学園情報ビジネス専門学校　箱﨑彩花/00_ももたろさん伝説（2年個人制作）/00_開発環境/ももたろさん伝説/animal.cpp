//=============================================================================
//
// ���Ƃ����� [animal.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "main.h"				//���C��
#include "scene.h"				//�V�[��
#include "renderer.h"			//�����_�����O
#include "scene2D.h"			//�V�[��2D
#include "manager.h"			//�}�l�[�W���[
#include "input.h"				//����
#include "animal.h"				//���Ƃ�
#include "bullet.h"				//�e
#include "player.h"				//�v���C���[
#include "bg.h"					//�w�i
#include "fade.h"					//�t�F�[�h
#include "score.h"				//�X�R�A
#include "sound.h"				//�T�E���h

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CAnimal::m_pTexture[MAX_ANIMALTEX] = {};
CAnimal::ANIMALTYPE CAnimal::m_animalType = CAnimal::ANIMALTYPE_DOG;			//�ŏ��̂��Ƃ�
CLife * CAnimal::m_pLife[ANIMAL_LIFE] = {};																	//���C�t

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CAnimal::CAnimal(int nPriority) : CScene2D(4)
{
	m_animalState = ANIMALSTATE_NONE;					//�ʏ���
	m_BulletType = CBullet::BULLETTYPE_NONE;			//�e�̎��
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ړ���
	m_nCntState = 0;														//��ԃJ�E���^�[
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CAnimal::~CAnimal()
{	//���������Ȃ�
}

//=============================================================================
// ���Ƃ��̐���
//=============================================================================
CAnimal *CAnimal::Create(D3DXVECTOR3 pos, ANIMALTYPE animalType)
{
	CAnimal * pAnimal = NULL;

	//���Ƃ��N���X�̓��I�m��
	if (pAnimal == NULL)
	{
		pAnimal = new CAnimal;
	}
	if(pAnimal != NULL)
	{
		pAnimal->Init();
		pAnimal->SetPosition(pos);												//�ʒu�̐ݒ�
		pAnimal->m_bJump = true;												//�W�����v���Ă�����
		pAnimal->SetAnimation(PATTERN_ANIM, 0);					//�A�j���[�V�����̐ݒ�
		pAnimal->m_nLife = ANIMAL_LIFE;									//���C�t�̐ݒ�
		pAnimal->m_animalType = animalType;							//���Ƃ��̎��

		if (pAnimal->m_animalType == ANIMALTYPE_DOG)
		{	//�C�k�A�e�N�X�`���̊��蓖��
			pAnimal->BindTexture(m_pTexture[0]);
		}
		if (pAnimal->m_animalType == ANIMALTYPE_MONKEY)
		{	//�T���A�e�N�X�`���̊��蓖��
			pAnimal->BindTexture(m_pTexture[1]);
		}
		if (pAnimal->m_animalType == ANIMALTYPE_KIJI)
		{	//�L�W�A�e�N�X�`���̊��蓖��
			pAnimal->BindTexture(m_pTexture[2]);
		}
	}

	return pAnimal;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CAnimal::Init()
{
	CManager::MODE mode = CManager::GetMode();			//���[�h�̎擾

	//������
	CScene2D::Init();

	//�e�N�X�`���̊��蓖��
	CLife::Load();

	//�I�u�W�F�N�g�̐ݒ�
	CScene2D::SetObjType(CScene::OBJTYPE_ANIMAL);

	//���Ƃ��̃T�C�Y��ݒ�
	SetSize(70.0f, 70.0f);

	if (mode == CManager::MODE_GAME)
	{	//�Q�[���̎��������C�t����
		for (int nCntLife = 0; nCntLife < ANIMAL_LIFE; nCntLife++)
		{	//���C�t�̐���
			m_pLife[nCntLife] = CLife::Create(D3DXVECTOR3(100.0f + (100.0f * nCntLife), 50.0f, 0.0f), nCntLife);
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CAnimal::Uninit(void)
{
	CLife::Unload();						//���C�t�̃e�N�X�`���̔j��

	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CAnimal::Update(void)
{
	m_pos = CScene2D::GetPosition();										//�ʒu
	int nPatternAnim = CScene2D::GetPatternAnim();				//�A�j���[�V����
	CFade::FADE fade = CFade::GetFade();									//�t�F�[�h
	CManager::MODE mode = CManager::GetMode();				//���[�h�̎擾

	float nSpeed = 1.0f;																//�^�C�g����ʂŎg�p�i�X�s�[�h�j

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

	switch (m_animalState)
	{	//���Ƃ��̃X�e�[�g
	case ANIMALSTATE_NONE:
		break;

	case ANIMALSTATE_DAMAGE:
		m_nCntState--;
		if (m_nCntState <= 0)
		{
			m_pLife[m_nLife]->Uninit();
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));			//�����Ă��Ԃ��瓧���ɖ߂�
			m_animalState = ANIMALSTATE_NONE;				//�ʏ��Ԃɖ߂�
		}
		break;

	case ANIMALSTATE_DEATH:
		m_pLife[m_nLife]->Uninit();
		if (fade != CFade::FADE_OUT)
		{
			CFade::SetFade(CManager::MODE_GAMEOVER);
		}
		break;
	}

	//*****************************************************************************
	// �A�j���[�V��������
	//*****************************************************************************
	m_nCntAnim++;			//�J�E���^�[�����Z

	if ((m_nCntAnim % ANIMAL_ANIMSPEED) == 0)
	{
		m_nPatternAnim++;		//�p�^�[��No���X�V
		CScene2D::SetAnimation(PATTERN_ANIM, m_nPatternAnim);
	}

	//*****************************************************************************
	// �^�C�g���ŃL�W��΂�
	//*****************************************************************************
	if (mode == CManager::MODE_TITLE)
	{
		//�ړ��ʂɃX�s�[�h�����Z
		m_move.x += nSpeed;

		if (m_pos.x >= SCREEN_WIDTH)
		{	//�E�[�܂ł�����
			m_pos.x = -30.0f;
		}

		if (m_animalType != ANIMALTYPE_KIJI)
		{
			m_move.y += ANIMAL_GRAVITY;		//�d�͉��Z
			m_pos.y += m_move.y;						//����
			CSound::PlaySound(CSound::SOUND_LABEL_SE_SHOT);
		}
		m_pos.x += m_move.x;			//���ړ�

		//����
		m_move.x += (0.0f - m_move.x) * ANIMAL_INERTIA_SPEED;
	}

	//*****************************************************************************
	// ���Ƃ��̐؂�ւ�����
	//*****************************************************************************
	if (mode == CManager::MODE_GAME || mode == CManager::MODE_TUTORIAL)
	{
		//���Ƃ��؂�ւ������i�W���C�R���j
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && CDirectXInput::GetConnectionJoypad() == true)
		{	//�W���C�R��RB/5������
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				m_nSelect = (m_nSelect + 1) % 3;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && CDirectXInput::GetConnectionJoypad() == true)
		{	//�W���C�R��LB/5������
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				m_nSelect = (m_nSelect + 2) % 3;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}

		//���Ƃ��؂�ւ������i�L�[�{�[�h�j
		if (pInputKeyboard->GetTrigger(DIK_F1) == true)
		{	//�C�k
			m_nSelect = 0;
		}
		if (pInputKeyboard->GetTrigger(DIK_F2) == true)
		{	//�T��
			m_nSelect = 1;
		}
		if (pInputKeyboard->GetTrigger(DIK_F3) == true)
		{	//�L�W
			m_nSelect = 2;
		}

		if (m_nSelect == 0)
		{
			m_animalType = ANIMALTYPE_DOG;
			m_BulletType = CBullet::BULLETTYPE_DOG;
			BindTexture(m_pTexture[0]);
		}
		if (m_nSelect == 1)
		{
			m_animalType = ANIMALTYPE_MONKEY;
			m_BulletType = CBullet::BULLETTYPE_MONKEY;
			BindTexture(m_pTexture[1]);
		}
		if (m_nSelect == 2)
		{
			if (mode == CManager::MODE_TUTORIAL)
			{	//�`���[�g���A��
				m_pos.y = 320.0f;
			}
			if (mode == CManager::MODE_GAME)
			{	//�Q�[��
				m_pos.y = 150.0f;
			}
			m_animalType = ANIMALTYPE_KIJI;
			m_BulletType = CBullet::BULLETTYPE_KIJI;
			BindTexture(m_pTexture[2]);
		}

		//�e���˂̏���
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_X && CDirectXInput::GetConnectionJoypad() == true))
		{	//�G���^�[�L�[�A�W���C�R��X�{�^��������
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_SHOT);
				CBullet::Create(m_pos, BULLET_SPEED, m_BulletType);
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}

		//���Ƃ��̈ړ�
		if (pInputKeyboard->GetPress(DIK_A) == true || (state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
		{	//�L�[�{�[�hA�L�[�A�W���C�R��9�X�e�B�b�N��������
			m_move.x += sinf(D3DX_PI * -0.5f) * ANIMAL_SPEED;
			m_move.y += cosf(D3DX_PI * -0.5f) * ANIMAL_SPEED;
		}
		if (pInputKeyboard->GetPress(DIK_D) == true || (state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
		{	//�L�[�{�[�hD�L�[�A�W���C�R��9�X�e�B�b�N��������
			m_move.x += sinf(D3DX_PI * 0.5f) * ANIMAL_SPEED;
			m_move.y += cosf(D3DX_PI * 0.5f) * ANIMAL_SPEED;
		}

		if (m_animalType != ANIMALTYPE_KIJI)
		{
			m_move.y += ANIMAL_GRAVITY;		//�d�͉��Z
			m_pos.y += m_move.y;		//����
		}
		m_pos.x += m_move.x;			//���ړ�

		//����
		m_move.x += (0.0f - m_move.x) * ANIMAL_INERTIA_SPEED;

		//�W�����v�̏���
		if (m_animalType == ANIMALTYPE_DOG || m_animalType == ANIMALTYPE_MONKEY)
		{	//�C�k�ƃT���̎������W�����v
			if (m_bJump == false)
			{	//�W�����v���Ă��Ȃ����
				if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && CDirectXInput::GetConnectionJoypad() == true))
				{	//�X�y�[�X�L�[�A�W���C�R��A�{�^��������
					m_move.y = -ANIMAL_JUMP;
					m_bJump = true;							//�W�����v���Ă�����
				}
				CSound::PlaySound(CSound::SOUND_LABEL_SE_JUMP);
			}
		}

		//�ړ��͈͂̏���
		if (m_pos.x >= 1000.0f)
		{	//�E�[�s����
			m_pos.x = 1000.0f;
		}
		if (m_pos.x <= LEFT_WIDTH)
		{	//���[�ɍs����
			m_pos.x = LEFT_WIDTH;
		}
		if (m_pos.y <= 20)
		{	//��s����
			m_pos.y = 20;
		}
		if (m_pos.y >= ANIMAL_FIELD_RANGE)
		{	//���s����
			m_pos.y = ANIMAL_FIELD_RANGE;
			m_bJump = false;									//�n�ʂɕt������W�����v���Ă��Ȃ���Ԃɖ߂�
		}
	}

	//�ݒ肵���ʒu�𔽉f
	SetPosition(m_pos);

	if (m_animalState == ANIMALSTATE_DEATH)
	{
		Uninit();		//���Ƃ��̔j��
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CAnimal::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �_���[�W����
//=============================================================================
void CAnimal::HitAnimal(int nDamage)
{
	CFade::FADE fade = CFade::GetFade();

	m_nLife -= nDamage;

	if (m_nLife <= 0)
	{	//���C�t��0�ɂȂ����炨�Ƃ��̔j��
		m_animalState = ANIMALSTATE_DEATH;
	}
	else
	{	//���C�t���c���Ă�
		m_animalState = ANIMALSTATE_DAMAGE;
		m_nCntState = 5;
		SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));			//�ԐF�ɂȂ�
	}
}

//=============================================================================
// �e�N�X�`����ǂݍ���
//=============================================================================
HRESULT CAnimal::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//�f�o�C�X�̎擾
	CRenderer * pRenderer = CManager::GetRenderer();						//�����_�����O�N���X�̌Ăяo��

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, ANIMAL_DOG, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, ANIMAL_MONKEY, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, ANIMAL_KIJI, &m_pTexture[2]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`����j��
//=============================================================================
void CAnimal::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntAnimal = 0; nCntAnimal < MAX_ANIMALTEX; nCntAnimal++)
	{
		if (m_pTexture[nCntAnimal] != NULL)
		{
			m_pTexture[nCntAnimal]->Release();
			m_pTexture[nCntAnimal] = NULL;
		}
	}
}