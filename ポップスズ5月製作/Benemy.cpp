#include"main.h"
#include"Benemy.h"
#include"hitCheck.h"
#include"shot.h"
#include"box.h"
#include"player.h"
#include"enemy.h"
#include "score.h"
#include <math.h>

int BenemyImage[2];
int BenemyDamegeImage;
CHARACTER benemy;
int BenemyTime;
XY_F length;
float distance;
int BsearchDistance;
XY tmpSpeed;

//ロード
void SysInitBenemy()
{
	LoadDivGraph("bmp/アンモナイト.png", 2, 2, 1, 32, 32, BenemyImage, true);
	BenemyDamegeImage = LoadGraph("bmp/アンモナイトダメージ.png");
	
}

//初期化
void InitBenemy()
{
	benemy.pos = { 50 + (rand() % 16) * 32, (rand() % 11) * 32 };
	benemy.speed = { 3,3 };
	if (rand() % 5 == 0)
	{
		benemy.speed.x = -1 * benemy.speed.x;
	}
	if (rand() % 5 == 0)
	{
		benemy.speed.y = -1 * benemy.speed.y;
	}
	benemy.size = { 32,32 };
	benemy.offSet = { benemy.size.x / 2,benemy.size.y / 2 };
	benemy.flag = false;
	benemy.count = 0;
	benemy.div = DIV_RAHGT;
	benemy.damageflag = false;
	benemy.hp = 5;
	benemy.movePattern = 0;
	benemy.refrectFlagX = false;
	benemy.refrectFlagY = false;
	BenemyTime = TIME_FRAME*3;//ダメージの描画時間
	BsearchDistance = 96;	// 敵の索敵距離(この範囲内に入ると敵が自分に向かってくる) 要調整！
}

//更新
void UpdetaBenemy()
{
	//移動
	if (benemy.flag == false) 
	{
		BenemyTime++;
		benemy.pos.x += benemy.speed.x;
		for (int i = 0; i < SHOT_MAX; i++)
		{
			if (HitCheckRectToRect(benemy, i, shot))
			{
				benemy.flag = true;
				benemy.damageflag = true;
				SetScore(SCORE, 600);//スコア加算
			}		
		}
		if (HitBox(benemy, player))
		{
			benemy.flag = true;
		}
		moveBenemy();//動き
	}
	DamegeBenemy();
}

//描画
void DrawBenemy()
{
	if (benemy.flag == false) 
	{
		switch (benemy.div)
		{
		case DIV_RAHGT:
			benemy.count++;
			DrawGraph(benemy.pos.x - benemy.offSet.x,
				benemy.pos.y - benemy.offSet.y,
				BenemyImage[benemy.count / 50 % 2], true);
			break;
		case DIV_LEFT:
			benemy.count++;
			DrawTurnGraph(benemy.pos.x - benemy.offSet.x,
				benemy.pos.y - benemy.offSet.y,
				BenemyImage[benemy.count / 50 % 2], true);
			break;
		default:
			break;
		}
	}
	//
	if (benemy.damageflag == true)
	{
		switch (benemy.div)
		{
		case DIV_RAHGT:
			benemy.count++;
			DrawGraph(benemy.pos.x - benemy.offSet.x,
				benemy.pos.y - benemy.offSet.y,
				BenemyDamegeImage, true);
			break;
		case DIV_LEFT:
			benemy.count++;
			DrawTurnGraph(benemy.pos.x - benemy.offSet.x,
				benemy.pos.y - benemy.offSet.y,
				BenemyDamegeImage, true);
			break;
		default:
			break;
		}
	}
	DrawBox(benemy.pos.x - benemy.offSet.x,
		benemy.pos.y - benemy.offSet.y,
		benemy.pos.x + benemy.offSet.x,
		benemy.pos.y + benemy.offSet.y,
		0x000000, false);
	DrawCircle(benemy.pos.x, benemy.pos.y, BsearchDistance, 0x000000, false);
	DrawFormatString(0, 360, 0xff0000, "テスト;%d", benemy.hp);
}

