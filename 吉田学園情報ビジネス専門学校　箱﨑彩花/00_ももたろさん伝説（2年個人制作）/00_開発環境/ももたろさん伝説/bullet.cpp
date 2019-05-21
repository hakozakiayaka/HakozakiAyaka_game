//=============================================================================
//
// �e�̏��� [bullet.cpp]
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
#include "animal.h"				//���Ƃ�
#include "bullet.h"				//�e
#include "explosion.h"			//����
#include "enemy.h"				//�G
#include "score.h"				//�X�R�A
#include "effect.h"				//�G�t�F�N�g
#include "life.h"					//���C�t
#include "game.h"				//�Q�[��
#include "sound.h"				//�T�E���h

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAX_BULLETTEX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBullet::CBullet(int nPriority) : CScene2D(nPriority)
{
	m_nLife = 0;						//���C�t
	m_nCntAnim = 0;				//�J�E���^�[�A�j���[�V����
	m_nPatternAnim = 0;			//�p�^�[����
	//m_nCntMove = 0;
	//m_nChangeMove = 0;
	m_bUse = false;					//�C�k�F�e���g�p����Ă��邩
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{	//���������Ȃ�
}

//=============================================================================
// �e�̐���
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, float moveDir, BULLETTYPE bulletType)
{
	CBullet *pBullet = NULL;

	//�e�N���X�̓��I�m��
	if (pBullet == NULL)
	{
		pBullet = new CBullet(BULLET_PRIORITY);
	}
	if (pBullet != NULL)
	{
		pBullet->Init();																		//����������
		pBullet->SetPosition(pos);														//�ʒu�̐ݒ�
		pBullet->m_fKeepAnimal = pos.x;											//�C�k�F�e���˂̈ʒu�Œ�
		pBullet->m_bulletType = bulletType;										//�e�̎��
		pBullet->m_move = D3DXVECTOR3(moveDir, 0.0f, 0.0f);		//�e�̔�ԕ���
		//pBullet->SetAnimation(0.2f, 0);												//�A�j���[�V�����̐ݒ�

		if (pBullet->m_bulletType == BULLETTYPE_DOG)
		{	//�C�k
			pBullet->BindTexture(m_pTexture[0]);
		}
		if (pBullet->m_bulletType == BULLETTYPE_MONKEY)
		{	//�T���F�΂߂ɔ��
			pBullet->BindTexture(m_pTexture[1]);
			pBullet->m_move.x += sinf(D3DX_PI * 0.9f) * MONKEY_BULLET_SPEED;
			pBullet->m_move.y += cosf(D3DX_PI * 0.9f) * MONKEY_BULLET_SPEED;
		}
		if (pBullet->m_bulletType == BULLETTYPE_KIJI)
		{	//�L�W�F�^���ɔ�΂�
			pBullet->BindTexture(m_pTexture[2]);
			pBullet->m_move = D3DXVECTOR3(0.0f, moveDir, 0.0f);
		}
		if (pBullet->m_bulletType == BULLETTYPE_REDONI)
		{	//��������
			pBullet->BindTexture(m_pTexture[3]);
			pBullet->m_move.x += sinf(D3DX_PI * 0.8f) * REDONI_BULLET_SPEED;
			pBullet->m_move.y += cosf(D3DX_PI * 0.8f) * REDONI_BULLET_SPEED;
		}
		if (pBullet->m_bulletType == BULLETTYPE_BULEONI)
		{	//��������
			pBullet->BindTexture(m_pTexture[3]);
			pBullet->m_move.x += sinf(D3DX_PI * -0.75f) * BULEONI_BULLET_SPEED;
			pBullet->m_move.y += cosf(D3DX_PI * -0.75f) * BULEONI_BULLET_SPEED;
		}
		if (pBullet->m_bulletType == BULLETTYPE_YELLOWONI)
		{	//�����남��
			pBullet->BindTexture(m_pTexture[3]);
		}
	}

	return pBullet;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBullet::Init(void)
{
	CScene2D::Init();

	//�e�̏����ݒ�
	m_nLife = BULLET_LIFE;

	//�I�u�W�F�N�g�̐ݒ�
	CScene2D::SetObjType(CScene::OBJTYPE_BULLET);

	//�e�̃T�C�Y��ݒ�
	CScene2D::SetSize(30.0f, 30.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBullet::Update(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPosition();							//�ʒu�̎擾
	int nAnimalType = CAnimal::GetAnimal();										//���Ƃ��̎�ނ��擾
	int nEnemyType = CEnemy::GetEnemyType();								//�G�̎�ނ��擾
	CLife * pLife = NULL;

	//�e���ړ�����
	pos.x += m_move.x;
	pos.y += m_move.y;

	if (m_bulletType != CBullet::BULLETTYPE_DOG)
	{	//�C�k�ȊO�̒e�ɂ͏d�͂�����
		m_move.y += 0.15f;
	}

#if 0
	if (m_bulletType == BULLETTYPE_DOG || m_bulletType == BULLETTYPE_MONKEY || m_bulletType == BULLETTYPE_KIJI)
	{
		//�J�E���^�[�����Z
		m_nCntAnim++;

		//�A�j���[�V����
		if ((m_nCntAnim % BULLET_ANIMAPEED) == 0)
		{
			m_nPatternAnim++;		//�p�^�[��No���X�V
			CScene2D::SetAnimation(0.2f, m_nPatternAnim);
		}
		CScene2D::SetPosition(pos);																		//�ʒu�̐ݒ�
	}

	if (m_bulletType == BULLETTYPE_REDONI || m_bulletType == BULLETTYPE_BULEONI || m_bulletType == BULLETTYPE_YELLOWONI)
	{
		CScene2D::SetPosition(pos);																		//�ʒu�̐ݒ�
	}
#endif

	CScene2D::SetPosition(pos);
	CEffect::Create(pos, D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f));								//�G�t�F�N�g

	//�e�̔򋗗��̐ݒ�
	m_nLife--;

	if (m_nLife <= 0 || pos.x >= SCREEN_WIDTH - 20)
	{	//�e�̒�����0�ɂȂ����A��ʉE���܂ł����A�n��
		CExplosion::Create(pos);
		Uninit();
	}

	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		for (int nCntBullet = 0; nCntBullet < MAX_DATA; nCntBullet++)
		{
			CScene * pScene = NULL;
			if (pScene == NULL)
			{
				pScene = CScene::GetScene(nCntPriority, nCntBullet);
			}
			if (pScene != NULL)
			{
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				if (this->m_bulletType == BULLETTYPE_DOG || this->m_bulletType == BULLETTYPE_MONKEY || this->m_bulletType == BULLETTYPE_KIJI)
				{	//���Ƃ��̒e
					if (m_bulletType == BULLETTYPE_DOG)
					{	//�C�k�̒e�̂�
						SetBullet(CBullet::BULLETTYPE_DOG, pos);
					}
					if (objType == OBJTYPE_ENEMY)
					{	//�C�k�̒e���A�G�ɓ�������
						CEnemy * pEnemy = ((CEnemy*)pScene);								//�G�l�~�[���Ăяo���āApScene�̒��ɋ���cast����
						D3DXVECTOR3 enemyPos = pEnemy->GetPosition();			//enemyPos������āA�e�N���X��pos�̏��������Ă���

						//�����蔻��
						if (pos.x > enemyPos.x - RANGE
							&& pos.x < enemyPos.x + RANGE
							&& pos.y > enemyPos.y - RANGE
							&& pos.y < enemyPos.y + RANGE)
						{
							CSound::PlaySound(CSound::SOUND_LABEL_SE_HIT000);
							pEnemy->HitEnemy(1);													//���C�t��1���炷
							CExplosion::Create(pos);												//�����̐���
							Uninit();																			//�e�̔j��
							break;
						}
					}
				}

#if 1
				if (this->m_bulletType == BULLETTYPE_REDONI || this->m_bulletType == BULLETTYPE_BULEONI || this->m_bulletType == BULLETTYPE_YELLOWONI)
				{	//�G�l�~�[�̒e
					if (objType == OBJTYPE_ANIMAL)
					{	//�G�̒e���A���Ƃ��ɓ�������
						CAnimal * pAnimal = ((CAnimal*)pScene);								//�v���C���[���Ăяo���āApScene�̒��ɋ���cast����
						D3DXVECTOR3 animalPos = pAnimal->GetPosition();				//animalPos������āA�e�N���X��pos�̏��������Ă���

						//�����蔻��
						if (pos.x > animalPos.x - RANGE
							&& pos.x < animalPos.x + RANGE
							&& pos.y > animalPos.y - RANGE
							&& pos.y < animalPos.y + RANGE)
						{
							CSound::PlaySound(CSound::SOUND_LABEL_SE_HIT000);
							pLife->SetLife(1);						//���C�t����
							pAnimal->HitAnimal(1);
							CExplosion::Create(pos);
							Uninit();
							break;
						}
					}
				}
#endif
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ���Ƃ��̒e�̐ݒ�
//=============================================================================
void CBullet::SetBullet(BULLETTYPE bulletType, D3DXVECTOR3 pos)
{
	m_bulletType = bulletType;

	if (m_bulletType == BULLETTYPE_DOG)
	{
		if (m_bUse == false)
		{
			if (pos.x > m_fKeepAnimal + 400)
			{
				m_bUse = true;
				m_move.x *= -1;
			}
		}
	}
}

//=============================================================================
// �e�N�X�`����ǂݍ���
//=============================================================================
HRESULT CBullet::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//�f�o�C�X�̎擾
	CRenderer * pRenderer = CManager::GetRenderer();						//�����_�����O�N���X�̌Ăяo��

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, BULLET_DOG, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, BULLET_MONKEY, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, BULLET_KIJI, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, BULLET_ONI, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, BULLET_BOSS, &m_pTexture[4]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`����j��
//=============================================================================
void CBullet::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntBullet = 0; nCntBullet < MAX_BULLETTEX; nCntBullet++)
	{
		if (m_pTexture[nCntBullet] != NULL)
		{
			m_pTexture[nCntBullet]->Release();
			m_pTexture[nCntBullet] = NULL;
		}
	}
}