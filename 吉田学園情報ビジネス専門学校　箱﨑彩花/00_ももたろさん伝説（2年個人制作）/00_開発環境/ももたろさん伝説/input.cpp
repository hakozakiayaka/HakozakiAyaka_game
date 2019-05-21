//=============================================================================
//
// ���͏��� [input.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "input.h"			//����

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECTINPUT8 CInput::m_pInput = NULL;
bool CDirectXInput::m_bConnectionJoypad = false;
CDirectXInput::InputJoyState CDirectXInput::m_nState = INPUT_JOYSTATE_NOTPUSH;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (m_pInput == NULL)
	{	//�{�̂������Ă��Ȃ������琶��
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CInput::Uninit(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();	//�L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// �R���X�g���N�^	�L�[�{�[�h
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	//�L�[�{�[�h���̃N���A
	m_aKeyState[0];
	m_aKeyStateTrigger[0];
}

//=============================================================================
// �f�X�g���N�^		�L�[�{�[�h
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{	//���������Ȃ�
}

//=============================================================================
// ����������			�L�[�{�[�h
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hIIstance, HWND hWnd)
{
	//�{�̂̐����̌Ăяo��
	CInput::Init(hIIstance, hWnd);

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// �I������				�L�[�{�[�h
//=============================================================================
void CInputKeyboard::Uninit(void)
{	//�{�̂̏I�������̌Ăяo��
	CInput::Uninit();
}

//=============================================================================
// �X�V����				�L�[�{�[�h
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	//�L�[�{�[�h�̓��͏��ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CDirectXInput::CDirectXInput()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CDirectXInput::~CDirectXInput()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CDirectXInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�e�N���X�̏���������
	CInput::Init(hInstance, hWnd);

	m_nState = INPUT_JOYSTATE_NOTPUSH;
	m_bConnectionJoypad = false;

	DWORD dwResult;
	for (DWORD dCnt = 0; dCnt < MAX_CONTROLLERS; dCnt++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// XInput����R���g���[���̏�Ԃ��擾����
		dwResult = XInputGetState(dCnt, &state);

		if (dwResult == ERROR_SUCCESS)
		{
#ifdef _DEBUG
			//MessageBox(0, "�R���g���[���[���ڑ�����Ă��܂�", "", MB_OK);
#endif // _DEBUG
			// �f�b�h�]�[���̐ݒ�
			if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
				(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
			{
				state.Gamepad.sThumbLX = 0;
				state.Gamepad.sThumbLY = 0;
			}

			if ((state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
				state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
				(state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
					state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
			{
				state.Gamepad.sThumbRX = 0;
				state.Gamepad.sThumbRY = 0;
			}

			m_bConnectionJoypad = true;
		}
		else
		{
#ifdef _DEBUG
			//MessageBox(0, "�R���g���[���[���ڑ�����Ă��܂���", "", MB_OK);
#endif // _DEBUG

			m_bConnectionJoypad = false;
		}
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CDirectXInput::Uninit(void)
{
	XInputEnable(false);

	//�e�N���X�̏I������
	CInput::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CDirectXInput::Update(void)
{
}

//=============================================================================
// �C���v�b�g�̏�Ԃ̐ݒ�
//=============================================================================
void CDirectXInput::SetInputJoyState(CDirectXInput::InputJoyState state)
{
	m_nState = state;
}