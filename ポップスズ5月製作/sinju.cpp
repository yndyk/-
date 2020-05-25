#include "main.h"
#include "kaigara.h"
#include "player.h"
#include "shot.h"
#include "hitCheck.h"
#include "score.h"

CHARACTER pearl;
int pearlImage;
int pearlCnt;		// 貝が出た回数


void SysInitPearl()
{
	pearlImage = LoadGraph("bmp/sinju.png");
}

void InitPearl()
{
	pearl.pos = { 0, 0 };
	pearl.flag = false;
	//pearl.hp = 10;
	pearl.size = { 32, 32 };
	pearl.speed = { 1, 1 };
	pearl.offSet = { pearl.size.x / 2, pearl.size.y / 2 };
	pearl.count = 0;
	pearl.onlyOnce = false;
}

void UpdataPearl(CHARACTER p, CHARACTER kai)
{
	if (kai.changeFlag)
	{
		if (!pearl.onlyOnce)
		{
			pearl.flag = kai.changeFlag;
			pearl.pos = kai.pos;
			pearl.onlyOnce = true;
		}
	}

	if (pearl.flag)
	{
		if (HitCheck(pearl, p))
		{
			pearl.flag = false;
			//真珠を取得した際の効果
			SetScore(SCORE, 2000);			//とりあえず真珠をゲットしたら2000点加算

			//光らせる処理

		}
		pearl.pos.y += pearl.speed.y;
	}
}

void DrawPearl()
{
	if (pearl.flag)
	{
		DrawGraph(pearl.pos.x - pearl.offSet.x, pearl.pos.y - pearl.offSet.y, pearlImage, true);


		DrawBox(pearl.pos.x - pearl.offSet.x,
			pearl.pos.y - pearl.offSet.y,
			pearl.pos.x + pearl.offSet.x,
			pearl.pos.y + pearl.offSet.y,
			0x000000, false);
	}

	//DrawFormatString(50, 50, 0xff0000, "cnt:%d", pearlCnt);
	//DrawFormatString(50, 70, 0xff0000, "x:%d", pearl.pos.x);
	//DrawFormatString(50, 90, 0xff0000, "y:%d", pearl.pos.y);
	//DrawFormatString(50, 110, 0xff0000, "f:%d", pearl.flag);
	//DrawFormatString(50, 130, 0xff0000, "s:%d", pearl.speed.y);
}
