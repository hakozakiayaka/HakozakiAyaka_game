//=============================================================================
//
// eÌ [bullet.cpp]
// Author :  ú±ÊÔ
//
//=============================================================================
#include "main.h"				//C
#include "scene.h"				//V[
#include "renderer.h"			//_O
#include "scene2D.h"			//V[2D
#include "manager.h"			//}l[W[
#include "input.h"				//üÍ
#include "player.h"				//vC[
#include "animal.h"				//¨Æà
#include "bullet.h"				//e
#include "explosion.h"			//­
#include "enemy.h"				//G
#include "score.h"				//XRA
#include "effect.h"				//GtFNg
#include "life.h"					//Ct
#include "game.h"				//Q[
#include "sound.h"				//TEh

//*****************************************************************************
// ÃIoÏé¾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAX_BULLETTEX] = {};

//=============================================================================
// RXgN^
//=============================================================================
CBullet::CBullet(int nPriority) : CScene2D(nPriority)
{
	m_nLife = 0;						//Ct
	m_nCntAnim = 0;				//JE^[Aj[V
	m_nPatternAnim = 0;			//p^[
	//m_nCntMove = 0;
	//m_nChangeMove = 0;
	m_bUse = false;					//CkFeªgp³êÄ¢é©
}

//=============================================================================
// fXgN^
//=============================================================================
CBullet::~CBullet()
{	//½à©È¢
}

//=============================================================================
// eÌ¶¬
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, float moveDir, BULLETTYPE bulletType)
{
	CBullet *pBullet = NULL;

	//eNXÌ®ImÛ
	if (pBullet == NULL)
	{
		pBullet = new CBullet(BULLET_PRIORITY);
	}
	if (pBullet != NULL)
	{
		pBullet->Init();																		//ú»
		pBullet->SetPosition(pos);														//ÊuÌÝè
		pBullet->m_fKeepAnimal = pos.x;											//CkFe­ËÌÊuÅè
		pBullet->m_bulletType = bulletType;										//eÌíÞ
		pBullet->m_move = D3DXVECTOR3(moveDir, 0.0f, 0.0f);		//eÌòÔûü
		//pBullet->SetAnimation(0.2f, 0);												//Aj[VÌÝè

		if (pBullet->m_bulletType == BULLETTYPE_DOG)
		{	//Ck
			pBullet->BindTexture(m_pTexture[0]);
		}
		if (pBullet->m_bulletType == BULLETTYPE_MONKEY)
		{	//TFÎßÉòÔ
			pBullet->BindTexture(m_pTexture[1]);
			pBullet->m_move.x += sinf(D3DX_PI * 0.9f) * MONKEY_BULLET_SPEED;
			pBullet->m_move.y += cosf(D3DX_PI * 0.9f) * MONKEY_BULLET_SPEED;
		}
		if (pBullet->m_bulletType == BULLETTYPE_KIJI)
		{	//LWF^ºÉòÎ·
			pBullet->BindTexture(m_pTexture[2]);
			pBullet->m_move = D3DXVECTOR3(0.0f, moveDir, 0.0f);
		}
		if (pBullet->m_bulletType == BULLETTYPE_REDONI)
		{	// ©¨É
			pBullet->BindTexture(m_pTexture[3]);
			pBullet->m_move.x += sinf(D3DX_PI * 0.8f) * REDONI_BULLET_SPEED;
			pBullet->m_move.y += cosf(D3DX_PI * 0.8f) * REDONI_BULLET_SPEED;
		}
		if (pBullet->m_bulletType == BULLETTYPE_BULEONI)
		{	// ¨¨É
			pBullet->BindTexture(m_pTexture[3]);
			pBullet->m_move.x += sinf(D3DX_PI * -0.75f) * BULEONI_BULLET_SPEED;
			pBullet->m_move.y += cosf(D3DX_PI * -0.75f) * BULEONI_BULLET_SPEED;
		}
		if (pBullet->m_bulletType == BULLETTYPE_YELLOWONI)
		{	//«¢ë¨É
			pBullet->BindTexture(m_pTexture[3]);
		}
	}

	return pBullet;
}

//=============================================================================
// ú»
//=============================================================================
HRESULT CBullet::Init(void)
{
	CScene2D::Init();

	//eÌúÝè
	m_nLife = BULLET_LIFE;

	//IuWFNgÌÝè
	CScene2D::SetObjType(CScene::OBJTYPE_BULLET);

	//eÌTCYðÝè
	CScene2D::SetSize(30.0f, 30.0f);

	return S_OK;
}

