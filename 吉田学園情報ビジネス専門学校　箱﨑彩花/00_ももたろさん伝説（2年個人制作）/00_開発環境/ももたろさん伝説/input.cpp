//=============================================================================
//
// όΝ [input.cpp]
// Author :  ϊ±ΚΤ
//
//=============================================================================
#include "input.h"			//όΝ

//*****************************************************************************
// ΓIoΟιΎ
//*****************************************************************************
LPDIRECTINPUT8 CInput::m_pInput = NULL;
bool CDirectXInput::m_bConnectionJoypad = false;
CDirectXInput::InputJoyState CDirectXInput::m_nState = INPUT_JOYSTATE_NOTPUSH;

//=============================================================================
// RXgN^
//=============================================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//=============================================================================
// fXgN^
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// ϊ»
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInputIuWFNgΜΆ¬
	if (m_pInput == NULL)
	{	//{ΜͺΒ­ηκΔ’Θ©Α½ηΆ¬
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// IΉ
//=============================================================================
void CInput::Uninit(void)
{
	// όΝfoCX(L[{[h)ΜJϊ
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();	//L[{[hΦΜANZX πϊό
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// DirectInputIuWFNgΜJϊ
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// RXgN^	L[{[h
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	//L[{[hξρΜNA
	m_aKeyState[0];
	m_aKeyStateTrigger[0];
}

//=============================================================================
// fXgN^		L[{[h
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{	//½ΰ©Θ’
}

//=============================================================================
// ϊ»			L[{[h
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hIIstance, HWND hWnd)
{
	//{ΜΜΆ¬ΜΔΡo΅
	CInput::Init(hIIstance, hWnd);

	// όΝfoCX(L[{[h)ΜΆ¬
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// f[^tH[}bgπέθ
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// ¦²[hπέθ
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// L[{[hΦΜANZX πlΎ(όΝ§δJn)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// IΉ				L[{[h
//=============================================================================
void CInputKeyboard::Uninit(void)
{	//{ΜΜIΉΜΔΡo΅
	CInput::Uninit();
}

//=============================================================================
// XV				L[{[h
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	// όΝfoCX©ηf[^πζΎ
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	//L[{[hΜόΝξρΫΆ
		}
	}
	else
	{
		m_pDevice->Acquire();	//L[{[hΦΜANZX πlΎ
	}
}

//=============================================================================
// L[{[hΜόΝξρ(vXξρ)πζΎ
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// L[{[hΜόΝξρ(gK[ξρ)πζΎ
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// RXgN^
//=============================================================================
CDirectXInput::CDirectXInput()
{
}
//=============================================================================
// fXgN^
//=============================================================================
CDirectXInput::~CDirectXInput()
{
}

//=============================================================================
// ϊ»
//=============================================================================
HRESULT CDirectXInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//eNXΜϊ»
	CInput::Init(hInstance, hWnd);

	m_nState = INPUT_JOYSTATE_NOTPUSH;
	m_bConnectionJoypad = false;

	DWORD dwResult;
	for (DWORD dCnt = 0; dCnt < MAX_CONTROLLERS; dCnt++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// XInput©ηRg[ΜσΤπζΎ·ι
		dwResult = XInputGetState(dCnt, &state);

		if (dwResult == ERROR_SUCCESS)
		{
#ifdef _DEBUG
			//MessageBox(0, "Rg[[ͺΪ±³κΔ’ά·", "", MB_OK);
#endif // _DEBUG
			// fbh][Μέθ
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
			//MessageBox(0, "Rg[[ͺΪ±³κΔ’άΉρ", "", MB_OK);
#endif // _DEBUG

			m_bConnectionJoypad = false;
		}
	}
	return S_OK;
}

//=============================================================================
// IΉ
//=============================================================================
void CDirectXInput::Uninit(void)
{
	XInputEnable(false);

	//eNXΜIΉ
	CInput::Uninit();
}
//=============================================================================
// XV
//=============================================================================
void CDirectXInput::Update(void)
{
}

//=============================================================================
// CvbgΜσΤΜέθ
//=============================================================================
void CDirectXInput::SetInputJoyState(CDirectXInput::InputJoyState state)
{
	m_nState = state;
}