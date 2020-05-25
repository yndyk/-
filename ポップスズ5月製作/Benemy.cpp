#include"main.h"
#include"Benemy.h"
#include"hitCheck.h"
#include"shot.h"
#include"box.h"
#include"player.h"
#include"enemy.h"
#include "score.h"

int BenemyImage[2];
int BenemyDamegeImage;
CHARACTER benemy;
int BenemyTime;
//ロード
void SysInitBenemy()
{
	LoadDivGraph("bmp/アンモナイト.png", 2, 2, 1, 32, 32, BenemyImage, true);
	BenemyDamegeImage = LoadGraph("bmp/アンモナイトダメージ.png");
	BenemyTime = 0;//ダメージの描画時間
}
//初期化
void InitBenemy()
{
	benemy.pos = { 50 + (rand() % 16) * 32, (rand() % 11) * 32 };
	benemy.speed = { 5,5 };
	benemy.size = { 32,32 };
	benemy.offSet = { benemy.size.x / 2,benemy.size.y / 2 };
	benemy.flag = false;
	benemy.count = 0;
	benemy.div = DIV_RAHGT;
	benemy.damageflag = false;
	benemy.hp = 5;
	
}
//更新
void UpdetaBenemy()
{
	//移動
	
	if (benemy.flag == false) 
	{
		BenemyTime++;
		benemy.pos.x += benemy.speed.x;
		if (benemy.pos.x >= 590)
		{
			benemy.speed.x = -benemy.speed.x;
			benemy.div = DIV_RAHGT;
		}
		if (benemy.pos.x < 0)
		{
			benemy.speed.x = -benemy.speed.x;
			benemy.div = DIV_LEFT;
		}
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
			benemy.damageflag = true;
		}
	}
	if (benemy.damageflag == true)
	{
		benemy.pos.y += 2;
		if (HitBox(benemy, player))
		{
			benemy.damageflag = false;
		}
	}
	
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

	if (benemy.damageflag == true)
	{
		DrawGraph(benemy.pos.x - benemy.offSet.x,
			benemy.pos.y - benemy.offSet.y,
			BenemyDamegeImage, true);
	}

	
	
	DrawFormatString(0, 360, 0xff0000, "テスト;%d", BenemyTime);
}

void DamegeBenemy()
{
	if (benemy.damageflag)
	{
		DrawGraph(benemy.pos.x - benemy.offSet.x,
			benemy.pos.y - benemy.offSet.y,
			BenemyDamegeImage, true);
		BenemyTime--;
		if (BenemyTime < 0 && benemy.hp > 0)
		{
			benemy.damageflag = false;
			BenemyTime = TIME_FRAME * 3;
			benemy.hp = 5;
		}
	}
	if (benemy.hp == 0)
	{
		benemy.flag = false;
		benemy.changeFlag = true;
	}
	
}