//=============================================================================
// I¹
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// XV
//=============================================================================
void CBullet::Update(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPosition();							//ÊuÌæ¾
	int nAnimalType = CAnimal::GetAnimal();										//¨ÆàÌíÞðæ¾
	int nEnemyType = CEnemy::GetEnemyType();								//GÌíÞðæ¾
	CLife * pLife = NULL;

	//eªÚ®·é
	pos.x += m_move.x;
	pos.y += m_move.y;

	if (m_bulletType != CBullet::BULLETTYPE_DOG)
	{	//CkÈOÌeÉÍdÍðÂ¯é
		m_move.y += 0.15f;
	}

#if 0
	if (m_bulletType == BULLETTYPE_DOG || m_bulletType == BULLETTYPE_MONKEY || m_bulletType == BULLETTYPE_KIJI)
	{
		//JE^[ðÁZ
		m_nCntAnim++;

		//Aj[V
		if ((m_nCntAnim % BULLET_ANIMAPEED) == 0)
		{
			m_nPatternAnim++;		//p^[NoðXV
			CScene2D::SetAnimation(0.2f, m_nPatternAnim);
		}
		CScene2D::SetPosition(pos);																		//ÊuÌÝè
	}

	if (m_bulletType == BULLETTYPE_REDONI || m_bulletType == BULLETTYPE_BULEONI || m_bulletType == BULLETTYPE_YELLOWONI)
	{
		CScene2D::SetPosition(pos);																		//ÊuÌÝè
	}
#endif

	CScene2D::SetPosition(pos);
	CEffect::Create(pos, D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f));								//GtFNg

	//eÌò£ÌÝè
	m_nLife--;

	if (m_nLife <= 0 || pos.x >= SCREEN_WIDTH - 20)
	{	//eÌ·³ª0ÉÈÁ½AæÊE¤ÜÅ«½AnÊ
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
				{	//¨ÆàÌe
					if (m_bulletType == BULLETTYPE_DOG)
					{	//CkÌeÌÝ
						SetBullet(CBullet::BULLETTYPE_DOG, pos);
					}
					if (objType == OBJTYPE_ENEMY)
					{	//CkÌeªAGÉ½Á½
						CEnemy * pEnemy = ((CEnemy*)pScene);								//Gl~[ðÄÑoµÄApSceneÌÉ­§cast·é
						D3DXVECTOR3 enemyPos = pEnemy->GetPosition();			//enemyPosðìÁÄAeNXÌposÌîñðÁÄ­é

						//½è»è
						if (pos.x > enemyPos.x - RANGE
							&& pos.x < enemyPos.x + RANGE
							&& pos.y > enemyPos.y - RANGE
							&& pos.y < enemyPos.y + RANGE)
						{
							CSound::PlaySound(CSound::SOUND_LABEL_SE_HIT000);
							pEnemy->HitEnemy(1);													//Ctð1¸ç·
							CExplosion::Create(pos);												//­Ì¶¬
							Uninit();																			//eÌjü
							break;
						}
					}
				}

#if 1
				if (this->m_bulletType == BULLETTYPE_REDONI || this->m_bulletType == BULLETTYPE_BULEONI || this->m_bulletType == BULLETTYPE_YELLOWONI)
				{	//Gl~[Ìe
					if (objType == OBJTYPE_ANIMAL)
					{	//GÌeªA¨ÆàÉ½Á½
						CAnimal * pAnimal = ((CAnimal*)pScene);								//vC[ðÄÑoµÄApSceneÌÉ­§cast·é
						D3DXVECTOR3 animalPos = pAnimal->GetPosition();				//animalPosðìÁÄAeNXÌposÌîñðÁÄ­é

						//½è»è
						if (pos.x > animalPos.x - RANGE
							&& pos.x < animalPos.x + RANGE
							&& pos.y > animalPos.y - RANGE
							&& pos.y < animalPos.y + RANGE)
						{
							CSound::PlaySound(CSound::SOUND_LABEL_SE_HIT000);
							pLife->SetLife(1);						//Ct¸é
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
// `æ
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ¨ÆàÌeÌÝè
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
// eNX`ðÇÝÞ
//=============================================================================
HRESULT CBullet::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//foCXÌæ¾
	CRenderer * pRenderer = CManager::GetRenderer();						//_ONXÌÄÑoµ

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// eNX`Ì¶¬
	D3DXCreateTextureFromFile(pDevice, BULLET_DOG, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, BULLET_MONKEY, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, BULLET_KIJI, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, BULLET_ONI, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, BULLET_BOSS, &m_pTexture[4]);

	return S_OK;
}

//=============================================================================
// eNX`ðjü
//=============================================================================
void CBullet::Unload(void)
{
	// eNX`Ìjü
	for (int nCntBullet = 0; nCntBullet < MAX_BULLETTEX; nCntBullet++)
	{
		if (m_pTexture[nCntBullet] != NULL)
		{
			m_pTexture[nCntBullet]->Release();
			m_pTexture[nCntBullet] = NULL;
		}
	}
}