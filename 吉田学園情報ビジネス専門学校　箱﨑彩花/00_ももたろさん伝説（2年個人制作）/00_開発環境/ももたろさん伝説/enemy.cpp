//=============================================================================
//
// �G�̏��� [enemy.cpp]
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
#include "enemy.h"				//�G
#include "fade.h"					//�t�F�[�h
#include "score.h"				//�X�R�A
#include "animal.h"				//���Ƃ�
#include "sound.h"				//�T�E���h

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[ENEMY_TEXTURE] = {};
int CEnemy::m_nNumEnemy = 0;
CEnemy::ENEMYTYPE CEnemy::m_enemyType = CEnemy::ENEMYTYPE_RED;		//�ŏ��̋S

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy() : CScene2D(2)
{
	m_enemyState = ENEMYSTATE_NONE;						//�ʏ���
	m_BulletType = CBullet::BULLETTYPE_NONE;				//�e�̎��
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�ړ���
	m_fSpeed = 0.0f;
	m_nNumEnemy++;											//�G�̑������J�E���g
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{	//���������Ȃ�
}

//=============================================================================
// �G�̐���
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, ENEMYTYPE enemyType)
{
	CEnemy * pEnemy = NULL;

	//�G�N���X�̓��I�m��
	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy;
	}
	if(pEnemy != NULL)
	{
		pEnemy->Init();
		pEnemy->m_enemyState = ENEMYSTATE_NONE;			//�G�̏��
		pEnemy->m_nCntState = 0;												//��ԊǗ��̃J�E���^�[
		pEnemy->SetPosition(pos);												//�ʒu�̐ݒ�
		pEnemy->m_pos = pos;														//�擾�����ʒu�ɑ��
		pEnemy->m_nLife = ENEMY_LIFE;									//���C�t�̐ݒ�
		pEnemy->m_enemyType = enemyType;								//�擾�����^�C�v����
		pEnemy->m_bJump = true;

		if (m_enemyType == ENEMYTYPE_RED)
		{	//�Ԃ���
			pEnemy->BindTexture(m_pTexture[0]);
			pEnemy->m_BulletType = CBullet::BULLETTYPE_REDONI;
		}
		if (m_enemyType == ENEMYTYPE_BLUE)
		{	//����
			pEnemy->BindTexture(m_pTexture[1]);
			pEnemy->m_BulletType = CBullet::BULLETTYPE_BULEONI;
		}
		if (m_enemyType == ENEMYTYPE_YELLOW)
		{	//������
			pEnemy->BindTexture(m_pTexture[2]);
			pEnemy->m_BulletType = CBullet::BULLETTYPE_YELLOWONI;
		}
	}

	return pEnemy;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemy::Init()
{
	CScene2D::Init();

	//�I�u�W�F�N�g�̐ݒ�
	CScene2D::SetObjType(CScene::OBJTYPE_ENEMY);

	//�G�l�~�[�̃T�C�Y��ݒ�
	SetSize(40.0f, 40.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemy::Update(void)
{
	m_pos = CScene2D::GetPosition();
	int nPatternAnim = CScene2D::GetPatternAnim();
	CFade::FADE fade = CFade::GetFade();

	switch (m_enemyState)
	{
	case ENEMYSTATE_NONE:		//�ʏ���
		break;

	case ENEMYSTATE_DAMAGE:	//�_���[�W���
		m_nCntState--;
		if (m_nCntState <= 0)
		{	//���C�t���c���Ă�
			m_enemyState = ENEMYSTATE_NONE;				//�ʏ��Ԃɖ߂�
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));			//�����Ă��Ԃ��瓧���ɖ߂�
		}
		break;

	case ENEMYSTATE_DEATH:
		m_nNumEnemy--;													//�G�̑��������炷

		//�G���S�ł�������
		if (m_nNumEnemy == 0)
		{
			if (fade != CFade::FADE_OUT)
			{
				CFade::SetFade(CManager::MODE_GAMECLEAR);
			}
		}
		break;
	}

	//float nSpeed = 10.0f;
	//m_pos.x -= nSpeed;

	////�e����
	//if ((rand() % 180) == 0)
	//{
	//	CSound::PlaySound(CSound::SOUND_LABEL_SE_SHOT);
	//	CBullet::Create(m_pos, -BULLET_SPEED, m_BulletType);		//�e����
	//}

	//m_move.y += ENEMY_GRAVITY;			//�d�͉��Z
	//m_pos.y += m_move.y;							//����

	//if ((rand() % 180) == 0)
	//{
	//	if (m_bJump == false)
	//	{
	//		m_move.y = -ANIMAL_JUMP;
	//		m_bJump = true;								//�W�����v���Ă�����
	//	}
	//}

	//m_pos.x += m_move.x;

	//�ړ��͈͂̏���
	if (m_pos.x >= SCREEN_WIDTH)
	{	//�E�[�s����
		m_pos.x = SCREEN_WIDTH;
	}
	if (m_pos.x <= LEFT_WIDTH)
	{	//���[�ɍs����
		m_pos.x = LEFT_WIDTH;
	}
	if (m_pos.y <= 20)
	{	//��s����
		m_pos.y = 20;
	}
	if (m_pos.y >= ENEMY_FIELD_RANGE)
	{	//���s����
		m_pos.y = ENEMY_FIELD_RANGE;
	}

	//�ݒ肵���ʒu�𔽉f
	SetPosition(m_pos);

	if (m_enemyState == ENEMYSTATE_DEATH)
	{	//���񂾏��
		Uninit();		//�G�̔j��
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �_���[�W����
//=============================================================================
void CEnemy::HitEnemy(int nDamage)
{
	m_nLife -= nDamage;													//���C�t����

	if (m_nLife <= 0)
	{	//���C�t��0�ɂȂ�����G�̔j��
		m_enemyState = ENEMYSTATE_DEATH;
		CScore::AddScore(23000);										//�X�R�A�̉��Z
	}
	else
	{	//���C�t���c���Ă�
		m_enemyState = ENEMYSTATE_DAMAGE;			//�_���[�W���
		m_nCntState = 5;													//��ԊǗ��̃J�E���^�[�̐ݒ�
		SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));			//�ԐF�ɂȂ�
	}
}

//=============================================================================
// �e�N�X�`����ǂݍ���
//=============================================================================
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//�f�o�C�X�̎擾
	CRenderer * pRenderer = CManager::GetRenderer();						//�����_�����O�N���X�̌Ăяo��

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, ENEMY_NAME, &m_pTexture[0]);		//��������
	D3DXCreateTextureFromFile(pDevice, ENEMY_NAME1, &m_pTexture[1]);		//��������
	D3DXCreateTextureFromFile(pDevice, ENEMY_NAME2, &m_pTexture[2]);		//�����남��

	return S_OK;
}

//=============================================================================
// �e�N�X�`����j��
//=============================================================================
void CEnemy::Unload(void)
{
	if (m_pTexture[0] != NULL)
	{
		m_pTexture[0]->Release();
		m_pTexture[0] = NULL;
	}

	if (m_pTexture[1] != NULL)
	{
		m_pTexture[1]->Release();
		m_pTexture[1] = NULL;
	}

	if (m_pTexture[2] != NULL)
	{
		m_pTexture[2]->Release();
		m_pTexture[2] = NULL;
	}
}