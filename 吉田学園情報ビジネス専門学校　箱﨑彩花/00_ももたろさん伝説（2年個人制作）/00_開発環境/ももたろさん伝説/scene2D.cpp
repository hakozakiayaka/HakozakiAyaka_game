//=============================================================================
//
// �V�[��2D���� [scene2D.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "main.h"				//���C��
#include "scene.h"				//�V�[��
#include "renderer.h"			//�����_�����O
#include "scene2D.h"			//�V�[��2D
#include "manager.h"			//�}�l�[�W���[
#include "input.h"				//����
#include "pause.h"				//�|�[�Y
#include "life.h"					//���C�t

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
bool g_bDelete = false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2D::CScene2D()
{
}

//=============================================================================
// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�ʒu
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);				//�F
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ړ���
	m_fSize = 0;																//�g��E�k��
	m_nCntAnim = 0;														//�J�E���^�[�A�j���[�V����
	m_nPatternAnim = 0;													//�p�^�[���A�j���[�V����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{	//���������Ȃ�
}

//=============================================================================
// �|���S���̐���
//=============================================================================
CScene2D *CScene2D::Create(void)
{
	CScene2D *pScene2D = NULL;

	//�I�u�W�F�N�g�N���X�̓��I�m��
	if (pScene2D == NULL)
	{
		pScene2D = new CScene2D;
	}
	if(pScene2D != NULL)
	{
		pScene2D->Init();
	}

	return pScene2D;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene2D::Init(void)
{
	VERTEX_2D * pVtx;																				//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;											//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();						//�����_�����O�N���X�̌Ăяo��

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	//�ϐ��̏�����
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSize = 0;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;

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
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�|���S���̐F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene2D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�I�u�W�F�N�g�i�������g�j�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene2D::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;							//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();		//�����_�����O�N���X�̎擾
	CScene::OBJTYPE type = CScene::GetObjType();

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	bool bPause = CPause::GetPause();

	if (type == CScene::OBJTYPE_PAUSE)
	{
		if (bPause == true)
		{
			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
	else
	{
		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=============================================================================
// �|���S���̐ݒ�
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_pos = pos;

	//�|���S���̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, - m_fHeight, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(+m_fWidth,  - m_fHeight, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, + m_fHeight, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(+m_fWidth, + m_fHeight, 0.0f) + m_pos;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

#if 1
//=============================================================================
// �|���S���̃A�j���[�V�����̐ݒ�
//=============================================================================
void CScene2D::SetAnimation(float uv, int nPatternAnim)
{
	VERTEX_2D * pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2((uv * nPatternAnim), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((uv * nPatternAnim) + uv, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((uv * nPatternAnim), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((uv * nPatternAnim) + uv, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
#endif

//=============================================================================
// �T�C�Y�ύX�̏���
//=============================================================================
void CScene2D::SetSize(float fWidth, float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	VERTEX_2D * pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y - fHeight / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y - fHeight / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y + fHeight / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y + fHeight / 2, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �F�̏���
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D * pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_col = col;

	//�|���S���̐F�ݒ�
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �w�i�����������i���j
//=============================================================================
void CScene2D::SetBgMove(int nCntBg, float fScrollSpeed)
{
	VERTEX_2D * pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + (nCntBg * (fScrollSpeed + 1)), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + (nCntBg * (fScrollSpeed + 1)), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (nCntBg * (fScrollSpeed + 1)), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + (nCntBg * (fScrollSpeed + 1)), 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

#if 0
//=============================================================================
// ���C�t����
//=============================================================================
void CScene2D::SetLife(float fWidth, float fHeight)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLife = 0; nCntLife < ANIMAL_LIFE; nCntLife++)
	{
		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f + (60.0f * (ANIMAL_LIFE - nCntLife - 1)), 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f + (60.0f * (ANIMAL_LIFE - nCntLife - 1)), 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f + (60.0f * (ANIMAL_LIFE - nCntLife - 1)), 55.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f + (60.0f * (ANIMAL_LIFE - nCntLife - 1)), 55.0f, 0.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
#endif

//=============================================================================
// �e�N�X�`�������蓖�Ă鏈��
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}