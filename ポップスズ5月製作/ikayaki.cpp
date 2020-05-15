//-------------------------------
//
// UpdateIkayaki()に敵の座標の取得を1度だけ実行する条件を追加しました
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
		ikayaki[i].speed = 1;
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
			ikayaki[num].onlyOnce = true;
		}
	}

	ikayaki[num].flag = flag;
		
	if (ikayaki[num].flag)
	{
		ikayaki[num].pos.y += ikayaki[num].speed;

		if (ikayaki[num].pos.y > SCREEN_SIZE_Y)
		{
			ikayaki[num].flag = false;
		}

		HitCheckIkayaki();
	}
}

void DrawIkayaki(int num)
{
	if (ikayaki[num].flag)
	{
		DrawGraph(ikayaki[num].pos.x, ikayaki[num].pos.y, ikayakiImage, true);
	}
	DrawFormatString(0, 100 + num * 18, 0xff0000, "f;%d", ikayaki[num].flag);
	DrawFormatString(50, 100 + num * 18, 0xff0000, "x:%d", ikayaki[num].pos.x);
	DrawFormatString(100, 100 + num * 18, 0xff0000, "y:%d", ikayaki[num].pos.y);
	//DrawFormatString(150, 100 + num * 18, 0xff0000, "num;%d", num);
}

void HitCheckIkayaki()
{
	for (int i = 0; i < IKAYAKI_MAX; i++)
	{
		if (ikayaki[i].flag)
		{
			if (player.pos.x < ikayaki[i].pos.x + ikayaki[i].size.x &&
				player.pos.x + player.size.x > ikayaki[i].pos.x &&
				player.pos.y < ikayaki[i].pos.y + ikayaki[i].size.y &&
				player.pos.y + player.size.y > ikayaki[i].pos.y)
			{
				ikayaki[i].flag = false;
				if (player.hp < TIME_FRAME * PLAYER_HP_MAX)
				{
					player.hp = player.hp + ikayaki[i].hp;
				}
				if (player.hp + ikayaki[i].hp >= TIME_FRAME * PLAYER_HP_MAX)
				{
					player.hp = TIME_FRAME * PLAYER_HP_MAX;
				}
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
