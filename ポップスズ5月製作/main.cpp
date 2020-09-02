//--------------------------------------------------
//
// 
// 
//
//--------------------------------------------------

#include "main.h"
#include "keycheck.h"
#include "player.h"
#include "enemy.h"
#include "shot.h"
#include "unti.h"
#include "awa.h"
#include "unti.h"
#include "map.h"
#include "ikayaki.h"
#include <time.h>
#include"ikatenn.h"
#include"surume.h"
#include"box.h"
#include"Benemy.h"
#include "score.h"
#include "file.h"
#include "kaigara.h"
#include "sinju.h"
#include "same.h"
#include"Title.h"
//Dxlid.h���g�p//�Ǝ��ŏ��������w�b�_�[�t�@�C���́h�h�Ŏw�肷��

//�^�C�g��
int TitieImage;
int GImage[2];
int OperationImage;
int OperationImage2;
int huriganaImage;
int bright;	//���邳
int gameCouner;//���C����ʂ̃J�E���^�[

int fadeCnt;//�t�F�[�h�̃J�E���g
bool fadein;//�t�F�[�h�C��(true)
bool fadeOut;//�t�F�[�h�A�E�g(false)
//�|�[�Y
bool pauseFlag;//�|�[�Y�̃t���O
int leftTime;//����
GAMEMODE gamemode;

//�T�E���h
int Sound;
int OverSound;
int ClearSound;
//WinMain�֐��̎g�p
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	if(SystmeInit() == false)
	{
		return -1;
	}

	gamemode = GMODE_INIT;
	
	//�Q�[�����[�v
	while (ProcessMessage() == 0 && newKey[QUIT] == 0)
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
					gamemode = GMODE_OPERATION;
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
		case GMODE_OPERATION:
			if (fadein)//�t�F�[�h�C��
			{
				if (!FadeinScreen(5))
				{
					fadein = false;
				}
			}
			else
			if (fadeOut)//�t�F�[�h�A�E�g
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
			GameOperation();
			PlaySoundMem(Sound, DX_PLAYTYPE_LOOP);
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
					StopSoundMem(OverSound);
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
	 TitieImage = LoadGraph("bmp/�^�C�g�����S0512.png");
	 LoadDivGraph("bmp/game_state.png", 2, 1, 2, 306, 34, GImage, true);
	OperationImage = LoadGraph("bmp/�������1.png");
	OperationImage2 = LoadGraph("bmp/�������2.png");
	huriganaImage = LoadGraph("bmp/�t���K�i.png");
	 StageSysinit();
	 SysInitPlayer();
	 SysInitEnemy();
	 SysInitShot();
	 SysInitBubble();
	 SysinitUnti();
	 SysInitBubble();
	 SysInitIkayaki();
	 SysInitIkatenn();
	 SysInitSurume();
	 SysInitBox();
	 SysInitBenemy();
	 SysInitShell();
	 SysInitPearl();
	 SysInitSame();
	 ScoreSysInit();
	 TitleSysInit();
	 leftTime = TIME_FRAME * 31;
	 //��
 	 Sound = LoadSoundMem("���f��/�A��.mp3");
	 OverSound = LoadSoundMem("���f��/�I�[�o�[.mp3");
	 ClearSound = LoadSoundMem("���f��/�N���A.mp3");
	 return true;
}

void GameInit(void)//�Q�[�����[�v���̏�����
{
	srand(time(NULL));

	//�ϐ�������
	//�t�F�[�h
	fadeCnt = 0;
	fadeOut = false;
	fadein = false;
	pauseFlag = false;
	InitPlayer();
	InitEnemy();
	InitShot();
	InitBubble();
	initUnti();
	InitBubble();
	InitIkayaki();
	InitIkatenn();
	InitSurume();
	InitBox();
	InitBenemy();
	InitShell();
	InitPearl();
	ScoreInit();
	InitSame();
	TitleInit();
}

void GameTitlr(void)//�^�C�g����ʏ���
{
	TitleUpdate();
	TitleDraw();
	DrawGraph(10, 200, TitieImage, true);
	DrawString(280, 400, "START_SPACE", 0x00ffff, true);
	
}

void GameMain(void)//�Q�[����ʏ���
{
	//PAUSE�������ꂽ��
	//pauseFlag��ؑ֓���
	
	if(trgKey[PAUSE])
	{
		pauseFlag = !pauseFlag;//!������Ɣے�ɂȂ�
	}
	
	//�|�[�Y���łȂ��Ƃ�
	if(!pauseFlag)
	{
		//�|�[�Y���ɂ��Ȃ�����
		srand(time(NULL));

		StageUpdate();//�X�e�[�W�؂�ւ��̏���
		UpdetaPlayer();
		UpdetaEnemy();
		UpdetaShot();
		UpdetaUnti();//�����ł��񂿂̏���������
		UpdetaBuble();
		UpdetaBenemy();
		UpdetaSame();
		leftTime--;
		
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
	SetScore(HIGH_SCORE, GetScore(SCORE));
	HighScoreDraw();
	DrawGraph((SCREEN_SIZE_X - 306) / 2, SCREEN_SIZE_Y / 10 * 4, GImage[0], true);
	//DrawString(0, 0, "GAME_CLERA", 0xffff00, true);
}

void GameOver(void)
{
	SetScore(HIGH_SCORE, GetScore(SCORE));
	HighScoreDraw();
	DrawGraph((SCREEN_SIZE_X - 282) / 2, SCREEN_SIZE_Y / 10 * 4, GImage[1], true);
	//DrawString(0, 0, "GAME_OVER", 0xffff00, true);
}

void GameDraw(void)//�`��ݒ�
{
	StageDraw();
	DrawPlayer();
	DrawEnemy();
	DrawShot();
	DrawBuble();
	DrawUnti();
	DrawBox();
	DrawBenemy();
	DrawShell();
	ScoreDraw();
	DrawSame();
	//DrawFormatString(399, 0, 0xff0000, "%d", leftTime / TIME_FRAME);
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

void GameOperation(void)
{
	DrawGraph(200, 180, OperationImage, true);
	DrawGraph(200, 270, OperationImage2, true);
	DrawString(280, 400, "START_SPACE", 0x00ffff, true);
	DrawGraph(375, 160, huriganaImage, true);
}

