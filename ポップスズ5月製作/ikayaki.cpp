//-------------------------------
//
// 
//
//-------------------------------

#include "main.h"
#include "ikayaki.h"
#include "player.h"

int ikayakiImage;
CHARACTER ikayaki[IKAYAKI_MAX];

void SysInitIkayaki()
{
	ikayakiImage = LoadGraph("bmp/イカ焼き.png");
}

void InitIkayaki()
{
	for (int i = 0; i < IKAYAKI_MAX; i++)
	{
		ikayaki[i].pos = { 0, 0 };
		ikayaki[i].speed = { 1,1 };
		ikayaki[i].count = 0;
		ikayaki[i].flag = false;
		ikayaki[i].size = { 32, 32 };
		ikayaki[i].hp = 30;		// イカ焼き取得時に回復するライフの量
		ikayaki[i].onlyOnce = false;
	}
}

void UpdateIkayaki(XY pos,bool flag, int num)	// pos:座標　flag:フラグ　num:配列番号
{
	if (!ikayaki[num].onlyOnce)
	{
		if (!ikayaki[num].flag)
		{
			ikayaki[num].pos = pos;
			ikayaki[num].flag = flag;
			ikayaki[num].onlyOnce = true;
		}
	}

		
	if (ikayaki[num].flag)
	{
		ikayaki[num].pos.y += ikayaki[num].speed.y;

		if (ikayaki[num].pos.y > SCREEN_SIZE_Y)
		{
			ikayaki[num].flag = false;
		}

		HitCheckIkayaki(num);
	}
}

void DrawIkayaki(int num)
{
	if (ikayaki[num].flag)
	{
		DrawGraph(ikayaki[num].pos.x, ikayaki[num].pos.y, ikayakiImage, true);
	}
	//DrawFormatString(0, 100 + num * 18, 0xff0000, "f;%d", ikayaki[num].flag);
	//DrawFormatString(50, 100 + num * 18, 0xff0000, "x:%d", ikayaki[num].pos.x);
	//DrawFormatString(100, 100 + num * 18, 0xff0000, "y:%d", ikayaki[num].pos.y);
	//DrawFormatString(150, 100 + num * 18, 0xff0000, "num;%d", num);
}

void HitCheckIkayaki(int num)
{
	if (ikayaki[num].flag)
	{
		if (player.pos.x < ikayaki[num].pos.x + ikayaki[num].size.x &&
			player.pos.x + player.size.x > ikayaki[num].pos.x &&
			player.pos.y < ikayaki[num].pos.y + ikayaki[num].size.y &&
			player.pos.y + player.size.y > ikayaki[num].pos.y)
		{
			ikayaki[num].flag = false;
			if (player.hp < TIME_FRAME * PLAYER_HP_MAX)
			{
				player.hp = player.hp + ikayaki[num].hp;
			}
			if (player.hp + ikayaki[num].hp >= TIME_FRAME * PLAYER_HP_MAX)
			{
				player.hp = TIME_FRAME * PLAYER_HP_MAX;
			}
		}
	}
}

void DeleteIkayaki()
{
	for (int i = 0; i < IKAYAKI_MAX; i++)
	{
		ikayaki[i].flag = false;
	}
}
