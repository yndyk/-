#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include"player.h"
#include"unti.h"

int UntiImage;
CHARACTER unti[UNTI_MAX];
int UnitCount;

//ロード
void SysinitUnti()
{
	UntiImage = LoadGraph("bmp/ウンコ.png");
}

//初期化
void initUnti()
{
	for (int i = 0; i < UNTI_MAX;++i) 
	{
		unti[i].pos = { GetRand(500), 0 };
		unti[i].size = { UNTI_SIZE_X,UNTI_SIZE_Y };
		unti[i].flag = false;
		unti[i].speed = 6;
		unti[i].count = false;
		UnitCount = false;
	}
}

//更新
void UpdetaUnti()
{
	for (int i = 0; i < UNTI_MAX;i++) 
	{
		unti[i].count++;
		//ウンチのランダム出現
		if (unti[i].count % 120 == 0)
		{
			unti[i].flag = true;
		}
		if (unti[i].flag == true)
		{
			unti[i].pos.y += unti[i].speed;
		}
		if (unti[i].flag == false)
		{
			unti[i].pos = { GetRand(500), 0 };
			unti[i].count = 0;
			unti[i].flag = true;
		}
		if (unti[i].pos.y > SCREEN_SIZE_Y + 32)
		{
			unti[i].pos = { GetRand(500), 0 };
			unti[i].flag = true;
		}

		//当たり判定
		if ((player.pos.x < unti[i].pos.x + unti[i].size.x
			&&unti[i].pos.x < player.pos.x + player.size.x
			&&player.pos.y < unti[i].pos.y + unti[i].size.y
			&&unti[i].pos.y < player.pos.y + player.size.y))
		{
			player.flag = false;
			unti[i].flag = false;
			player.hp -= 1;
		}
	}
}

//描画
void DrawUnti()
{
	for (int i = 0; i < UNTI_MAX; i++) 
	{
		if (unti[i].flag == true)
		{
			DrawGraph(unti[i].pos.x, unti[i].pos.y, UntiImage, true);
			/*DrawBox(unti.pos.x, unti.pos.y,
			unti.size.x, unti.size.y, 0xff0000, true);*/
			//DrawFormatString(30, 60, 0xff0000, "%d", unti[i].count, true);
		}
	}
}