//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _PLAYER_H_		//��d�C���N���[�h�h�~
#define _PLAYER_H_

#include	"main.h"			//���C��

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBullet;				//�e

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE									(80)														//�|���S���̒��S�_����̃T�C�Y
#define PLAYER_SPEED					(1.0f)													//�v���C���[�̃X�s�[�h
#define PLAYER_FIELD_RANGE		(500.0f)												//�n�ʂ͈̔�
#define GRAVITY								(0.5)														//�d�͉��Z
#define PLAYER_JUMP					(10)														//�W�����v
#define PLAYER_INERTIA_SPEED	(0.2f)													//�����̃X�s�[�h

//�e�N�X�`����
#define PLAYER_NAME		"data/TEXTURE/momotarou.png"		//�i�v���C���[�j

//*****************************************************************************
// �v���C���[�N���X
//*****************************************************************************
class CPlayer : public CScene2D
{
public:
	CPlayer(int nPriority = 4);														//�R���X�g���N�^
	~CPlayer();																				//�f�X�g���N�^
	HRESULT Init();																		//����������
	void Uninit(void);																		//�I������
	void Update(void);																	//�X�V����
	void Draw(void);																		//�`�揈��

	//�ÓI�����o�֐�
	static CPlayer * Create(D3DXVECTOR3 pos);						//�v���C���[�̐���
	static HRESULT Load(void);													//�e�N�X�`����ǂݍ��ޏ���
	static void Unload(void);															//�e�N�X�`����j�����鏈��

private:
	bool												m_bJump;							//�W�����v���Ă��邩���Ă��Ȃ���
	D3DXVECTOR3							m_pos;									//�ʒu
	D3DXVECTOR3							m_move;								//�ړ���

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture;							//���L�e�N�X�`���ւ̃|�C���^
};
#endif