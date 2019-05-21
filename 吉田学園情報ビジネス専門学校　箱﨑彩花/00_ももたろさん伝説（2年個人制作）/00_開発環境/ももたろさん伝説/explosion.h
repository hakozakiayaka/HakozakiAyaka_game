//=============================================================================
//
// �����̏��� [explosion.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _EXPLOSION_H_		//��d�C���N���[�h�h�~
#define _EXPLOSION_H_

#include	"main.h"				//���C��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE								(80)			//�|���S���̒��S�_����̃T�C�Y
#define EXPLOSION_SPEED		(10)			//�����̃X�s�[�h
#define MAX_BULLET				(256)		//�e�̍ő吔

//�e�N�X�`��
#define EXPLOSION_NAME		"data/TEXTURE/explosion000.png"

//*****************************************************************************
// �����N���X
//*****************************************************************************
class CExplosion : public CScene2D
{
public:
	CExplosion();																//�R���X�g���N�^
	~CExplosion();															//�f�X�g���N�^
	HRESULT Init(void);													//����������
	void Uninit(void);															//�I������
	void Update(void);														//�X�V����
	void Draw(void);															//�`�揈��

	//�ÓI�����o�֐�
	static CExplosion * Create(D3DXVECTOR3 pos);		//�I�u�W�F�N�g�̐���
	static HRESULT Load(void);										//�e�N�X�`����ǂݍ��ޏ���
	static void Unload(void);												//�e�N�X�`����j�����鏈��

private:
	int												m_nCntAnim;			//�A�j���[�V�����̃J�E���^�[
	int												m_nPatternAnim;		//�A�j���[�V������No.

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture;				//���L�e�N�X�`���ւ̃|�C���^
};
#endif