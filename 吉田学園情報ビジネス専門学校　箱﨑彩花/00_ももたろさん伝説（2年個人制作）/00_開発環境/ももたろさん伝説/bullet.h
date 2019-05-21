//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _BULLET_H_	//��d�C���N���[�h�h�~
#define _BULLET_H_

#include	"main.h"		//���C��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_BULLETTEX						(5)			//�e�N�X�`���̍ő吔
#define SIZE											(80)			//�|���S���̒��S�_����̃T�C�Y
#define BULLET_SPEED							(10.0f)		//�e�̃X�s�[�h
#define MONKEY_BULLET_SPEED		(5.0f)		//�T���F�e�̃X�s�[�h
#define REDONI_BULLET_SPEED			(5.0f)		//�ԋS�F�e�̃X�s�[�h
#define BULEONI_BULLET_SPEED		(10.0f)		//�S�F�e�̃X�s�[�h
#define YELLOWONI_BULLET_SPEED	(5.0f)		//���S�F�e�̃X�s�[�h
#define MAX_BULLET							(256)		//�e�̍ő吔
#define BULLET_LIFE								(100)		//�e�̎���
#define RANGE										(40)			//�����蔻��͈̔�
#define BULLET_PRIORITY					(4)			//�e�̗D�揇��
#define BULLET_ANIMAPEED				(10)			//�e�̃A�j���[�V�����X�s�[�h

//�e�N�X�`���̖��O
#define BULLET_DOG			"data/TEXTURE/dog_born.png"
#define BULLET_MONKEY		"data/TEXTURE/banana.png"
#define BULLET_KIJI				"data/TEXTURE/kinomi.png"
#define BULLET_ONI				"data/TEXTURE/dango.png"
#define BULLET_BOSS			"data/TEXTURE/momo.png"

//*****************************************************************************
// �e�N���X
//*****************************************************************************
class CBullet : public CScene2D
{
public:
	typedef enum
	{	//�e�̎��
		BULLETTYPE_NONE = 0,					//�����l
		BULLETTYPE_PLAYER,						//�v���C���[
		BULLETTYPE_DOG,							//�C�k
		BULLETTYPE_MONKEY,					//�T��
		BULLETTYPE_KIJI,								//�L�W
		BULLETTYPE_ENEMY,						//�G�l�~�[
		BULLETTYPE_REDONI,						//�ԋS
		BULLETTYPE_BULEONI,					//�S
		BULLETTYPE_YELLOWONI,				//���S
		BULLETTYPE_BOSS,							//�{�X�S
		BULLETTYPE_MAX							//��ނ̍ő�l
	} BULLETTYPE;

	CBullet(int nPriority);																																		//�R���X�g���N�^
	~CBullet();																																						//�f�X�g���N�^
	HRESULT Init(void);																																		//����������
	void Uninit(void);																																				//�I������
	void Update(void);																																			//�X�V����
	void Draw(void);																																				//�`�揈��
	void SetBullet(BULLETTYPE bulletType, D3DXVECTOR3 pos);
	BULLETTYPE GetBulletType(void) { return m_bulletType; }

	//�ÓI�����o�֐�
	static CBullet * Create(D3DXVECTOR3 pos, float	moveDir, BULLETTYPE bulletType);								//�I�u�W�F�N�g�̐���
	static HRESULT Load(void);																															//�e�N�X�`����ǂݍ��ޏ���
	static void Unload(void);																																	//�e�N�X�`����j�����鏈��

private:
	int								m_nLife;																														//�e�̒����i�����j
	int								m_nCntAnim;																												//�J�E���^�[�A�j���[�V����
	int								m_nPatternAnim;																											//�A�j���[�V�����̃p�^�[����
	int								m_nCntMove;																												//�ړ��̃J�E���^�[�i�C�k�j
	int								m_nChangeMove;																										//�e�̈ړ��ʁi�C�k�j
	BULLETTYPE				m_bulletType;																												//�e�̎��
	D3DXVECTOR3			m_move;																														//�ړ���
	bool								m_bUse;																														//�C�k�F���ł��邩�ǂ���
	float								m_fKeepAnimal;																											//�C�k�F���ˈʒu���Œ肷��

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_BULLETTEX];																	//���L�e�N�X�`���ւ̃|�C���^
};
#endif