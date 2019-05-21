//=============================================================================
//
// ���Ƃ����� [animal.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _ANIMAL_H_	//��d�C���N���[�h�h�~
#define _ANIMAL_H_

#include	"main.h"		//���C��
#include	"life.h"			//���C�t
#include "bullet.h"		//�e

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ANIMALTEX					(3)														//�e�N�X�`���̍ő吔
#define PATTERN_ANIM						(0.25f)													//������
#define SIZE										(80)														//�|���S���̒��S�_����̃T�C�Y
#define ANIMAL_SPEED						(1.0f)													//���Ƃ��̃X�s�[�h
#define ANIMAL_FIELD_RANGE		(500.0f)												//�n�ʂ͈̔�
#define ANIMAL_GRAVITY					(0.5)														//�d�͉��Z
#define ANIMAL_JUMP						(7)														//�W�����v
#define LEFT_WIDTH							(70)														//���[�s�������̉�ʂ̋���
#define ANIMAL_INERTIA_SPEED		(0.15f)													//�����̃X�s�[�h
#define ANIMAL_ANIMSPEED			(20)														//���Ƃ��̃A�j���[�V�����̃X�s�[�h
#define ANIMAL_LIFE							(3)														//���Ƃ��̃��C�t

//�e�N�X�`����
#define ANIMAL_DOG				"data/TEXTURE/dog.png"						//�i�C�k�j
#define ANIMAL_MONKEY			"data/TEXTURE/monkey.png"				//�i�T���j
#define ANIMAL_KIJI					"data/TEXTURE/kiji.png"						//�i�L�W�j

//*****************************************************************************
// ���Ƃ��N���X
//*****************************************************************************
class CAnimal : public CScene2D
{
public:
	typedef enum
	{	//���Ƃ��̏�ԊǗ�
		ANIMALSTATE_NONE = 0,																//�ʏ���
		ANIMALSTATE_DAMAGE,																//�_���[�W���
		ANIMALSTATE_DEATH,																	//���񂾏��
		ANIMALSTATE_MAX																		//��ԊǗ��̍ő吔
	} ANIMALSTATE;

	typedef enum
	{	//���Ƃ��̃^�C�v����
		ANIMALTYPE_DOG = 0,																	//�C�k
		ANIMALTYPE_MONKEY,																//�T��
		ANIMALTYPE_KIJI,																			//�L�W
		ANIMALTYPE_MAX																			//���Ƃ��̍ő吔
	} ANIMALTYPE;

	CAnimal(int nPriority = 4);																	//�R���X�g���N�^
	~CAnimal();																							//�f�X�g���N�^
	HRESULT Init();																					//����������
	void Uninit(void);																					//�I������
	void Update(void);																				//�X�V����
	void Draw(void);																					//�`�揈��
	void HitAnimal(int nDamage);																//�_���[�W����

	//�ÓI�����o�֐�
	static CAnimal * Create(D3DXVECTOR3 pos, ANIMALTYPE animalType);					//���Ƃ��̐���
	static HRESULT Load(void);																//�e�N�X�`����ǂݍ��ޏ���
	static void Unload(void);																		//�e�N�X�`����j�����鏈��
	static ANIMALTYPE GetAnimal(void) { return m_animalType; }		//���Ƃ��̃^�C�v�擾����

	int GetLife(void) { return m_nLife; }

private:
	ANIMALSTATE							m_animalState;								//���Ƃ��̏�ԊǗ��̕ϐ�
	D3DXVECTOR3							m_pos;												//�ʒu
	D3DXVECTOR3							m_move;											//�ړ���
	bool												m_bJump;										//�W�����v���Ă��邩���Ă��Ȃ���
	int												m_nCntAnim;									//�J�E���^�[�A�j���[�V����
	int												m_nPatternAnim;								//�p�^�[���A�j���[�V����
	int												m_nLife;											//���C�t
	int												m_nCntState;									//��ԊǗ��̃J�E���^�[
	int												m_nSelect;										//���Ƃ��؂�ւ�
	CBullet::BULLETTYPE				m_BulletType;									//�e�̃^�C�v�̊Ǘ�

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_ANIMALTEX];		//���L�e�N�X�`���ւ̃|�C���^
	static ANIMALTYPE					m_animalType;								//���Ƃ����g��������ϐ�
	static CLife * m_pLife[ANIMAL_LIFE];												//���C�t�N���X�̎擾

};
#endif