#include "DxLib.h"

//定数

#define COLOR_MODE	16

typedef enum {
	GAME_MODE_INIT,
	GAME_MODE_TITLE,
	GAME_MODE_MAIN,
	GAME_MODE_OVER
} GAME_MODE;

//定義
int stageImg;

//変数
GAME_MODE gameMode;
int gameCounter;
int fadeCnt;
bool fadeIn;
bool fadeOut;
bool pauseFlag;			//一時停止のフラグ (true:停止)

//プロトタイプ宣言
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

// ========= WinMain関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	// システムの初期化
	if (SystemInit() == false)
	{
		return -1;
	}
	gameMode = GAME_MODE_INIT;

	// --------ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	//画面消去

		DrawGraph(0, 0, stageImg, true);

	}

	gameCounter++;
	ScreenFlip();		//裏画面を表画面に瞬間コピー

	DxLib_End();			// DXライブラリの終了処理
	return 0;				//このプログラムの終了
}

//---------------------------------------------
// システムの初期化
bool SystemInit(void)
{
	// ----------システム処理
	SetWindowText("1816043_大木猛史");
	//システム処理
	SetGraphMode(800, 600, COLOR_MODE);
	ChangeWindowMode(true);							//true:window false:フルスクリーン
	if (DxLib_Init() == -1)							//DXライブラリ初期化処理
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);					//ひとまずバックバッファに描画

	// ------グラフィックの登録　---------
	stageImg = LoadGraph("image/asaiumi.png");

	// ------変数初期化　-----------
	return true;
}

//---------------------------------------------
// ゲームループ内の初期化
void GameInit(void)
{
	GameTitle();
}

//---------------------------------------------
// タイトル処理
void GameTitle(void)
{
	GameTitleDraw();
}

//---------------------------------------------
// タイトルの描画
void GameTitleDraw(void)
{
	DrawString(0, 0, "GameTitle", 0xFFFFFF);

}

//---------------------------------------------
// プレイ中処理
void GameMain(void)
{
	////Pause の ON/OFF
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
	//	//主な処理
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
// プレイ中の描画
void GameMainDraw(void)
{
	DrawGraph(0, 0, stageImg, true);



	//DrawFormatString(0, 0, 0xFFFFFF, "GameMain : %d", gameCounter);
}


//---------------------------------------------
// 当たり判定
void HitCheck(void)
{

}

////---------------------------------------------
//// フェードイン処理
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
//// フェードアウト処理
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
