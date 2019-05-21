//=============================================================================
//
// ���S���� [logo.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _LOGO_H_		//��d�C���N���[�h�h�~
#define _LOGO_H_

#include	"main.h"		//���C��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LOGOTEXTURE		(9)													//�e�N�X�`���̍ő吔

//*****************************************************************************
// ���S�N���X
//*****************************************************************************
class CLogo : public CScene2D
{
public:
	typedef enum
	{
		LOGOSTATE_NONE = 0,
		LOGOSTATE_FLASH,
		LOGOSTATE_MAX
	} LOGOSTATE;

	CLogo();																											//�f�t�H���g�R���X�g���N�^
	~CLogo();																										//�f�X�g���N�^
	HRESULT Init(void);																						//����������
	void Uninit(void);																								//�I������
	void Update(void);																							//�X�V����
	void Draw(void);																								//�`�揈��

	//�ÓI�����o�֐�
	static HRESULT Load(void);																			//�e�N�X�`���̊��蓖�ď���
	static void Unload(void);																					//�e�N�X�`���̔j��

	//�ÓI�����o�ϐ�
	static CLogo *Create();																					//���S�̐���

private:
	CScene2D * m_apScene2D[MAX_LOGOTEXTURE];										//�|���S���̐���
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;												// ���_�o�b�t�@�ւ̃|�C���^
	D3DXCOLOR									m_col;														//�F�̊Ǘ�
	int													m_BgMove;												//	�w�i�𓮂����ϐ�
	int													m_nCntFlash;											//�_�ŊǗ�����J�E���^�[
	float													m_fFlash;													//�_�ł���ϐ�
	LOGOSTATE									m_logoState;											//���S�̃X�e�[�g

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_LOGOTEXTURE];		//�e�N�X�`���̃|�C���^
};

#endif