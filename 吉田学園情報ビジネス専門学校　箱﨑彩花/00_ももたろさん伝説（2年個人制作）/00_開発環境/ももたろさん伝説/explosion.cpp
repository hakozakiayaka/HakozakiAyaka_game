//=============================================================================
//
// ­Ì [explosion.cpp]
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
#include "bullet.h"				//e
#include "explosion.h"			//­

//*****************************************************************************
// ÃIoÏé¾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//=============================================================================
// RXgN^
//=============================================================================
CExplosion::CExplosion()
{
	m_nCntAnim = 0;
	m_nPatternAnim = 0;
}

//=============================================================================
// fXgN^
//=============================================================================
CExplosion::~CExplosion()
{	//½à©È¢
}

//=============================================================================
// |SÌ¶¬
//=============================================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion *pExplosion = NULL;

	//vC[NXÌ®ImÛ
	if (pExplosion == NULL)
	{
		pExplosion = new CExplosion;
	}
	if(pExplosion != NULL)
	{
		pExplosion->Init();													//ú»
		pExplosion->SetPosition(pos);								//ÊuÌÝè
		pExplosion->SetAnimation(0.125f, 0);
		pExplosion->BindTexture(m_pTexture);					//eNX`ÌèÄ
	}

	return pExplosion;
}

//=============================================================================
// ú»
//=============================================================================
HRESULT CExplosion::Init(void)
{
	CScene2D::Init();

	//­ÌTCYðÝè
	SetSize(30.0f, 30.0f);

	return S_OK;
}

//=============================================================================
// I¹
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// XV
//=============================================================================
void CExplosion::Update(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPosition();		//CScene2D©çÊuðæ¾
	SetPosition(pos);															//æ¾µ½ÊuðACScene2DÉÔ·

	m_nCntAnim++;					//JE^[ðÁZ

	if ((m_nCntAnim % EXPLOSION_SPEED) == 0)
	{
		m_nPatternAnim++;		//p^[NoðXV

		//Aj[VÌÝè
		SetAnimation(0.125f, m_nPatternAnim);							//t[Ap^[No
	}

	//Aj[VÌI¹
	if (m_nPatternAnim >= 7)
	{	//p^[ª·¬½ç
		Uninit();
	}
}

//=============================================================================
// `æ
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// eNX`ðÇÝÞ
//=============================================================================
HRESULT CExplosion::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//foCXÌæ¾
	CRenderer * pRenderer = CManager::GetRenderer();						//_ONXÌÄÑoµ

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// eNX`Ì¶¬
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_NAME, &m_pTexture);

	return S_OK;
}

//=============================================================================
// eNX`ðjü
//=============================================================================
void CExplosion::Unload(void)
{
	// eNX`Ìjü
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}