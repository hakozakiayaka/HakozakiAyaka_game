//=============================================================================
//
// �V�[������ [scene.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "main.h"				//���C��
#include "scene.h"				//�V�[��
#include "renderer.h"			//�����_�����O
#include "scene2D.h"			//2D�|���S��
#include "bg.h"					//�w�i
#include "pause.h"				//�|�[�Y
#include "manager.h"			//�}�l�[�W���[

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE						(80)			//�|���S���̒��S�_����̃T�C�Y

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
int CScene::m_nNumAll = 0;
bool CScene::m_bPause = false;
CScene * CScene::m_apScene[PRIORITY][MAX_DATA] = {};			//�|���S���̐���

//=============================================================================
// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			//�I�u�W�F�N�g�̐ݒ�
			SetObjType(CScene::OBJTYPE_NONE);						//�I�u�W�F�N�g�̎�ނ̏�����
			m_apScene[nPriority][nCntScene] = this;					//������Ԃ�
			m_nID = nCntScene;													//�������ꂽ�ԍ����Œ肷��
			m_nPriority = nPriority;												//�D�揇�ʂ̔ԍ����Am_nPriority�Ɋi�[����
			m_nNumAll++;															//�|���S���̑��������Z
			break;
		}
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{	//���������Ȃ�
}

//=============================================================================
// �I�u�W�F�N�g�̔j��
//=============================================================================
void CScene::Release(void)
{
	int nID;				//ID��ۑ�����
	int nPriority;		//�D�揇�ʂ̔ԍ���ۑ�

	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		nID = m_nID;
		nPriority = m_nPriority;								//���X����ϐ��Ɋi�[

		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;												//�S�̂̑������猸�炷
	}
}

//=============================================================================
// �S�Ẵ|���S���̔j��
//=============================================================================
void CScene::ReleaseAll(void)
{	//�S�Ă̏������I������
	//�|���S���̔j��
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				delete m_apScene[nCntPriority][nCntScene];
				m_apScene[nCntPriority][nCntScene] = NULL;
			}
		}
	}
}

//=============================================================================
// �t�F�[�h�ȊO�I������
//=============================================================================
void CScene::ReleaseFadeAll(void)
{
	//�|���S���̔j��
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				if (m_apScene[nCntPriority][nCntScene]->m_objType != OBJTYPE_FADE)
				{	//�t�F�[�h�ȊO�c��
					delete m_apScene[nCntPriority][nCntScene];
					m_apScene[nCntPriority][nCntScene] = NULL;
				}
			}
		}
	}
}


//=============================================================================
// �S�Ẵ|���S���̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	CManager::MODE mode = CManager::GetMode();

	//�|���S���̍X�V
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				if (mode == CManager::MODE_GAME)
				{	//���[�h���Q�[����������
					bool bPause = CPause::GetPause();
					if (bPause == false)
					{	//�|�[�Y��Ԃ���Ȃ�
						m_apScene[nCntPriority][nCntScene]->Update();
					}
				}
				else
				{
					m_apScene[nCntPriority][nCntScene]->Update();
				}
			}
		}
	}
}

//=============================================================================
// �S�Ẵ|���S���̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	//�|���S���̕`��
	for (int nCntPriotity = 0; nCntPriotity < PRIORITY; nCntPriotity++)
	{
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			if (m_apScene[nCntPriotity][nCntScene] != NULL)
			{
				m_apScene[nCntPriotity][nCntScene]->Draw();
			}
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�̐ݒ�
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//=============================================================================
// �I�u�W�F�N�g�̎�ނ��擾���鏈��
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//=============================================================================
// �V�[���̎擾
//=============================================================================
CScene * CScene::GetScene(int nPriority, int nIdx)
{
	return m_apScene[nPriority][nIdx];
}

//=============================================================================
// �|�[�Y�̐ݒ�
//=============================================================================
void CScene::SetPause(bool bPause)
{
	m_bPause = bPause;
}