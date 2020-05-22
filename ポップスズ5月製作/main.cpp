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
//Dxlid.hを使用//独自で準備したヘッダーファイルは””で指定する

//タイトル
int TitieImage;
int bright;	//明るさ
int gameCouner;//メイン画面のカウンター

int fadeCnt;//フェードのカウント
bool fadein;//フェードイン(true)
bool fadeOut;//フェードアウト(false)
//ポーズ
bool pauseFlag;//ポーズのフラグ
int leftTime;//時間
GAMEMODE gamemode;

//WinMain関数の使用
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	if(SystmeInit() == false)
	{
		return -1;
	}

	gamemode = GMODE_INIT;
	
	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
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
	 ScoreSysInit();
	 leftTime = TIME_FRAME * 31;
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
}

void GameTitlr(void)//タイトル画面処理
{
	DrawGraph(10, 200, TitieImage, true);
	//DrawString(SCREEN_SIZE_X/2, SCREEN_SIZE_Y / 2, "フェンビー", 0xffff00, true);
}

void GameMain(void)//ゲーム画面処理
{
	//PAUSEが押されたら
	//pauseFlagを切替得る
	
	if(trgKey[P1_A])
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
	DrawString(0, 0, "GAME_CLERA", 0xffff00, true);
}

void GameOver(void)
{
	DrawString(0, 0, "GAME_OVER", 0xffff00, true);
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
	ScoreDraw();
	DrawFormatString(399, 0, 0xff0000, "%d", leftTime / TIME_FRAME);
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