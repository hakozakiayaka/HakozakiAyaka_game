//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _EXFFECT_H_		//��d�C���N���[�h�h�~
#define _EXFFECT_H_

#include	"main.h"			//���C��

//*****************************************************************************
// �G�t�F�N�g�N���X
//*****************************************************************************
class CEffect : public CScene2D
{
public:
	CEffect(int nPriority);																					//�R���X�g���N�^
	~CEffect();																									//�f�X�g���N�^
	HRESULT Init(void);																					//����������
	void Uninit(void);																							//�I������
	void Update(void);																						//�X�V����
	void Draw(void);																							//�`�揈��

	//�ÓI�����o�֐�
	static CEffect * Create(D3DXVECTOR3 pos, D3DXCOLOR col);				//�I�u�W�F�N�g�̐���
	static HRESULT Load(void);																		//�e�N�X�`����ǂݍ��ޏ���
	static void Unload(void);																				//�e�N�X�`����j�����鏈��

private:
	D3DXCOLOR								m_col;														// �F
	int												m_nLife;													// �\������(����)
	float												m_nSize;													//�G�t�F�N�g�̃T�C�Y

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture;												//���L�e�N�X�`���ւ̃|�C���^
};
#endif