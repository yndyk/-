#include "main.h"
#include "Title.h"

int TpImage[2];
int TpCount;
CHARACTER Tp;

void TitleSysInit()
{
	LoadDivGraph("bmp/潜水艇アニメーション.png", 2, 2, 1, 32, 32, TpImage);
}

void TitleInit()
{
	Tp.pos = { 0 - 96 * 3 , 64 + rand() % 18 + 1 * 32 };
	Tp.size = { 32, 32 };
	Tp.offSet = { Tp.size.x / 2, Tp.size.y / 2 };
	Tp.speed = { 2,2 };
	Tp.flag = false;
	TpCount = 0;
}

void TitleUpdate()
{
	ApprTitle();
	if (Tp.flag == true)
	{
		Tp.pos.x += Tp.speed.x;
		if (Tp.pos.x + Tp.size.x < 0)
		{
			Tp.flag = false;
			Tp.pos = { 0 + 96 ,64 + (rand() % 18 + 1) * 32 };
		}
		
	}

	if (Tp.pos.x > SCREEN_SIZE_X)
	{
		Tp.flag = false;
	}
}

void TitleDraw()
{
	Tp.count++;
	if (Tp.flag) 
	{
		DrawTurnGraph(Tp.pos.x - Tp.offSet.x, Tp.pos.y - Tp.offSet.y,
			TpImage[Tp.count / 50 % 2], true);
	}
}

void ApprTitle()
{
	if (TpCount % 120 == 0)
	{
		if (Tp.flag == false)
		{
			Tp.flag = true;
			Tp.pos = { 0 + 96, 64 + (rand() % 18 + 1) * 32 };
		}
	}
}