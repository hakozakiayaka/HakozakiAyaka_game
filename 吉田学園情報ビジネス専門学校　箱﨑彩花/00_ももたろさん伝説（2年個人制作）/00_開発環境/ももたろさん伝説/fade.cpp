//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : �����ʉ�
//
//=============================================================================
#include "main.h"				//���C��
#include "scene.h"				//�V�[��
#include "renderer.h"			//�����_�����O
#include "scene2D.h"			//�V�[��2D
#include "manager.h"			//�}�l�[�W���[
#include "input.h"				//����
#include "game.h"				//�Q�[��
#include "fade.h"					//�^�C�g��

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CFade::FADE CFade::m_fade = CFade::FADE_NONE;									//�ʏ���
CManager::MODE CFade::m_modeNext = CManager::MODE_TITLE;
D3DXCOLOR CFade::m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//�F�ݒ�
LPDIRECT3DVERTEXBUFFER9 CFade::m_pVtxBuff = NULL;						//�o�b�t�@�̃|�C���^
//LPDIRECT3DTEXTURE9	 CFade::m_pTexture = NULL;									//�e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFade::CFade() : CScene(7)
{
		CFade::m_fade = FADE_NONE;
		CFade::m_modeNext = CManager::MODE_MAX;
		CFade::m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);			//�������
		//m_apScene2D = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFade::~CFade()
{	//���������Ȃ�
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CFade::Init(void)
{
	VERTEX_2D * pVtx;																				//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;											//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();						//�����_�����O�N���X�̌Ăяo��

	CScene::SetObjType(CScene::OBJTYPE_FADE);
	CFade::m_fade = FADE_IN;
	CFade::m_modeNext = CManager::MODE_TITLE;
	CFade::m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);			//�������

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * MAX_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�|���S���̐F�ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//if (m_apScene2D == NULL)
	//{	//�e�N�X�`���̓ǂݍ���
	//	m_apScene2D = new CScene2D(FADE_PRIORITY);
	//}
	//if (m_apScene2D != NULL)
	//{
	//	m_apScene2D->Init();
	//	m_apScene2D->BindTexture(m_pTexture);											//�e�N�X�`���̊��蓖��
	//	m_apScene2D->SetPosition(D3DXVECTOR3(1000.0f, 600.0f, 0.0f));	//�ʒu�̐ݒ�
	//	m_apScene2D->SetSize(200.0f, 100.0f);												//�T�C�Y�ݒ�
	//}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFade::Uninit(void)
{
	////�e�N�X�`���̔j��
	//if (m_apScene2D != NULL)
	//{
	//	m_apScene2D->Uninit();
	//	m_apScene2D = NULL;
	//}

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CFade::Update(void)
{
	VERTEX_2D * pVtx;								//���_���ւ̃|�C���^

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{	//�t�F�[�h�C�����
			m_colorFade.a -= 0.03f;				//��ʂ𓧖��ɂ���
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;			//�������Ă��Ȃ���Ԃɂ���
			}
		}
		else if (m_fade == FADE_OUT)
		{	//�t�F�[�h�A�E�g���
			m_colorFade.a += 0.03f;				//��ʂ�s�����ɂ���
			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;					//�t�F�[�h�C�����

				//���[�h�̐ݒ�
				CManager::SetMode(m_modeNext);
			}
		}

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�|���S���̐F�ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade.a);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade.a);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade.a);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade.a);

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();

		//m_apScene2D->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade.a));
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;							//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();		//�����_�����O�N���X�̎擾

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//Scene2D�̕`��
	//m_apScene2D->Draw();
}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	m_fade = FADE_OUT;
	m_modeNext = modeNext;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

#if 0
//=============================================================================
// �e�N�X�`����ǂݍ���
//=============================================================================
HRESULT CFade::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//�f�o�C�X�̎擾
	CRenderer * pRenderer = CManager::GetRenderer();						//�����_�����O�N���X�̌Ăяo��

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, LODING_TEX, &m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`����j��
//=============================================================================
void CFade::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
#endif