void DamegeBenemy()
{
	//ダメージ受けた後
	if (benemy.damageflag == true)
	{
		benemy.pos.y += 2;
		if(BenemyTime <= 0)
		{
			benemy.flag = false;
		}
		
		if (benemy.pos.y == SCREEN_SIZE_Y)
		{
			benemy.damageflag = false;
		}
	}
}

//移動制限
void moveBenemy()
{
	//移動制限
	if (benemy.refrectFlagX == false && benemy.refrectFlagX == false) 
	{
		if (benemy.pos.x < 50)
		{
			benemy.pos.x = 50;
			benemy.refrectFlagX = true;
		}
		if (benemy.pos.x + benemy.size.x > SCREEN_SIZE_X - 50)
		{
			benemy.pos.x = SCREEN_SIZE_X - 50 - benemy.size.x;
			benemy.refrectFlagX = true;
		}

		if (benemy.pos.y < 50)
		{
			benemy.pos.y = 50;
			benemy.refrectFlagY = true;
		}
		if (benemy.pos.y + benemy.size.y > SCREEN_SIZE_Y - 50)
		{
			benemy.pos.y = SCREEN_SIZE_Y - 50 - benemy.size.y;
			benemy.refrectFlagY = true;
		}
	}
	
	if (benemy.count % 60 == 0)
	{
		BrefrectMoveXY();
		benemy.movePattern = rand() % 2;
	}
	int tmpR = player.r + benemy.r;

	// ここに敵の一定範囲内に入ったらプレイヤーのほうに移動してくる処理を書く
	length = { (float)(player.pos.x - benemy.pos.x), (float)(player.pos.y - benemy.pos.y) };			// 中心間距離のX,Y成分
	distance = sqrtf(length.x * length.x + length.y * length.y);
	tmpSpeed= benemy.speed;

	if (distance - BsearchDistance < player.r)
	{
		if (player.pos.x - benemy.pos.x > 0)
		{
			if (benemy.speed.x < 0)
				benemy.speed.x = -1 * tmpSpeed.x;
		}
		else
		{
			if (benemy.speed.x > 0)
				benemy.speed.x = -1 * tmpSpeed.x;
		}
		if (abs(benemy.pos.x - player.pos.x) < 2)
		{
			benemy.speed.x = 0;
			if (player.pos.y - benemy.pos.y > 0)
			{
				if (benemy.speed.y < 0)
					benemy.speed.y = -1 * tmpSpeed.y;
			}
			else
			{
				if (benemy.speed.y > 0)
					benemy.speed.y = -1 * tmpSpeed.y;
			}
			if (abs(player.pos.y - benemy.pos.y) < 2)
				benemy.speed.y = 0;
			//ここから下の処理内容を+から－に変更
			benemy.pos.y -= benemy.speed.y;
		}

		benemy.pos.x -= benemy.speed.x;
	}
	else
	{
		if (benemy.movePattern == 0)
			benemy.pos.y -= benemy.speed.y;
		if (benemy.movePattern == 1)
			benemy.pos.x -= benemy.speed.x;
	}
	benemy.speed = tmpSpeed;
}

//大まかな動き
void BrefrectMoveXY()
{
	if (benemy.refrectFlagX)
	{
		benemy.speed.x = -1 * benemy.speed.x;
		if (benemy.speed.x < 0)				// 速度が負の時
			benemy.div = DIV_LEFT;
		if (benemy.speed.x > 0)				// 速度が正の時
			benemy.div = DIV_RAHGT;
		benemy.refrectFlagX = false;
	}
	if (benemy.refrectFlagY)
	{
		benemy.speed.y = -1 * benemy.speed.y;

		benemy.refrectFlagY = false;
	}
}
