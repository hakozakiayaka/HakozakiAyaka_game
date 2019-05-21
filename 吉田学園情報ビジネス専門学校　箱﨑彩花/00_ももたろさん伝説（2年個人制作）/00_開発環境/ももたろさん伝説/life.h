//=============================================================================
//
// ���C�t���� [life.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _LIFE_H_			//��d�C���N���[�h�h�~
#define _LIFE_H_

#include	"main.h"		//���C��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LIFE_TEX		"data/TEXTURE/momo.png"

//*****************************************************************************
// ���C�t�N���X
//*****************************************************************************
class CLife : CScene2D
{
public:
	CLife();																							//�R���X�g���N�^
	~CLife();																							//�f�X�g���N�^
	HRESULT Init(void);																		//����������
	void Uninit(void);																				//�I������
	void Update(void);																			//�X�V����
	void Draw(void);																				//�`�揈��
	void SetLife(int nLifeDown);															//�X�R�A�̐ݒ�
	static int GetLife(void) { return m_nLife; }										//���C�t�N���X�̎擾

	//�ÓI�����o�֐�
	static CLife * Create(D3DXVECTOR3 pos, int nCntLife);				//���C�t�̐���
	static HRESULT Load(void);															//�e�N�X�`����ǂݍ��ޏ���
	static void Unload(void);																	//�e�N�X�`����j�����鏈��

private:
	static int								m_nLife;												//���C�t
	D3DXVECTOR3					m_pos;													//�ʒu

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9		m_pTexture;								// �e�N�X�`���ւ̃|�C���^
};

#endif