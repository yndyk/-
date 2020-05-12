#pragma once
#include "DxLib.h"
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
}CHARACTER;

extern GAMEMODE gamemode;

#define SCREEN_SIZE_X 640
#define SCREEN_SIZE_Y 480

#define PI 3.141592

//プロトタイプ宣言
void GameInit(void);
bool SystmeInit(void);
void GameTitlr(void);
void GameMain(void);
void GameMain2(void);
void GameDraw(void);
void GameClera(void);
void GameOver(void);
bool FadeOutScreen(int fadeStep);
bool FadeinScreen(int fadeStep);

