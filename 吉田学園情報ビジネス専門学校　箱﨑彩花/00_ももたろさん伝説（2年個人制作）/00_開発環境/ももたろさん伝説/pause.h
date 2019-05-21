//=============================================================================
//
// �|�[�Y���� [pause.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _PAUSE_H_		//��d�C���N���[�h�h�~
#define _PAUSE_H_

#include	"main.h"		//���C��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PAUSE_PRIORITY			(5)															//�|�[�Y�̗D�揇��
#define PAUSE_TEXTURE			(5)															//�e�N�X�`���̍ő吔
#define PAUSEMENU					(3)															//���j���[�̐�

//�e�N�X�`����
#define PAUSE_PAUSEMENU	"data/TEXTURE/pausemenu.jpg"			//���j���[�̔w�i
#define PAUSE_CONTINUE		"data/TEXTURE/continue.png"				//�Â���
#define PAUSE_RETRY				"data/TEXTURE/retry.png"						//���Ȃ���
#define PAUSE_QUIT					"data/TEXTURE/quit.png"						//�^�C�g���ɖ߂�

//*****************************************************************************
// �w�i�N���X
//*****************************************************************************
class CPause : public CScene
{
public:
	typedef enum
	{	//�|�[�Y�̎�ނ킯
		PAUSESTATE_NONE = 0,																	//������
		PAUSESTATE_CONTINUE,																	//�Â���
		PAUSESTATE_RETRY,																		//���Ȃ���
		PAUSESTATE_QUIT,																			//�^�C�g���ɖ߂�
		PAUSESTATE_MAX																				//�|�[�Y���j���[�̍ő吔
	} PAUSESTATE;

	typedef enum
	{	//�e���j���[���I�����ꂽ���̐F
		PAUSECOLOR_NONE = 0,																	//������
		PAUSECOLOR_CONTINUE,																//�Â���
		PAUSECOLOR_RETRY,																		//���Ȃ���
		PAUSECOLOR_QUIT,																			//�^�C�g���ɖ߂�
		PAUSECOLOR_MAX																			//�|�[�Y���j���[�̍ő吔
	} PAUSECOLOR;

	CPause();																								//�f�t�H���g�R���X�g���N�^
	~CPause();																								//�f�X�g���N�^
	HRESULT Init(void);																				//����������
	void Uninit(void);																						//�I������
	void Update(void);																					//�X�V����
	void Draw(void);																						//�`�揈��

	//�ÓI�����o�֐�
	static CPause * Create();																		//�w�i�̐���
	static HRESULT Load(void);																	//�e�N�X�`���̊��蓖�ď���
	static void Unload(void);																			//�e�N�X�`���̔j��
	static bool GetPause(void) { return m_bPause; }									//�|�[�Y�̏�Ԃ��擾
	static void SetPause(bool bPause);														//�|�[�Y�̐ݒ�

private:
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;										// ���_�o�b�t�@�ւ̃|�C���^
	PAUSESTATE									m_PauseState;								//�|�[�Y�̏�Ԃ��Ǘ�
	PAUSECOLOR									m_PauseColor;								//�|�[�Y�ł̐F�̊Ǘ�
	int													m_SelectNum;									//	�w�i�𓮂����ϐ�

	//�ÓI�����o�ϐ�
	static CScene2D * m_apScene2D[PAUSE_TEXTURE];							//�|���S���̐���
	static LPDIRECT3DTEXTURE9		m_pTexture[PAUSE_TEXTURE];		//�e�N�X�`���̃|�C���^
	static bool										m_bPause;
};

#endif