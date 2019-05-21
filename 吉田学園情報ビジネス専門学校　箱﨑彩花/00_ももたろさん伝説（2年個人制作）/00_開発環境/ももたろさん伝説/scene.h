//=============================================================================
//
// �V�[������ [scene.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _SCENE_H_		//��d�C���N���[�h�h�~
#define _SCENE_H_

#include	"main.h"		//���C��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_DATA				(10000)			//�f�[�^�̍ő吔
#define PRIORITY				(8)					//�D�揇�ʂ̍ő吔

//*****************************************************************************
// �I�u�W�F�N�g�N���X
//*****************************************************************************
class CScene
{
public:
	//�I�u�W�F�N�g�̎��
	typedef enum
	{
		OBJTYPE_NONE = 0,									//������
		OBJTYPE_BG,												//�w�i
		OBJTYPE_PLAYER,										//�v���C���[
		OBJTYPE_ANIMAL,										//���Ƃ�
		OBJTYPE_ENEMY,										//�G�l�~�[
		OBJTYPE_BULLET,										//�e
		OBJTYPE_EFFECT,										//�G�t�F�N�g
		OBJTYPE_FADE,											//�t�F�[�h
		OBJTYPE_PAUSE,										//�|�[�Y
		OBJTYPE_LIFE,											//���C�t
		OBJTYPE_MAX											//��ނ̍ő�l
	} OBJTYPE;

	CScene(int nPriority = 3);								//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
	virtual ~CScene();											//�f�X�g���N�^
	virtual HRESULT Init(void) = 0;						//����������
	virtual void Uninit(void) = 0;							//�I������
	virtual void Update(void) = 0;							//�X�V����
	virtual void Draw(void) = 0;							//�`�揈��

	//�ÓI�����o�֐�
	void SetObjType(OBJTYPE objType);				//�I�u�W�F�N�g�̐ݒ�
	OBJTYPE GetObjType(void);							//�I�u�W�F�N�g�̎�ނ��擾���鏈��

	//�ÓI�����o�֐�
	static CScene * GetScene(int nPriority, int nIdx);				//�V�[���̎擾
	static void ReleaseAll(void);												//�S�Ă̏I������
	static void ReleaseFadeAll(void);										//�t�F�[�h�ȊO�I������
	static void UpdateAll(void);													//�S�Ă̍X�V����
	static void DrawAll(void);													//�S�Ă̕`�揈��
	static void SetPause(bool bPause);

private:
	//�ÓI�����o�ϐ��錾
	static int			m_nNumAll;													//�|���S���̑���
	static CScene *m_apScene[PRIORITY][MAX_DATA];		//�|���S���̐���
	static bool		 m_bPause;

	int					m_nPriority;								//�D�揇�ʂ̔ԍ�
	int					m_nID;										//�������g�̔ԍ�
	OBJTYPE			m_objType;								//�I�u�W�F�N�g�̎��

protected:
	void Release(void);											//�I�u�W�F�N�g��j�����鏈��
};

#endif