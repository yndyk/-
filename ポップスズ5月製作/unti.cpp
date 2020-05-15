//-------------------------------------
//
// ステージの切り替えの処理のほうにDeleteUnti()を移動しました
//
//-----------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include"player.h"
#include"unti.h"

int UntiImage;
CHARACTER unti[UNTI_MAX];
int Untinum;
int UntiCount;

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
		unti[i].pos = { 64 + rand() % 18 + 1 * 32, 0 - 32 * 3 };
		unti[i].size = { UNTI_SIZE_X,UNTI_SIZE_Y };
		unti[i].flag = false;
		unti[i].speed = 6;
		unti[i].count = false;
		
	}
	UntiCount = 0;
	Untinum = 0;
}

//更新
void UpdetaUnti()
{
	srand(time(NULL));
	UntiCount++;
		//ウンチのランダム出現
	ApperUnti();
	for (int i = 0; i < UNTI_MAX; i++)
	{
		if (unti[i].flag)
		{
			unti[i].pos.y += unti[i].speed;

			if (unti[i].pos.y + unti[i].size.y < 0)
			{
				unti[i].flag = false;
				unti[i].pos = { 64 + (rand() % 18 + 1) * 32, 0 + 32 };
			}
		}

		if(unti[i].pos.y > SCREEN_SIZE_Y)
		{
			unti[i].flag = false;
		}
	}

	for (int i = 0; i < UNTI_MAX; i++)
	{
			//当たり判定
			if ((player.pos.x < unti[i].pos.x + unti[i].size.x
				&&unti[i].pos.x < player.pos.x + player.size.x
				&&player.pos.y < unti[i].pos.y + unti[i].size.y
				&&unti[i].pos.y < player.pos.y + player.size.y))
			{
				player.flag = false;
				unti[i].flag = false;
				player.damageflag = true;
				player.hp -= TIME_FRAME * 1;
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
			//DrawFormatString(30, 60, 0xff0000, "%d", UntiCount, true);
		}
		/*DrawFormatString(0, 50, 0xff0000, "UntiCount:%d", UntiCount);
		DrawFormatString(0, 120 + i * 18, 0xff0000, "y:%d", unti[i].pos.y);
		DrawFormatString(70, 120 + i * 18, 0xff0000, "x:%d", unti[i].pos.x);
		DrawFormatString(140, 120 + i * 18, 0xff0000, "flag:%d", unti[i].flag);*/
	}
}

void DeleteUnti()
{
	for (int i = 0; i < UNTI_MAX; i++) 
	{
		if (unti[i].flag) 
		{
			UntiCount = 0;
			unti[i].flag = false;
			Untinum++;
		}
	}
}

void ApperUnti()
{
	if (UntiCount % 120 == 0)
	{
		for (int i = 0; i < UNTI_MAX; i++)
		{
			if (unti[i].flag == false)
			{
				unti[i].flag = true;
				unti[i].pos = { 64 + (rand() % 18 + 1) * 32, 0 + 32 };
				break;
			}
		}
	}
}