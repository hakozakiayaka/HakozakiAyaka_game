//=============================================================================
//
// ­Ì [explosion.h]
// Author :  ú±ÊÔ
//
//=============================================================================
#ifndef _EXPLOSION_H_		//ñdCN[hh~
#define _EXPLOSION_H_

#include	"main.h"				//C

//*****************************************************************************
// }Nè`
//*****************************************************************************
#define SIZE								(80)			//|SÌS_©çÌTCY
#define EXPLOSION_SPEED		(10)			//­ÌXs[h
#define MAX_BULLET				(256)		//eÌÅå

//eNX`
#define EXPLOSION_NAME		"data/TEXTURE/explosion000.png"

//*****************************************************************************
// ­NX
//*****************************************************************************
class CExplosion : public CScene2D
{
public:
	CExplosion();																//RXgN^
	~CExplosion();															//fXgN^
	HRESULT Init(void);													//ú»
	void Uninit(void);															//I¹
	void Update(void);														//XV
	void Draw(void);															//`æ

	//ÃIoÖ
	static CExplosion * Create(D3DXVECTOR3 pos);		//IuWFNgÌ¶¬
	static HRESULT Load(void);										//eNX`ðÇÝÞ
	static void Unload(void);												//eNX`ðjü·é

private:
	int												m_nCntAnim;			//Aj[VÌJE^[
	int												m_nPatternAnim;		//Aj[VÌNo.

	//ÃIoÏ
	static LPDIRECT3DTEXTURE9	m_pTexture;				//¤LeNX`ÖÌ|C^
};
#endif