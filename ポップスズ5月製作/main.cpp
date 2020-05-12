#include "main.h"
#include "keycheck.h"
#include "player.h"
#include "enemy.h"
#include"shot.h"
//Dxlid.h���g�p//�Ǝ��ŏ��������w�b�_�[�t�@�C���́h�h�Ŏw�肷��

//�^�C�g��
int TitieImage;
int MapImage;
int MapImage2;
int bright;	//���邳
int gameCouner;//���C����ʂ̃J�E���^�[

int fadeCnt;//�t�F�[�h�̃J�E���g
bool fadein;//�t�F�[�h�C��(true)
bool fadeOut;//�t�F�[�h�A�E�g(false)
//�|�[�Y
bool pauseFlag;//�|�[�Y�̃t���O

GAMEMODE gamemode;

//WinMain�֐��̎g�p
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	if(SystmeInit() == false)
	{
		return -1;
	}

	gamemode = GMODE_INIT;
	
	//�Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();

		KeyCheck();
	
		//���C������
		switch (gamemode)
		{
		case GMODE_INIT:
			GameInit();
			gamemode = GMODE_TITLE;
			break;
		case GMODE_TITLE: 
			if (fadein)//�t�F�[�h�C��
			{
				if (!FadeinScreen(5))
				{
					fadein = false;
				}
			}
			else
			if(fadeOut)//�t�F�[�h�A�E�g
			{
				if (!FadeOutScreen(5)) 
				{
					gamemode = GMODE_MAIN;
					fadeOut = false;
					fadein = true;
				}
			}
			else
			{
				if (trgKey[START])
					fadeOut = true;
			}
			GameTitlr();
			break;
		case GMODE_MAIN:
			if (fadein)//�t�F�[�h�C��
			{
				if (!FadeinScreen(5))
				{
					fadein = false;
				}
			}
			GameMain();
			break;
		case GMODE_CLERA:
			if (trgKey[START])
			{
				fadeOut = true;
			}
			if (fadeOut)//�t�F�[�h�A�E�g
			{
				if (!FadeOutScreen(5))
				{
					gamemode = GMODE_INIT;
					fadeOut = false;
					fadein = true;
				}
			}
			GameClera();
			break;
		case GMODE_OVER:
			if (trgKey[START])
			{
				fadeOut = true;
			}
			if (fadeOut)//�t�F�[�h�A�E�g
			{
				if (!FadeOutScreen(5))
				{
					gamemode = GMODE_INIT;
					fadeOut = false;
					fadein = true;
				}
			}
			GameOver();
			break;
		default:
			gamemode = GMODE_INIT;
			break;
		}
		gameCouner++;
		ScreenFlip();		//���\�ʂ�\�\�ʂɏu�ԃR�s�[
	}



	DxLib_End();	//DxLib�̏I��
	return 0;		//���̃v���O�����̏I��
}

bool SystmeInit(void)//�V�X�e��������
{
	//�V�X�e������
	SetWindowText("�t�F���r�[");
	//�V�X�e������
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);	//640*480�h�b�g�U�T�T�R�U�F���[�h�ɐݒ�
	ChangeWindowMode(true);	//true:window flase:�t���X�N���[��
	if (DxLib_Init() == -1)return -1;	//�ЂƂ܂��o�b�N�o�b�t�@�ɕ`��
	SetDrawScreen(DX_SCREEN_BACK);

//�O���t�B�b�N
	 TitieImage = LoadGraph("bmp/title.bmp");
	 MapImage = LoadGraph("bmp/map_big.bmp");
	 MapImage2 = LoadGraph("bmp/map_big.bmp");
	 SysInitPlayer();
	 SysInitEnemy();
	 SysInitShot();
	 return true;
}

void GameInit(void)//�Q�[�����[�v���̏�����
{
	//�ϐ�������
	//�t�F�[�h
	fadeCnt = 0;
	fadeOut = false;
	fadein = false;
	pauseFlag = false;
	InitPlayer();
	InitEnemy();
	InitShot();
}

void GameTitlr(void)//�^�C�g����ʏ���
{
	DrawString(SCREEN_SIZE_X/2, SCREEN_SIZE_Y / 2, "�t�F���r�[", 0xffff00, true);
}

void GameMain(void)//�Q�[����ʏ���
{
	//PAUSE�������ꂽ��
	//pauseFlag��ؑ֓���
	if(trgKey[P1_A])
	{
		pauseFlag = !pauseFlag;//!������Ɣے�ɂȂ�
	}
	
	//�|�[�Y���łȂ��Ƃ�
	if(!pauseFlag)
	{
		//�|�[�Y���ɂ��Ȃ�����
		UpdetaPlayer();
		UpdetaEnemy();
		UpdetaShot();
	}

	//�|�[�Y����������F����
	if (pauseFlag )
	{
		SetDrawBright(128, 128, 128);
	}
	GameDraw();

	if(pauseFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawString(SCREEN_SIZE_X/2, SCREEN_SIZE_Y / 2, "PAUSE", 0xffff00, true);
	}
}



void GameClera(void)//�N���A��ʏ���
{
	DrawString(0, 0, "GAME_CLERA", 0xffff00, true);
	
}

void GameOver(void)
{
	DrawString(0, 0, "GAME_OVER", 0xffff00, true);
}

void GameDraw(void)//�`��ݒ�
{
	DrawGraph(0, 0, MapImage, true);
	DrawPlayer();
	DrawEnemy();
	DrawShot();
}

bool FadeinScreen(int fadeStep)//�t�F�[�h�C������
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255)//�J�E���^�[��255�ȉ���������
	{
		//fadeOut = 0;
		SetDrawBright(fadeCnt, fadeCnt, fadeCnt);//�F�̒l
		return true;//�t�F�[�h��
	}
	else
	{
		SetDrawBright(255, 255, 255);
		fadeCnt = 0;
		return  false;//�t�F�[�h�I��
	}
}

bool FadeOutScreen(int fadeStep)//�t�F�[�h�A�E�g����
{
	fadeCnt += fadeStep;
	if(fadeCnt <= 255)
	{
		SetDrawBright(255 - fadeCnt, 255 - fadeCnt, 255 - fadeCnt);
		return true;
	}
	else 
	{
		SetDrawBright(0, 0, 0);
		fadeCnt = 0;
		return false;
	}
}