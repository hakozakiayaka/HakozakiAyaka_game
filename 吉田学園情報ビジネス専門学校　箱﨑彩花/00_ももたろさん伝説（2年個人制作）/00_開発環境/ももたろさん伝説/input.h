//=============================================================================
//
//���͏��� [input.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _INPUT_H_		//��d�C���N���[�h�h�~
#define _INPUT_H_

#include	"main.h"		//���C��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_KEY_MAX					(256)				// �L�[�̍ő吔
#define MAX_CONTROLLERS         (1)					//�R���g���[���[�̍ő吔
#define NUM_JOYKEY_MAX		     (128)				//�L�[�̍ő吔

//*****************************************************************************
// ���͏����̃N���X
//*****************************************************************************
class CInput
{
public:
	CInput();																									//�R���X�g���N�^
	virtual ~CInput();																					//�f�X�g���N�^
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);				//����������
	virtual void Uninit(void);																			//�I������
	virtual void Update(void) = 0;																	//�X�V�����i�������z�֐��j

protected:
	LPDIRECTINPUTDEVICE8		m_pDevice;												//���͏����̃f�o�C�X�������ϐ�

	//�ÓI�����o�ϐ�
	static LPDIRECTINPUT8			m_pInput;												//�I�u�W�F�N�g�̖{��
};

//*****************************************************************************
// �L�[�{�[�h�N���X
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();																					//�R���X�g���N�^
	~CInputKeyboard();																				//�f�X�g���N�^
	HRESULT Init(HINSTANCE hIIstance, HWND hWnd);							//����������
	void Uninit(void);																						//�I������
	void Update(void);																					//�X�V����
	bool GetPress(int nKey);																			//�L�[�{�[�h�̓��͏��(�v���X���)���擾
	bool GetTrigger(int nKey);																		//�L�[�{�[�h�̓��͏��(�g���K�[���)���擾

private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
};

//*****************************************************************************
// �R���g���[���[�N���X
//*****************************************************************************
class CDirectXInput : public CInput
{
public:
	typedef enum
	{//�{�^���̉�����
		INPUT_JOYSTATE_NOTPUSH = 0,
		INPUT_JOYSTATE_PUSH,
		INPUT_JOYSTATE_NONE,
	}InputJoyState;

	CDirectXInput();
	~CDirectXInput();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	static void SetInputJoyState(InputJoyState state);
	static bool GetConnectionJoypad(void) { return m_bConnectionJoypad; }
	static InputJoyState GetInputJoyState(void) { return m_nState; }

private:
	static InputJoyState m_nState;											//�W���C�p�b�h�̏��
	static bool m_bConnectionJoypad;										  //�W���C�p�b�h�̐ڑ����
	LPDIRECTINPUTDEVICE8 m_pDevJoyPad = NULL;           //���̓f�o�C�X(�W���C�p�b�h)�ւ̃|�C���^
	BYTE m_aJoyKeyState[NUM_JOYKEY_MAX];					  //�W���C�p�b�h�̓��͏��(�v���X���)
	BYTE m_aJoyKeyStateTrigger[NUM_JOYKEY_MAX];         //�W���C�p�b�h�̓��͏��(�g���K�[���)
};

#endif