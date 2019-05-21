//=============================================================================
//
// �V�[��2D���� [scene2D.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _SCENE2D_H_		//��d�C���N���[�h�h�~
#define _SCENE2D_H_

#include	"main.h"				//���C��

//*****************************************************************************
// �I�u�W�F�N�g2D�N���X
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D();																										//�f�t�H���g�R���X�g���N�^
	CScene2D(int nPriority);																						//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
	~CScene2D();																										//�f�X�g���N�^
	HRESULT Init(void);																							//����������
	void Uninit(void);																									//�I������
	void Update(void);																								//�X�V����
	void Draw(void);																									//�`�揈��
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);										//�e�N�X�`�������蓖�Ă�ׂ̏���

	//�e�����̐ݒ�
	void SetPosition(D3DXVECTOR3 pos);																//�|���S���̐ݒ�
	void SetAnimation(float uv, int nPatternAnim);													//�A�j���[�V�����̐ݒ�
	void SetBgMove(int nCntBg, float fScrollSpeed);												//�w�i�𓮂�������
	void SetSize(float fWidth, float fHeight);															//�T�C�Y��ύX���鏈��
	void SetColor(D3DXCOLOR col);																		//�F�̐ݒ�
	void SetLife(float fWidth, float fHeight);																//���C�t����

	//�e�ϐ��̎擾
	D3DXVECTOR3 GetPosition(void) { return m_pos; }											//�ʒu���擾
	int GetPatternAnim(void) { return m_nPatternAnim; }										//�p�^�[���A�j���[�V�����̎擾

	//�ÓI�����o�֐�
	static CScene2D *Create();																				//�I�u�W�F�N�g�̐���

	D3DXVECTOR3								m_move;														//�|���S���̈ړ���

private:
	D3DXVECTOR3								m_pos;															// �|���S���̈ʒu
	D3DXCOLOR									m_col;															//�F
	float													m_fHeight;													//����
	float													m_fWidth;													//��
	int													m_nCntAnim;												//�A�j���[�V�����̃J�E���^�[
	int													m_nPatternAnim;											//�A�j���[�V�����p�^�[����

protected:
	LPDIRECT3DTEXTURE9					m_pTexture;													// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;													// ���_�o�b�t�@�ւ̃|�C���^

	float													m_fSize;														//�g��k���Ŏg��
};
#endif