#include "main.h"
#include "surume.h"
#include "player.h"
#include "hitCheck.h"
#include"enemy.h"
#include "score.h"

CHARACTER surume[SURUME_MAX];
int surumeImage;

//ロード
void SysInitSurume()
{
	surumeImage = LoadGraph("bmp/イカスルメ.png");
}
//初期化
void InitSurume()
{
	for (int i = 0; i < SURUME_MAX; i++)
	{
		surume[i].pos = { 0, 0 };
		surume[i].speed = { 1,1 };
		surume[i].count = 0;
		surume[i].flag = false;
		surume[i].size = { 32, 32 };
		surume[i].offSet = { surume[i].size.x / 2, surume[i].size.y / 2 };
		surume[i].hp = 30;		// イカ焼き取得時に回復するライフの量
		surume[i].onlyOnce = false;
	}
}
//更新
void UpdetaSurume(XY pos, bool flag, int num)
{
	if (!surume[num].onlyOnce)
	{
		if (!surume[num].flag)
		{
			surume[num].pos = pos;
			surume[num].flag = flag;
			surume[num].onlyOnce = true;
		}
	}


	if (surume[num].flag)
	{
		surume[num].pos.y += surume[num].speed.y;

		if (surume[num].pos.y > SCREEN_SIZE_Y)
		{
			surume[num].flag = false;
		}

		if (HitCheckRectToRect(player, num, surume))		// 矩形と矩形の当たり判定
		{
			surume[num].flag = false;
			if (player.hp + surume[num].hp < TIME_FRAME * PLAYER_HP_MAX)
			{
				player.hp = player.hp + surume[num].hp;
			}
			if (player.hp + surume[num].hp >= TIME_FRAME * PLAYER_HP_MAX)
			{
				player.hp = TIME_FRAME * PLAYER_HP_MAX;
			}
			//enemyScore += 300;
			SetScore(SCORE, 300);//スコア加算
			
		}
		PlaySoundMem(ChngSound, DX_PLAYTYPE_LOOP);//サウンド
	}
}

//描画
void DrawSurume(int num)
{
	if (surume[num].flag)
	{
		DrawGraph(surume[num].pos.x - surume[num].offSet.x,
			surume[num].pos.y - surume[num].offSet.y,
			surumeImage, true);
		// 当たり判定の可視化
		DrawBox(surume[num].pos.x - surume[num].offSet.x,
			surume[num].pos.y - surume[num].offSet.y,
			surume[num].pos.x + surume[num].offSet.x,
			surume[num].pos.y + surume[num].offSet.y,
			0x000000, false);
		
	}
}

void DeleteSurume()
{
	for (int i = 0; i < SURUME_MAX; i++)
	{
		surume[i].flag = false;
		
	}
}