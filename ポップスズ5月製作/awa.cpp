#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "awa.h"
#include "player.h"

CHARACTER bubble[BUBBLE_MAX];

int bubbleImage;
int bubbleCnt;	// 現在画面上に表示されている泡の数
int randNum;	// 乱数格納用変数
int cnt;
int num;

void SysInitBubble()
{
 	bubbleImage = LoadGraph("bmp/awa.png");
}

void InitBubble()
{
	for (int i = 0; i < BUBBLE_MAX; i++) 
	{
		bubble[i].size = { 26, 26 };
		bubble[i].pos = { 64 + rand() % 18 + 1 * 32, SCREEN_SIZE_Y - 32 *3 };
		bubble[i].speed = 1;
		bubble[i].hp = 60 * 20;			// 泡により回復するライフの量
		bubble[i].flag = false;		// 表示するかしないか
		bubble[i].count = 0;
	}
	cnt = 0;				// 毎フレーム加算されるカウント
	bubbleCnt = 0;			// 現在画面上に表示されている泡の数
	num = 0;

}

void UpdetaBuble()
{
	srand(time(NULL));
	cnt++;
	if (cnt % 180 == 0) 
	{
		for (int i = 0; i < BUBBLE_MAX; i++) 
		{
			if (!bubble[i].flag) 
			{
				bubble[i].flag = true;
				bubble[i].pos = { 64 + (rand() % 18 + 1) * 32, SCREEN_SIZE_Y + 32 };
				break;
			}
		}
	}

	for (int i = 0; i < BUBBLE_MAX; i++)
	{
		if (bubble[i].flag)
		{
			bubble[i].pos.y -= bubble[i].speed;

			if (bubble[i].pos.y + bubble[i].size.y < 0)
			{
				bubble[i].flag = false;
				bubble[i].pos = { 64 + (rand() % 18 + 1) * 32, SCREEN_SIZE_Y + 32 };
			}
			HitCheckBubble();
		}
	}
}

void DrawBuble()
{
	for (int i = 0; i < BUBBLE_MAX; i++) 
	{
		if (bubble[i].flag == true)
		{
			DrawGraph(bubble[i].pos.x, bubble[i].pos.y, bubbleImage, true);
		}

		//DrawFormatString(0, 50, 0xff0000, "cnt:%d", cnt);
		//DrawFormatString(0, 120 + i * 18, 0xff0000, "y:%d", bubble[i].pos.y);
		//DrawFormatString(70, 120 + i * 18, 0xff0000, "x:%d", bubble[i].pos.x);
		//DrawFormatString(140, 120 + i * 18, 0xff0000, "flag:%d", bubble[i].flag);
	}
}


void HitCheckBubble()
{
	for (int i = 0; i < BUBBLE_MAX; i++) 
	{
		if (bubble[i].flag == true)
		{
			if (player.pos.x < bubble[i].pos.x + bubble[i].size.x &&
				player.pos.x + player.size.x > bubble[i].pos.x &&
				player.pos.y < bubble[i].pos.y + bubble[i].size.y &&
				player.pos.y + player.size.y > bubble[i].pos.y)
			{
				bubble[i].flag = false;
				if (player.hp < TIME_FRAME*PLAYER_HP_MAX)
				{
					player.hp = player.hp + bubble[i].hp;
				}
				if (player.hp + bubble[i].hp >= TIME_FRAME *PLAYER_HP_MAX)
				{
					player.hp = TIME_FRAME *PLAYER_HP_MAX;
				}
			}
		}
	}
}

void BubbleDelete()
{
	for (int i = 0; i < BUBBLE_MAX; i++) 
	{
		if (bubble[i].flag) 
		{
			cnt = 0;
			bubble[i].flag = false;
			num++;
		}
	}
}
