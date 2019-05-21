//=============================================================================
//
// �w�i���� [bg.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _BG_H_			//��d�C���N���[�h�h�~
#define _BG_H_

#include	"main.h"		//���C��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TEXTURE		(11)															//�e�N�X�`���̍ő吔
#define BG_PRIORITY			(0)															//�w�i�̗D�揇��

//�e�N�X�`����
#define BG_SKY						"data/TEXTURE/sky000.jpg"				//��
#define BG_MOUNTAIN			"data/TEXTURE/mountain.png"			//�R
#define BG_FOREST				"data/TEXTURE/weed.png"				//��
#define BG_FIELD					"data/TEXTURE/field.png"					//�n��
#define BG_FRONTWEED		"data/TEXTURE/frontweed.png"		//��O�̑�
#define BG_STONE					"data/TEXTURE/stone.png"				//�S����
#define BG_TITLE					"data/TEXTURE/title.jpg"					//�^�C�g��
#define BG_GAMECLEAR		"data/TEXTURE/gameclear.jpg"			//�Q�[���N���A
#define BG_GAMEOVER			"data/TEXTURE/gameover.jpg"			//�Q�[���I�[�o�[
#define BG_RANKING				"data/TEXTURE/pausemenu.jpg"		//�����L���O
#define BG_TUTORIAL01		"data/TEXTURE/tutorial01.png"			//�`���[�g���A��1����
#define BG_TUTORIAL02		"data/TEXTURE/tutorial02.png"			//�`���[�g���A��2����

//*****************************************************************************
// �w�i�N���X
//*****************************************************************************
class CBg : public CScene
{
public:
	typedef enum
	{
		BGSTATE_NONE = 0,
		BGSTATE_MOVE,
		BGSTATE_MAX
	} BGSTATE;

	CBg();																										//�f�t�H���g�R���X�g���N�^
	~CBg();																									//�f�X�g���N�^
	HRESULT Init(void);																				//����������
	void Uninit(void);																						//�I������
	void Update(void);																					//�X�V����
	void Draw(void);																						//�`�揈��

	//�ÓI�����o�֐�
	static CBg *Create();																				//�w�i�̐���
	static HRESULT Load(void);																	//�e�N�X�`���̊��蓖�ď���
	static void Unload(void);																			//�e�N�X�`���̔j��
	D3DXVECTOR3 GetPos(void) { return m_pos; }

private:
	CScene2D * m_apScene2D[MAX_TEXTURE];										//�|���S���̐���
	D3DXVECTOR3								m_pos;												//�w�i�̈ʒu
	D3DXVECTOR3								m_move;											//�ړ���
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;										// ���_�o�b�t�@�ւ̃|�C���^
	int													m_BgMove;										//	�w�i�𓮂����ϐ�
	BGSTATE											m_bgState;										//��ԊǗ��̕ϐ�

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_TEXTURE];		//�e�N�X�`���̃|�C���^
};

#endif