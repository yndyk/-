#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include"player.h"
#include"unti.h"

int UntiImage;
CHARACTER unti;
int UntiCount;

//ロード
void SysinitUnti()
{
	UntiImage = LoadGraph("bmp/ウンコ.png");
}

//初期化
void initUnti() 
{
	unti.pos = { 64 + rand() % 18 - 1 * 32,0 };
	unti.size = { UNTI_SIZE_X,UNTI_SIZE_Y };
	unti.flag = false; //表示判定
	unti.speed = 6; 
	unti.count = 0;
	UntiCount = 0;
}

//更新
void UpdetaUnti()
{
	srand(time(NULL));

	unti.count++;
	if (unti.count % 120 == 0)
	{
		unti.flag == true;
	}
	if(unti.flag == true)
	{
		unti.pos.y += unti.speed;
	}
	else
	{
		unti.flag = true;
	}

	if (unti.pos.y + 32 < 0)
	{
		unti.flag = false;
		unti.pos = { 64 + (rand() % 18 - 1) * 32,  + 32 };
	}

		if ((player.pos.x < unti.pos.x + unti.size.x
			&&unti.pos.x < player.pos.x + player.size.x
			&&player.pos.y < unti.pos.y + unti.size.y
			&&unti.pos.y < player.pos.y + player.size.y))
		{
			player.flag = false;
			unti.flag = true;
			player.hp -= 1;
		}

		/*if (unti.flag == true)
		{
			unti.pos.x = GetRand(320);
			unti.flag = false;
		}*/
	
}

//描画
void DrawUnti()
{
	if (unti.flag == true)
	{
		DrawGraph(unti.pos.x, unti.pos.y, UntiImage, true);
		/*DrawBox(unti.pos.x, unti.pos.y,
			unti.size.x, unti.size.y, 0xff0000, true);*/
	}
	
}