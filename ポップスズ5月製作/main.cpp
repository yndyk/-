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
//Dxlid.hを使用//独自で準備したヘッダーファイルは””で指定する

//タイトル
int TitieImage;
int GImage[2];
int OperationImage;
int OperationImage2;
int huriganaImage;
int bright;	//明るさ
int gameCouner;//メイン画面のカウンター

int fadeCnt;//フェードのカウント
bool fadein;//フェードイン(true)
bool fadeOut;//フェードアウト(false)
//ポーズ
bool pauseFlag;//ポーズのフラグ
int leftTime;//時間
GAMEMODE gamemode;

//サウンド
int Sound;
int OverSound;
int ClearSound;
//WinMain関数の使用
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	if(SystmeInit() == false)
	{
		return -1;
	}

	gamemode = GMODE_INIT;
	
	//ゲームループ
	while (ProcessMessage() == 0 && newKey[QUIT] == 0)
	{
		ClsDrawScreen();

		KeyCheck();
	
		//メイン処理
 		switch (gamemode)
		{
		case GMODE_INIT:
			GameInit();
			gamemode = GMODE_TITLE;
			break;
		case GMODE_TITLE: 
			if (fadein)//フェードイン
			{
				if (!FadeinScreen(5))
				{
					fadein = false;
				}
			}
			else
			if(fadeOut)//フェードアウト
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
			if (fadein)//フェードイン
			{
				if (!FadeinScreen(5))
				{
					fadein = false;
				}
			}
			else
			if (fadeOut)//フェードアウト
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
			if (fadein)//フェードイン
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
			if (fadeOut)//フェードアウト
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
			if (fadeOut)//フェードアウト
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
		ScreenFlip();		//裏表面を表表面に瞬間コピー
	}

	DxLib_End();	//DxLibの終了
	return 0;		//このプログラムの終了
}

bool SystmeInit(void)//システム初期化
{
	//システム処理
	SetWindowText("フェンビー");
	//システム処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);	//640*480ドット６５５３６色モードに設定
	ChangeWindowMode(true);	//true:window flase:フルスクリーン
	if (DxLib_Init() == -1)return -1;	//ひとまずバックバッファに描画
	SetDrawScreen(DX_SCREEN_BACK);

//グラフィック
	 TitieImage = LoadGraph("bmp/タイトルロゴ0512.png");
	 LoadDivGraph("bmp/game_state.png", 2, 1, 2, 306, 34, GImage, true);
	OperationImage = LoadGraph("bmp/操作説明1.png");
	OperationImage2 = LoadGraph("bmp/操作説明2.png");
	huriganaImage = LoadGraph("bmp/フリガナ.png");
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
	 //音
 	 Sound = LoadSoundMem("音素材/アワ.mp3");
	 OverSound = LoadSoundMem("音素材/オーバー.mp3");
	 ClearSound = LoadSoundMem("音素材/クリア.mp3");
	 return true;
}

void GameInit(void)//ゲームループ内の初期化
{
	srand(time(NULL));

	//変数初期化
	//フェード
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

void GameTitlr(void)//タイトル画面処理
{
	TitleUpdate();
	TitleDraw();
	DrawGraph(10, 200, TitieImage, true);
	DrawString(280, 400, "START_SPACE", 0x00ffff, true);
	
}

void GameMain(void)//ゲーム画面処理
{
	//PAUSEが押されたら
	//pauseFlagを切替得る
	
	if(trgKey[PAUSE])
	{
		pauseFlag = !pauseFlag;//!をつけると否定になる
	}
	
	//ポーズ中でないとき
	if(!pauseFlag)
	{
		//ポーズ中にしない処理
		srand(time(NULL));

		StageUpdate();//ステージ切り替えの処理
		UpdetaPlayer();
		UpdetaEnemy();
		UpdetaShot();
		UpdetaUnti();//ここでうんちの処理をする
		UpdetaBuble();
		UpdetaBenemy();
		UpdetaSame();
		leftTime--;
		
	}

	//ポーズ中だったら色半分
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

void GameClera(void)//クリア画面処理
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

void GameDraw(void)//描画設定
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

bool FadeinScreen(int fadeStep)//フェードイン処理
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255)//カウンターが255以下だったら
	{
		//fadeOut = 0;
		SetDrawBright(fadeCnt, fadeCnt, fadeCnt);//色の値
		return true;//フェード中
	}
	else
	{
		SetDrawBright(255, 255, 255);
		fadeCnt = 0;
		return  false;//フェード終了
	}
}

bool FadeOutScreen(int fadeStep)//フェードアウト処理
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

