//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _FADE_H_		//��d�C���N���[�h�h�~
#define _FADE_H_

#include	"main.h"		//���C��

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CManager;		//�}�l�[�W���[

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FADE_PRIORITY	(0)															//�w�i�̗D�揇��

//�e�N�X�`����
#define LODING_TEX		"data/TEXTURE/lodinglogo.png"				//�ǂݍ��ݒ�

//*****************************************************************************
// �t�F�[�h�N���X
//*****************************************************************************
class CFade : public CScene
{
public:
	typedef enum
	{	//�t�F�[�h��Ԃ̃^�C�v����
		FADE_NONE = 0,															//�������Ă��Ȃ����
		FADE_IN,																			//�t�F�[�h�C�����
		FADE_OUT,																		//�t�F�[�h�A�E�g���
		FADE_MAX																		//�t�F�[�h��Ԃ̍ő吔
	} FADE;

	CFade();
	~CFade();																			//�f�X�g���N�^
	HRESULT Init(void);															//����������
	void Uninit(void);																	//�I������
	void Update(void);																//�X�V����
	void Draw(void);																	//�`�揈��

	//�ÓI�����o�֐�
	//static HRESULT Load(void);												//�e�N�X�`���̊��蓖�ď���
	//static void Unload(void);														//�e�N�X�`���̔j��
	static void SetFade(CManager::MODE modeNext);			//�t�F�[�h�̐ݒ�
	static FADE GetFade(void) { return m_fade; }					//�t�F�[�h�̎擾

private:
	//CScene2D * m_apScene2D;												//�|���S���̐���

	//�ÓI�����o�ϐ�
	//static LPDIRECT3DTEXTURE9					m_pTexture;		//�e�N�X�`���̃|�C���^
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	static FADE													m_fade;			//�t�F�[�h�̏��
	static CManager::MODE								m_modeNext;	//���̃��[�h
	static D3DXCOLOR										m_colorFade;	//�t�F�[�h�̐F
};
#endif