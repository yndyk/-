#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"main.h"
#include"player.h"
#include"same.h"
#include"hitCheck.h"

CHARACTER same;
int SameCount;

//ロード
void SysInitSame()
{  
	
}

//初期化
void InitSame()
{
	same.pos = { 0 - 32 * 3 , 64 + rand() % 18 + 1 * 32 };
	same.size = { 96,64 };
	same.speed = {4,4};
	same.offSet = { same.size.x / 2,same.size.y / 2 };
	same.flag = false;
	SameCount = 0;
}

//更新
void UpdetaSame()
{
	srand(time(NULL));
	SameCount++;
	ApprSame();
	if (same.flag == true) 
	{
		same.pos.x += same.speed.x;
		if (same.pos.x + same.size.x < 0)
		{
			same.flag = false;
			same.pos = { 0 + 32 ,64 + (rand() % 18 + 1) * 32 };
		}
	}

	if(same.pos.x > SCREEN_SIZE_X)
	{
		same.flag = false;
	}
	
	if (!player.damageflag && same.flag)
	{
		if (HitCheck(player, same))
		{
			player.damageflag = true;
			player.flag = false;

		}
	}
	else
	{
		player.flag = true;
	}
	/*if(same.pos.x < 0)
	{
		same.speed.x = -same.speed.x;
	}

	if (same.pos.x >= 590)
	{
		same.speed.x = -same.speed.x;
	}*/
}

//描画
void DrawSame()
{
	if (same.flag == true)
	{
		DrawBox(same.pos.x - same.offSet.x, same.pos.y - same.offSet.y,
			same.pos.x + same.offSet.x, same.pos.y + same.offSet.y,
			0xff0000, true);
	}
	DrawFormatString(0, 250, 0xff0000, "%d",SameCount, true);
}

void ApprSame()
{
	if (SameCount % 120 == 0) 
	{
		if (same.flag == false)
		{
			same.flag = true;
			same.pos = { 0 + 32, 64 + (rand() % 18 + 1) * 32 };
		}
	}
}