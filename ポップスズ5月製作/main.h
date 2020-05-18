//-----------------------------------------------------
// 
// CHARACTER構造体に一度だけ実行する用の変数を追加
// 
//-----------------------------------------------------

#pragma once
#include "Dxlib.h"

enum GAMEMODE
{
	GMODE_INIT,
	GMODE_MAIN,
	GMODE_TITLE,
	GMODE_CLERA,
	GMODE_OVER
};

enum GAMEDIV
{
	DIV_UP,
	DIV_RAHGT,
	DIV_LEFT,
	DIV_DOWN
};
enum TYPE_MODE
{
	TYPE_1,
	TYPE_2,
	TYPE_3,
	TYPE_MAX
};


typedef struct
{
	int x;
	int y;
}XY;


typedef struct
{
	float x;
	float y;
}XY_F;


typedef struct
{
	XY pos;
	int speed;
	int count;
	int point;
	bool flag;
	GAMEDIV div;
	XY size;
	int type;
	int hp;
	bool damageflag;
	bool changeFlag;		// 画像切り替え用変数
	bool onlyOnce;			// 1度だけ実行する用の変数
}CHARACTER;

#define SCREEN_SIZE_X 640
#define SCREEN_SIZE_Y 480
#define TIME_FRAME 60

#define PI 3.141592
extern GAMEMODE gamemode;
extern int leftTime;

//プロトタイプ宣言
void GameInit(void);
bool SystmeInit(void);
void GameTitlr(void);
void GameMain(void);
void GameDraw(void);
void GameClera(void);
void GameOver(void);
bool FadeOutScreen(int fadeStep);
bool FadeinScreen(int fadeStep);

