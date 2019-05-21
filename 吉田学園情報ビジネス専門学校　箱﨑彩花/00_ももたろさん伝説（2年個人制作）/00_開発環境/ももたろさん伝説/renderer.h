//=============================================================================
//
// �����_�����O���� [renderer.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _RENDERER_H_		//��d�C���N���[�h�h�~
#define _RENDERER_H_

#include	"main.h"				//���C��

//*****************************************************************************
// �����_�����O�N���X
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);													//����������
	void Uninit(void);																								//�I������
	void Update(void);																							//�X�V����
	void Draw(void);																								//�`�揈��
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }				//�f�o�C�X�̎擾

private:
	//�f�o�b�N�̂ݗL��
#ifdef _DEBUG
	void DrawFPS(void);																						//FPS�̕`��
#endif

	//�����o�ϐ�
	LPDIRECT3D9									m_pD3D;												// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9					m_pD3DDevice;									// Device�I�u�W�F�N�g(�`��ɕK�v)

	//�f�o�b�N�̂ݗL��
#ifdef _DEBUG
	LPD3DXFONT									m_pFont;												// �t�H���g�ւ̃|�C���^
#endif
};

#endif