//=============================================================================
//
// �Q�[���̏��� [game.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _GAME_H_		//��d�C���N���[�h�h�~
#define _GAME_H_

#include	"main.h"		//���C��
#include "animal.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPlayer;				//�v���C���[
class CAnimal;				//���Ƃ�
class CEnemy;				//�G�l�~�[
class CNumber;			//�i���o�[
class CPause;				//�|�[�Y

//*****************************************************************************
// �Q�[���N���X
//*****************************************************************************
class CGame
{
public:
	CGame();																		//�R���X�g���N�^
	~CGame();																	//�f�X�g���N�^
	HRESULT Init(void);													//����������
	void Uninit(void);															//�I������
	void Update(void);														//�X�V����
	void Draw(void);															//�`�揈��

	//�ÓI�����o�֐�
	static CPlayer * GetPlayer(void) { return m_pPlayer; }													//�v���C���[�N���X�ɒl��Ԃ�
	static CAnimal * GetAnimal(void) { return m_pAnimal; }												//���Ƃ��N���X�ɒl��Ԃ�
	static CEnemy * GetEnemy(void) { return m_pEnemy; }												//�G�l�~�[�N���X�ɒl��Ԃ�
	static CNumber * GetNumber(void) { return m_pNumber; }											//�X�R�A�N���X�ɒl��Ԃ�
	static CPause * GetPause(void) { return m_pPause; }													//�|�[�Y�N���X�ɒl��Ԃ�

private:
	//�ÓI�����o�ϐ�
	static CPlayer * m_pPlayer;																							//�v���C���[�N���X�̎擾
	static CAnimal * m_pAnimal;																							//���Ƃ��N���X�̎擾
	static CEnemy * m_pEnemy;																							//�G�l�~�[�N���X�̎擾
	static CNumber * m_pNumber;																						//�X�R�A�N���X�̎擾
	static CPause * m_pPause;																								//�|�[�Y�N���X�̎擾
	static CScore * m_pScore;																								//�X�R�A�N���X�̎擾
	static int m_nCntTime;																									//

};
#endif