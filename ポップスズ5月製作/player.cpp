//-----------------------------------------------------
// 
// プレイヤーの当たり判定に敵に当たったときの処理を追加
//	if (enemy[0]～[8].point == 1)の箇所
// 
//-----------------------------------------------------

#include "main.h"
#include"keycheck.h"
#include"player.h"
#include"enemy.h"

int playerImage[2];
int playerdamageImage;
CHARACTER player;

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
	player.speed = 5;
	player.div = DIV_RAHGT;
	player.hp = TIME_FRAME *PLAYER_HP_MAX;
	player.flag = false;
	player.damageflag = false;
	player.count = 0;
}

//更新
void UpdetaPlayer()
{
	//移動
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		player.pos.x += player.speed;
		player.div = DIV_LEFT;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		player.pos.x -= player.speed;
		player.div = DIV_RAHGT;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		player.pos.y -= player.speed;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		player.pos.y += player.speed;
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
		if ((player.pos.x < enemy[i].pos.x + enemy[i].size.x
			&&enemy[i].pos.x < player.pos.x + player.size.x
			&&player.pos.y < enemy[i].pos.y + enemy[i].size.y
			&&enemy[i].pos.y < player.pos.y + player.size.y))
		{
			player.flag = true;
			enemy[i].flag = false;
			player.damageflag = true;
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
				enemyAllDeadFlag = true;
				//gamemode = GMODE_CLERA;
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
				DrawGraph(player.pos.x, player.pos.y, playerImage[player.count / 50 % 2], true);
				if (player.damageflag == true)
				{
					DrawGraph(player.pos.x, player.pos.y, playerdamageImage, true);
				}
			break;
		case DIV_LEFT:
				player.count++;
				DrawTurnGraph(player.pos.x, player.pos.y, playerImage[player.count / 50 % 2], true);
				if (player.damageflag == true)
				{
					DrawTurnGraph(player.pos.x, player.pos.y, playerdamageImage, true);
				}
			break;
		}
		player.damageflag = false;
		DrawFormatString(30, 30, 0xff0000, "%d", player.hp / TIME_FRAME, true);
		DrawBox(0, 440, player.hp / 60, 450 , 0xff0000, true);
		DrawBox(0, 440, player.hp / 60, 450, 0x000000, false);
}