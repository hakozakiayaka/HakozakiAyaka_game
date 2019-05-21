//=============================================================================
//
// �i���o�[���� [number.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _NUMBER_H_		//��d�C���N���[�h�h�~
#define _NUMBER_H_

#include	"main.h"			//���C��

//*****************************************************************************
// �i���o�[�N���X
//*****************************************************************************
class CNumber
{
public:
	CNumber();																							//�R���X�g���N�^
	~CNumber();																						//�f�X�g���N�^
	HRESULT Init(void);																			//����������
	void Uninit(void);																					//�I������
	void Update(void);																				//�X�V����
	void Draw(void);																					//�`�揈��
	void SetNumber(int nNumber);															//�����̌����̐ݒ�
	void SetPosition(D3DXVECTOR3 pos, int nCnt);								//�ʒu�̐ݒ�
	void SetColor(D3DXCOLOR col);														//�F�̐ݒ�

	//�ÓI�����o�֐�
	static CNumber * Create(void);															//�����̐���
	static HRESULT Load(void);																//�e�N�X�`���̊��蓖�ď���
	static void Unload(void);																		//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9		m_pTexture;									// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;									// ���_�o�b�t�@�ւ̃|�C���^

	int m_nTimeData[3];
	int m_nTime;
	int m_col;
};

#endif