//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _SOUND_H_		//��d�C���N���[�h�h�~
#define _SOUND_H_

#include "main.h"			//���C��

//*****************************************************************************
// �T�E���h�N���X
//*****************************************************************************
class CSound
{
public:
	//�p�����[�^�\���̒�`
	typedef struct
	{
		char *pFilename;								// �t�@�C����
		int nCntLoop;									// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	} SOUNDPARAM;

	//�e�f�ނ̎��
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// �^�C�g��
		SOUND_LABEL_BGM001,				// �`���[�g���A��
		SOUND_LABEL_BGM002,				// �Q�[��
		SOUND_LABEL_BGM003,				// �Q�[���N���A
		SOUND_LABEL_BGM004,				// �Q�[���I�[�o�[
		SOUND_LABEL_BGM005,				// ��񂫂�
		SOUND_LABEL_SE_SHOT,				// �e���ˉ�
		SOUND_LABEL_SE_HIT000,			// �q�b�g��0
		SOUND_LABEL_SE_HIT001,			// �q�b�g��1
		SOUND_LABEL_SE_EXPLOSION,	// ������
		SOUND_LABEL_SE_DECIDE,			// ���艹
		SOUND_LABEL_SE_PAUSE,			// �|�[�Y
		SOUND_LABEL_SE_SELECT,			// �I����
		SOUND_LABEL_SE_JUMP,				// �W�����v���n
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);

	//�ÓI�����o�֐�
	static HRESULT PlaySound(SOUND_LABEL label);
	static void StopSound(SOUND_LABEL label);
	static void StopSound(void);

private:
	static IXAudio2 * m_pXAudio2;																		// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	static IXAudio2MasteringVoice * m_pMasteringVoice;									// �}�X�^�[�{�C�X�ւ̃|�C���^
	static IXAudio2SourceVoice * m_apSourceVoice[SOUND_LABEL_MAX];		// �\�[�X�{�C�X�ւ̃|�C���^
	static BYTE * m_apDataAudio[SOUND_LABEL_MAX];									// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];									// �I�[�f�B�I�f�[�^�T�C�Y
};
#endif