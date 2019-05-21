//=============================================================================
//
// �����̏��� [explosion.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "main.h"				//���C��
#include "scene.h"				//�V�[��
#include "renderer.h"			//�����_�����O
#include "scene2D.h"			//�V�[��2D
#include "manager.h"			//�}�l�[�W���[
#include "player.h"				//�v���C���[
#include "bullet.h"				//�e
#include "explosion.h"			//����
#include "effect.h"				//�G�t�F�N�g

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define EFFECT_LIFE					(20)				//�G�t�F�N�g�̕\�����Ԃ̐ݒ�
#define EFFECT_SIZE					(20.0f)			//�G�t�F�N�g�̃T�C�Y
#define EFFECT_PRIORITY		(3)				//�G�t�F�N�g�̗D�揇��

//�e�N�X�`����
#define EFFECT_NAME				"data/TEXTURE/effect000.jpg"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect::CEffect(int nPriority) : CScene2D(nPriority)
{
	m_nSize = EFFECT_SIZE;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{	//���������Ȃ�
}

//=============================================================================
// �|���S���̐���
//=============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	CEffect *pEffect = NULL;

	//�v���C���[�N���X�̓��I�m��
	if (pEffect == NULL)
	{
		pEffect = new CEffect(EFFECT_PRIORITY);
	}
	if(pEffect != NULL)
	{
		pEffect->Init();
		pEffect->SetPosition(pos);
		pEffect->SetColor(D3DXCOLOR(col.r, col.g, col.b, col.a));

		//�e�N�X�`���̊��蓖��
		pEffect->BindTexture(m_pTexture);
	}

	return pEffect;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEffect::Init(void)
{
	CScene2D::Init();

	//������
	CScene2D::SetObjType(CScene2D::OBJTYPE_EFFECT);
	m_nLife = EFFECT_LIFE;								//�G�t�F�N�g�̕\������
	CScene2D::SetSize(m_nSize, m_nSize);			//�G�t�F�N�g�̃T�C�Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEffect::Update(void)
{
	m_nLife--;
	CScene2D::SetSize(m_nSize + m_nLife, m_nSize + m_nLife);

	if (m_nLife == 0)
	{	//�\�����Ԃ�0�ɂȂ���
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;							//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();		//�����_�����O�N���X�̎擾

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// �e�N�X�`����ǂݍ���
//=============================================================================
HRESULT CEffect::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//�f�o�C�X�̎擾
	CRenderer * pRenderer = CManager::GetRenderer();						//�����_�����O�N���X�̌Ăяo��

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, EFFECT_NAME, &m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`����j��
//=============================================================================
void CEffect::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}