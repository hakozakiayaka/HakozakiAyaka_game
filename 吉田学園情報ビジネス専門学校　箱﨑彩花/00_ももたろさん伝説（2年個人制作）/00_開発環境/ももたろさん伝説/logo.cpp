//=============================================================================
//
// ���S���� [logo.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "main.h"				//���C��
#include "scene.h"				//�V�[��
#include "renderer.h"			//�����_�����O
#include "scene2D.h"			//�V�[��2D
#include "manager.h"			//�}�l�[�W���[
#include "input.h"				//����
#include "logo.h"					//���S

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LOGO_PRIORITY			(0)			//�w�i�̗D�揇��

//�e�N�X�`����
#define LOGO_TITLE								"data/TEXTURE/titlelogo.png"						//�^�C�g��
#define LOGO_PRESSENTER					"data/TEXTURE/pressEnter.png"					//�v���X�G���^�[
#define LOGO_RANKING						"data/TEXTURE/rankinglogo.png"					//�����L���O���S
#define LOGO_RANKINGLINE				"data/TEXTURE/rankingLine.png"					//�����L���O�̉����C��
#define LOGO_RANK								"data/TEXTURE/rank.png"								//����
#define LOGO_CLEAR								"data/TEXTURE/gameClear.png"					//�Q�[���N���A
#define LOGO_OVER								"data/TEXTURE/gameOver.png"					//�Q�[���I�[�o�[
#define LOGO_TUTORIAL						"data/TEXTURE/tutorial100.png"					//�`���[�g���A�����S
#define LOGO_RESULT							"data/TEXTURE/resultlogo.png"					//���U���g���S

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	 CLogo::m_pTexture[MAX_LOGOTEXTURE] = {};		//�e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLogo::CLogo() : CScene2D(LOGO_PRIORITY)
{
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_fFlash = 0.0f;
	m_nCntFlash = 0;

	for (int nCntLogo = 0; nCntLogo < MAX_LOGOTEXTURE; nCntLogo++)
	{
		m_apScene2D[nCntLogo] = NULL;
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLogo::~CLogo()
{	//���������Ȃ�
}

//=============================================================================
// ���S�̐���
//=============================================================================
CLogo *CLogo::Create()
{
	CLogo *pLogo = NULL;

	//�w�i�N���X�̓��I�m��
	if (pLogo == NULL)
	{
		pLogo = new CLogo;
	}

	//�w�i�̏���������
	if (pLogo != NULL)
	{
		pLogo->Init();
	}

	return pLogo;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLogo::Init(void)
{
	CManager::MODE BgMode = CManager::GetMode();

	switch (BgMode)
	{
	case CManager::MODE_TITLE:
		if (m_apScene2D[0] == NULL)
		{	//�������낳��`�����S
			m_apScene2D[0] = new CScene2D(LOGO_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();
			m_apScene2D[0]->BindTexture(m_pTexture[0]);					//�e�N�X�`���̊��蓖��
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
			m_apScene2D[0]->SetSize(800.0f, 250.0f);
		}

		if (m_apScene2D[1] == NULL)
		{	//�v���X�G���^�[���S
			m_apScene2D[1] = new CScene2D(LOGO_PRIORITY);
		}
		if (m_apScene2D[1] != NULL)
		{
			m_apScene2D[1]->Init();
			m_apScene2D[1]->BindTexture(m_pTexture[1]);																//�e�N�X�`���̊��蓖��
			m_apScene2D[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_apScene2D[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f));
			m_apScene2D[1]->SetSize(380.0f, 90.0f);
			m_logoState = CLogo::LOGOSTATE_FLASH;
			m_fFlash = 0.05f;
		}
		break;

	case CManager::MODE_TUTORIAL:
		if (m_apScene2D[0] == NULL)
		{	//�v���X�G���^�[���S
			m_apScene2D[0] = new CScene2D(LOGO_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();
			m_apScene2D[0]->BindTexture(m_pTexture[1]);																//�e�N�X�`���̊��蓖��
			m_apScene2D[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f));
			m_apScene2D[0]->SetSize(380.0f, 90.0f);
			m_logoState = CLogo::LOGOSTATE_FLASH;
			m_fFlash = 0.05f;
		}
		break;

	case CManager::MODE_GAMECLEAR:
		if (m_apScene2D[0] == NULL)
		{
			m_apScene2D[0] = new CScene2D(LOGO_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();																									//������
			m_apScene2D[0]->BindTexture(m_pTexture[4]);																//�e�N�X�`���̊��蓖��
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(300.0f, 200.0f, 0.0f));								//�ʒu�̐ݒ�
			m_apScene2D[0]->SetSize(450.0f, 150.0f);																		//�T�C�Y�̐ݒ�
		}

		if (m_apScene2D[1] == NULL)
		{	//�v���X�G���^�[���S
			m_apScene2D[1] = new CScene2D(LOGO_PRIORITY);
		}
		if (m_apScene2D[1] != NULL)
		{
			m_apScene2D[1]->Init();
			m_apScene2D[1]->BindTexture(m_pTexture[8]);																//�e�N�X�`���̊��蓖��
			m_apScene2D[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_apScene2D[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f));
			m_apScene2D[1]->SetSize(380.0f, 90.0f);
			m_logoState = CLogo::LOGOSTATE_FLASH;
			m_fFlash = 0.05f;
		}
		break;

	case CManager::MODE_GAMEOVER:
		if (m_apScene2D[0] == NULL)
		{
			m_apScene2D[0] = new CScene2D(LOGO_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();																									//������
			m_apScene2D[0]->BindTexture(m_pTexture[5]);																//�e�N�X�`���̊��蓖��
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(850.0f, 200.0f, 0.0f));								//�ʒu�̐ݒ�
			m_apScene2D[0]->SetSize(550.0f, 170.0f);																		//�T�C�Y�̐ݒ�
		}
		break;

	case CManager::MODE_RANKING:
		if (m_apScene2D[0] == NULL)
		{	//�����L���O���S
			m_apScene2D[0] = new CScene2D(LOGO_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();																									//������
			m_apScene2D[0]->BindTexture(m_pTexture[2]);																//�e�N�X�`���̊��蓖��
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 70.0f, 0.0f));		//�ʒu�̐ݒ�
			m_apScene2D[0]->SetSize(300.0f, 70.0f);																			//�T�C�Y�ݒ�
		}

		if (m_apScene2D[1] == NULL)
		{	//����
			m_apScene2D[1] = new CScene2D(LOGO_PRIORITY);
		}
		if (m_apScene2D[1] != NULL)
		{
			m_apScene2D[1]->Init();																									//������
			m_apScene2D[1]->BindTexture(m_pTexture[6]);																//�e�N�X�`���̊��蓖��
			m_apScene2D[1]->SetPosition(D3DXVECTOR3(300.0f, 400.0f, 0.0f));								//�ʒu�̐ݒ�
			m_apScene2D[1]->SetSize(150.0f, 500.0f);																		//�T�C�Y�̐ݒ�
		}

		if (m_apScene2D[2] == NULL)
		{	//�v���X�G���^�[���S
			m_apScene2D[2] = new CScene2D(LOGO_PRIORITY);
		}
		if (m_apScene2D[2] != NULL)
		{
			m_apScene2D[2]->Init();
			m_apScene2D[2]->BindTexture(m_pTexture[8]);																//�e�N�X�`���̊��蓖��
			m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_apScene2D[2]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f));
			m_apScene2D[2]->SetSize(380.0f, 90.0f);
			m_logoState = CLogo::LOGOSTATE_FLASH;
			m_fFlash = 0.05f;
		}

		break;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLogo::Uninit(void)
{	//�w�i�j��
	for (int nCntBg = 0; nCntBg < MAX_LOGOTEXTURE; nCntBg++)
	{
		m_apScene2D[nCntBg]->Uninit();
		m_apScene2D[nCntBg] = NULL;
	}

	//�I�u�W�F�N�g�i�������g�j�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLogo::Update(void)
{
	CManager::MODE BgMode = CManager::GetMode();

	switch (m_logoState)
	{
	case LOGOSTATE_NONE:
		break;

	case LOGOSTATE_FLASH:
		m_col.a += m_fFlash;
		if (m_col.a <= 0.0f || m_col.a >= 1.0f)
		{
			m_fFlash *= -1.0f;
		}
		break;
	}

	if (BgMode == CManager::MODE_TITLE)
	{
		if (m_logoState == LOGOSTATE_FLASH)
		{
			m_apScene2D[1]->SetColor(m_col);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CLogo::Draw(void)
{
}

#if 1
//=============================================================================
// �e�N�X�`����ǂݍ���
//=============================================================================
HRESULT CLogo::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//�f�o�C�X�̎擾
	CRenderer * pRenderer = CManager::GetRenderer();						//�����_�����O�N���X�̌Ăяo��

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, LOGO_TITLE, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, LOGO_PRESSENTER, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, LOGO_RANKING, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, LOGO_RANKINGLINE, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, LOGO_CLEAR, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, LOGO_OVER, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, LOGO_RANK, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TUTORIAL, &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, LOGO_RESULT, &m_pTexture[8]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`����j��
//=============================================================================
void CLogo::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntBg = 0; nCntBg < MAX_LOGOTEXTURE; nCntBg++)
	{
		if (m_pTexture[nCntBg] != NULL)
		{
			m_pTexture[nCntBg]->Release();
			m_pTexture[nCntBg] = NULL;
		}
	}
}
#endif