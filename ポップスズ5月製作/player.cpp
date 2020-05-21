//-----------------------------------------------------
// 
// 
// 
// 
// 
//-----------------------------------------------------

#include "main.h"
#include "keycheck.h"
#include "player.h"
#include "enemy.h"
#include "hitCheck.h"

int playerImage[2];
int playerdamageImage;
CHARACTER player;
int BoxFlag;

//ロード
void SysInitPlayer()
{
	LoadDivGraph("bmp/潜水艇アニメーション.png", 2, 2, 1, 32, 32, playerImage);
	playerdamageImage = LoadGraph("bmp/プレイヤーダメージ.png");
}
//初期化
void InitPlayer()
{
	player.pos = { 500,430 };
	player.size = { 32, 32 };
	player.offSet = { player.size.x / 2, player.size.y / 2 };
	player.speed = { 5,5 };
	player.r = 16;
	player.div = DIV_RAHGT;
	player.hp = TIME_FRAME *PLAYER_HP_MAX;
	player.flag = true;
	player.damageflag = false;
	player.count = 0;
	BoxFlag = false;
}

//更新
void UpdetaPlayer()
{
	//移動
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		player.pos.x += player.speed.x;
		player.div = DIV_LEFT;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		player.pos.x -= player.speed.x;
		player.div = DIV_RAHGT;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		player.pos.y -= player.speed.y;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		player.pos.y += player.speed.y;
	}

	//移動制限
	if (player.pos.x >= 590)
	{
		player.pos.x = 590;
	}
	if (player.pos.x < 0)
	{
		player.pos.x = 0;
	}
	if (player.pos.y >= 430)
	{
		player.pos.y = 430;
	}
	if (player.pos.y < 0)
	{
		player.pos.y = 0;
	}
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].flag)				// 条件追加
		{
			if (HitCheckRectToRect(player, i, enemy))		// 矩形と矩形の当たり判定
			{
				player.flag = false;
				enemy[i].flag = false;
				player.damageflag = true;
				BoxFlag = true;
				player.hp -= 1;
				if (player.hp == 0)
				{
					gamemode = GMODE_OVER;
				}
				
				enemy[i].point = 1;
				if (enemy[0].point == 1 &&
					enemy[1].point == 1 &&
					enemy[2].point == 1 &&
					enemy[3].point == 1 &&
					enemy[4].point == 1 &&
					enemy[5].point == 1 &&
					enemy[6].point == 1 &&
					enemy[7].point == 1 &&
					enemy[8].point == 1)
				{				
						//enemyAllDeadFlag = true;
				}
			}
		}
	}
	if (gamemode == GMODE_OVER)
	{
		player.flag = false;
		for (int i = 0; i < ENEMY_MAX;i++)
		{
			enemy[i].flag = false;
		}
	}
	player.hp--;
	player.count++;
}

//描画
void DrawPlayer()
{
		switch (player.div)
		{
		case DIV_RAHGT:
				player.count++;
				if (player.flag)		// flagがtrueの時に描画
				{
					DrawGraph(player.pos.x - player.offSet.x, player.pos.y - player.offSet.y,
						playerImage[player.count / 50 % 2], true);
				}
				if (player.damageflag)
				{
					DrawGraph(player.pos.x - player.offSet.x, player.pos.y - player.offSet.y,
							  playerdamageImage, true);
				}
			break;
		case DIV_LEFT:
				player.count++;
				if (player.flag)		// flagがtrueの時に描画
				{
					DrawTurnGraph(player.pos.x - player.offSet.x, player.pos.y - player.offSet.y,
						playerImage[player.count / 50 % 2], true);
				}
				if (player.damageflag)
				{
					DrawTurnGraph(player.pos.x - player.offSet.x, player.pos.y - player.offSet.y,
								  playerdamageImage, true);
				}
			break;
		}

		player.damageflag = false;
		DrawFormatString(30, 30, 0xff0000, "%d", player.hp / TIME_FRAME, true);
		//DrawFormatString(0, 100, 0xff0000, "flag:%d", player.flag);
		if (BoxFlag == true) 
		{
			DrawBox(320, 430, 340, 450, 0xff0000, true);
		}
		// 当たり判定の可視化
		DrawBox(player.pos.x - player.offSet.x,
			player.pos.y - player.offSet.y,
			player.pos.x + player.offSet.x,
			player.pos.y + player.offSet.y, 0x000000, false);
		//DrawCircle(player.pos.x, player.pos.y, player.r, 0x000000, false);
		DrawBox(0, 440, player.hp / 60, 450 , 0xff0000, true);
		DrawBox(0, 440, player.hp / 60, 450, 0x000000, false);
}