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
#include "input.h"				//����
#include "player.h"				//�v���C���[
#include "bullet.h"				//�e
#include "explosion.h"			//����

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExplosion::CExplosion()
{
	m_nCntAnim = 0;
	m_nPatternAnim = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CExplosion::~CExplosion()
{	//���������Ȃ�
}

//=============================================================================
// �|���S���̐���
//=============================================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion *pExplosion = NULL;

	//�v���C���[�N���X�̓��I�m��
	if (pExplosion == NULL)
	{
		pExplosion = new CExplosion;
	}
	if(pExplosion != NULL)
	{
		pExplosion->Init();													//������
		pExplosion->SetPosition(pos);								//�ʒu�̐ݒ�
		pExplosion->SetAnimation(0.125f, 0);
		pExplosion->BindTexture(m_pTexture);					//�e�N�X�`���̊��蓖��
	}

	return pExplosion;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CExplosion::Init(void)
{
	CScene2D::Init();

	//�����̃T�C�Y��ݒ�
	SetSize(30.0f, 30.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CExplosion::Update(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPosition();		//CScene2D����ʒu���擾
	SetPosition(pos);															//�擾�����ʒu���ACScene2D�ɕԂ�

	m_nCntAnim++;					//�J�E���^�[�����Z

	if ((m_nCntAnim % EXPLOSION_SPEED) == 0)
	{
		m_nPatternAnim++;		//�p�^�[��No���X�V

		//�A�j���[�V�����̐ݒ�
		SetAnimation(0.125f, m_nPatternAnim);							//�t���[�����A�p�^�[��No
	}

	//�A�j���[�V�����̏I������
	if (m_nPatternAnim >= 7)
	{	//�p�^�[��������������
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �e�N�X�`����ǂݍ���
//=============================================================================
HRESULT CExplosion::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//�f�o�C�X�̎擾
	CRenderer * pRenderer = CManager::GetRenderer();						//�����_�����O�N���X�̌Ăяo��

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_NAME, &m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`����j��
//=============================================================================
void CExplosion::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}