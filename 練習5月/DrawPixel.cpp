#include "DxLib.h"

//�萔

#define COLOR_MODE	16

typedef enum {
	GAME_MODE_INIT,
	GAME_MODE_TITLE,
	GAME_MODE_MAIN,
	GAME_MODE_OVER
} GAME_MODE;

//��`
int stageImg;

//�ϐ�
GAME_MODE gameMode;
int gameCounter;
int fadeCnt;
bool fadeIn;
bool fadeOut;
bool pauseFlag;			//�ꎞ��~�̃t���O (true:��~)

//�v���g�^�C�v�錾
bool SystemInit(void);
void GameInit(void);
void GameTitle(void);
void GameTitleDraw(void);
void GameMain(void);
void GameMainDraw(void);
//void GameOver(void);
//void GameOverDraw(void);
void HitCheck(void);
//bool FadeInScreen(int fadeStep);
//bool FadeOutScreen(int fadeStep);

// ========= WinMain�֐�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	// �V�X�e���̏�����
	if (SystemInit() == false)
	{
		return -1;
	}
	gameMode = GAME_MODE_INIT;

	// --------�Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	//��ʏ���

		DrawGraph(0, 0, stageImg, true);

	}

	gameCounter++;
	ScreenFlip();		//����ʂ�\��ʂɏu�ԃR�s�[

	DxLib_End();			// DX���C�u�����̏I������
	return 0;				//���̃v���O�����̏I��
}

//---------------------------------------------
// �V�X�e���̏�����
bool SystemInit(void)
{
	// ----------�V�X�e������
	SetWindowText("1816043_��ؖҎj");
	//�V�X�e������
	SetGraphMode(800, 600, COLOR_MODE);
	ChangeWindowMode(true);							//true:window false:�t���X�N���[��
	if (DxLib_Init() == -1)							//DX���C�u��������������
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);					//�ЂƂ܂��o�b�N�o�b�t�@�ɕ`��

	// ------�O���t�B�b�N�̓o�^�@---------
	stageImg = LoadGraph("image/asaiumi.png");

	// ------�ϐ��������@-----------
	return true;
}

//---------------------------------------------
// �Q�[�����[�v���̏�����
void GameInit(void)
{
	GameTitle();
}

//---------------------------------------------
// �^�C�g������
void GameTitle(void)
{
	GameTitleDraw();
}

//---------------------------------------------
// �^�C�g���̕`��
void GameTitleDraw(void)
{
	DrawString(0, 0, "GameTitle", 0xFFFFFF);

}

//---------------------------------------------
// �v���C������
void GameMain(void)
{
	////Pause �� ON/OFF
	//if (trgKey[PAUSE])
	//{
	//	pauseFlag = !pauseFlag;
	//}

	//if (pauseFlag)
	//{
	//	SetDrawBright(128, 128, 128);
	//}
	//else
	//{
	//	//��ȏ���
	//	HitCheck();
	//}
	//GameMainDraw();
	//if (pauseFlag)
	//{
	//	SetDrawBright(255, 255, 255);
	//	DrawString(360, 292, "P A U S E", 0xFFFFFF);
	//}

}

//---------------------------------------------
// �v���C���̕`��
void GameMainDraw(void)
{
	DrawGraph(0, 0, stageImg, true);



	//DrawFormatString(0, 0, 0xFFFFFF, "GameMain : %d", gameCounter);
}


//---------------------------------------------
// �����蔻��
void HitCheck(void)
{

}

////---------------------------------------------
//// �t�F�[�h�C������
//bool FadeInScreen(int fadeStep)
//{
//	fadeCnt += fadeStep;
//	if (fadeCnt <= 255)
//	{
//		SetDrawBright(fadeCnt, fadeCnt, fadeCnt);
//		return true;
//	}
//	else
//	{
//		SetDrawBright(255, 255, 255);
//		fadeCnt = 0;
//		return false;
//	}
//}
//
////---------------------------------------------
//// �t�F�[�h�A�E�g����
//bool FadeOutScreen(int fadeStep)
//{
//	fadeCnt += fadeStep;
//	if (fadeCnt <= 255)
//	{
//		SetDrawBright(255 - fadeCnt, 255 - fadeCnt, 255 - fadeCnt);
//		return true;
//	}
//	else
//	{
//		SetDrawBright(0, 0, 0);
//		fadeCnt = 0;
//		return false;
//	}
//}
