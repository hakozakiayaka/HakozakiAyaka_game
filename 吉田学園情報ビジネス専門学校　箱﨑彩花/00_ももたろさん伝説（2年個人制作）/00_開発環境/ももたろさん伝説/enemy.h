//=============================================================================
//
// �G�̏��� [enemy.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _ENEMY_H_	//��d�C���N���[�h�h�~
#define _ENEMY_H_

#include	"main.h"		//���C��
#include "bullet.h"		//�e

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_TEXTURE				(3)												//�e�N�X�`���̍ő吔
#define SIZE									(80)												//�|���S���̒��S�_����̃T�C�Y
#define ENEMY_LIFE						(2)												//�G�̃��C�t�ݒ�
#define DAMAGE_STATE				(5)												//�_���[�W�󂯂����̌��鎞��
#define ENEMY_FIELD_RANGE		(500.0f)										//�n�ʂ͈̔�
#define ENEMY_GRAVITY				(0.5)												//�d�͉��Z
#define ENEMY_JUMP					(7)												//�W�����v
#define ENEMY_SPEED					(0.05f)											//�X�s�[�h

//�e�N�X�`����
#define ENEMY_NAME				"data/TEXTURE/akaoni.png"				//�i�������Ɂj
#define ENEMY_NAME1				"data/TEXTURE/aooni.png"				//�i�������Ɂj
#define ENEMY_NAME2				"data/TEXTURE/kioni.png"					//�i�����남�Ɂj

//*****************************************************************************
// �G�N���X
//*****************************************************************************
class CEnemy : public CScene2D
{
public:
	typedef enum
	{	//�G�̏�Ԃ̎��
		ENEMYSTATE_NONE = 0,																		//�ʏ���
		ENEMYSTATE_DAMAGE,																		//�_���[�W���
		ENEMYSTATE_DEATH,																			//���񂾏��
		ENEMYSTATE_MAX																				//��Ԃ̎�ނ̐�
	} ENEMYSTATE;

	typedef enum
	{	//�S�̃^�C�v����
		ENEMYTYPE_RED,																					//��������
		ENEMYTYPE_BLUE,																				//��������
		ENEMYTYPE_YELLOW,																			//�����남��
		ENEMYTYPE_BOSS,																				//�{�X
		ENEMYTYPE_MAX																					//�S�̃^�C�v�̍ő吔
	} ENEMYTYPE;

	CEnemy();																									//�R���X�g���N�^
	~CEnemy();																									//�f�X�g���N�^
	HRESULT Init();																							//����������
	void Uninit(void);																							//�I������
	void Update(void);																						//�X�V����
	void Draw(void);																							//�`�揈��
	void HitEnemy(int nDamage);																		//�_���[�W����
	//void SetEnemy(D3DXVECTOR3 pos, float fWidth, float fHeight);

	//�ÓI�����o�֐�
	static CEnemy * Create(D3DXVECTOR3 pos, ENEMYTYPE enemyType);//�G�̐���
	static ENEMYTYPE GetEnemyType(void) { return m_enemyType; }			//�G�̃^�C�v���擾����
	static HRESULT Load(void);																		//�e�N�X�`����ǂݍ��ޏ���
	static void Unload(void);																				//�e�N�X�`����j�����鏈��

	//�ÓI�����o�ϐ�
	static int m_nNumEnemy;																			//�G�̑���

private:
	ENEMYSTATE								m_enemyState;										//�G�̏�Ԃ̕ϐ�
	D3DXVECTOR3							m_pos;														//�ʒu
	D3DXVECTOR3							m_move;													//�ړ���
	bool												m_bJump;												//�W�����v���Ă��邩���Ă��Ȃ���
	CBullet::BULLETTYPE				m_BulletType;											//�e�̃^�C�v�̊Ǘ�
	int												m_nCntState;											//��ԊǗ��̃J�E���^�[
	int												m_nLife;													//�G�̃��C�t
	float												m_fSpeed;												//�X�s�[�h

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[ENEMY_TEXTURE];			//���L�e�N�X�`���ւ̃|�C���^
	static ENEMYTYPE						m_enemyType;										//�S�̃^�C�v�����ϐ�
};
#endif