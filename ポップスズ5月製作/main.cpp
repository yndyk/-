#include "main.h"
#include "keycheck.h"
#include "player.h"
#include "enemy.h"
#include"shot.h"
//Dxlid.hを使用//独自で準備したヘッダーファイルは””で指定する

//タイトル
int TitieImage;
int MapImage;
int MapImage2;
int bright;	//明るさ
int gameCouner;//メイン画面のカウンター

int fadeCnt;//フェードのカウント
bool fadein;//フェードイン(true)
bool fadeOut;//フェードアウト(false)
//ポーズ
bool pauseFlag;//ポーズのフラグ

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
	 TitieImage = LoadGraph("bmp/title.bmp");
	 MapImage = LoadGraph("bmp/map_big.bmp");
	 MapImage2 = LoadGraph("bmp/map_big.bmp");
	 SysInitPlayer();
	 SysInitEnemy();
	 SysInitShot();
	 return true;
}

void GameInit(void)//ゲームループ内の初期化
{
	//変数初期化
	//フェード
	fadeCnt = 0;
	fadeOut = false;
	fadein = false;
	pauseFlag = false;
	InitPlayer();
	InitEnemy();
	InitShot();
}

void GameTitlr(void)//タイトル画面処理
{
	DrawString(SCREEN_SIZE_X/2, SCREEN_SIZE_Y / 2, "フェンビー", 0xffff00, true);
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
		UpdetaPlayer();
		UpdetaEnemy();
		UpdetaShot();
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
	DrawGraph(0, 0, MapImage, true);
	DrawPlayer();
	DrawEnemy();
	DrawShot();
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