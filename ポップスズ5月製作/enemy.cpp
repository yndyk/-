//-----------------------------------------------------
// 
// 残機の可視化
// 残機の追加
// enemyTimeを配列に変更
// 
// 
//-----------------------------------------------------

#include "main.h"
#include "keycheck.h"
#include "enemy.h"
#include "player.h"
#include "shot.h"
#include "ikayaki.h"
#include"map.h"
#include "map.h"
#include <math.h>
#include "hitCheck.h"

int enemyImage[3][2];//エネミー3種類,2パターン
int enemyDamageImage[3];//エネミーダメージ3種類
bool enemyAllDeadFlag;
CHARACTER enemy[ENEMY_MAX];
TYPE_MODE enemyType;//これで種類を管理する
int enemyTime[ENEMY_MAX];//エネミー描画切り替え時間
int enemyScore;//スコア管理
//ロード
void SysInitEnemy()
{
	LoadDivGraph("bmp/イカプレーン.png", 2, 2, 1, 32, 32, enemyImage[0], true);
	LoadDivGraph("bmp/イカメカ.png", 2, 2, 1, 32, 32, enemyImage[1], true);
  	LoadDivGraph("bmp/長足イカ.png", 2, 2, 1, 32, 64, enemyImage[2], true);
	enemyDamageImage[0] = LoadGraph("bmp/イカプレーンダメージ.png");
	enemyDamageImage[1] = LoadGraph("bmp/イカメカダメージ.png");
	enemyDamageImage[2] = LoadGraph("bmp/長足イカダメージ.png");
}
//初期化
void InitEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		TypeEnemy();

		enemy[i].pos = { 50 + (rand() % 16) * 32, (rand() % 11) * 32 };
		enemy[i].speed = { 2, 2 };
		if (rand() % 2 == 0)
		{
			enemy[i].speed.x = -1 * enemy[i].speed.x;

		}
		if (rand() % 2 == 0)
		{
			enemy[i].speed.y = -1 * enemy[i].speed.y;
		}
		enemy[i].count = 0;
		enemy[i].flag = true;
		enemy[i].point = 0;
		enemy[i].size = { 32,32 };
		enemy[i].offSet = { enemy[i].size.x / 2, enemy[i].size.y / 2 };
		enemy[i].hp = 3;			// エネミーの残機
		enemy[i].changeFlag = false;
		enemy[i].div = DIV_RAHGT;
		enemy[i].refrectFlagX = false;			// x軸進行方向反転フラグ　true:反転　false:そのまま
		enemy[i].refrectFlagY = false;			// y軸進行方向反転フラグ
		enemy[i].movePattern = 0;
		enemy[i].damageflag = false;
		enemy[i].score = 0;
		enemyTime[i] = TIME_FRAME * 3;//ダメージの描画時間
	}
	enemyAllDeadFlag = false;
	enemyScore = 0;
}

//更新
void UpdetaEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].flag)
		{
			//弾の当たり判定
			if (shot.flag)
			{
				if (HitCheckRectToRect(shot, i, enemy))			// 矩形と矩形の当たり判定
				{
					shot.flag = false;
					//enemy[i].flag = false;
					enemy[i].damageflag = true;
					shot.pos.x = player.pos.x;
					shot.pos.y = player.pos.y;
					enemyScore += enemy[i].score;//スコアを加算
					enemy[i].hp -= 1;// 
				}
			}
			//移動
			if (enemyTime[i] == TIME_FRAME * 3)	// ダメージを受けると動きが止まる(この条件を消せば攻撃を食らっても動きが止まらない)
			{
				MoveEnemy(i);// 敵の移動制御
			}
		}
		else
		{
			//クリア判定
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
			}

			if (enemy[i].changeFlag)		// イカ焼きに代わるかどうか
			{
				UpdateIkayaki(enemy[i].pos, enemy[i].changeFlag, i);
			}
		}
	}
}

//描画
void DrawEnemy()
{
	int ID = GetStageID();

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		int enenmyType = GetRand(2);
		if (enemy[i].flag == true)
		{
			switch (enemy[i].div)
			{
			case DIV_RAHGT:
				enemy[i].count++;	
				//エネミータイプ
				if (!enemy[i].damageflag)
				{
					DrawGraph(enemy[i].pos.x - enemy[i].offSet.x,
						enemy[i].pos.y - enemy[i].offSet.y,
						enemyImage[enemy[i].type][enemy[i].count / 50 % 2], true);
				}
				DamageEnemy(i);
				break;
			case DIV_LEFT:
				enemy[i].count++;	
				if (!enemy[i].damageflag)
				{
					DrawTurnGraph(enemy[i].pos.x - enemy[i].offSet.x,
						enemy[i].pos.y - enemy[i].offSet.y,
						enemyImage[enemy[i].type][enemy[i].count / 50 % 2], true);
				}
				DamageEnemy(i);
				break;
			default:
				break;
			}
		
			// 当たり判定の可視化
			DrawBox(enemy[i].pos.x - enemy[i].offSet.x,
				enemy[i].pos.y - enemy[i].offSet.y,
				enemy[i].pos.x + enemy[i].offSet.x,
				enemy[i].pos.y + enemy[i].offSet.y,
				0x000000, false);

			DrawFormatString(enemy[i].pos.x, enemy[i].pos.y - 32, 0xff0000, "%d", enemy[i].hp);	// 残機の可視化
		}
		//DrawFormatString(0, 100 + i * 18, 0xff0000, "x:%d", enemy[i].pos.x);
		//DrawFormatString(50, 100 + i * 18, 0xff0000, "y:%d", enemy[i].pos.y);
		//DrawFormatString(50, 100 + i * 18, 0xff0000, "eT;%d", enemyTime[i]);
		//DrawFormatString(100, 100 + i * 18, 0xff0000, "df:%d", enemy[i].damageflag);
		//DrawFormatString(150, 100 + i * 18, 0xff0000, "cf:%d", enemy[i].changeFlag);
		//DrawFormatString(150, 100 + i * 18, 0xff0000, "f:%d", enemy[i].flag);

		DrawIkayaki(i);

		//DrawFormatString(60, 30, 0xff0000, "%d", enemyScore, true);
		//DrawFormatString(40, 40, 0xff0000, "%d", enemy[0].score, true);
		//DrawFormatString(40, 60, 0xff0000, "%d", enemy[1].score, true);
		//DrawFormatString(40, 80, 0xff0000, "%d", enemy[2].score, true);
		//DrawFormatString(40, 100, 0xff0000, "%d", enemy[3].score, true);
		//DrawFormatString(40, 120, 0xff0000, "%d", enemy[4].score, true);
		//DrawFormatString(40, 140, 0xff0000, "%d", enemy[5].score, true);
		//DrawFormatString(40, 160, 0xff0000, "%d", enemy[6].score, true);
		//DrawFormatString(40, 180, 0xff0000, "%d", enemy[7].score, true);
		//DrawFormatString(40, 200, 0xff0000, "%d", enemy[8].score, true);
	}
	/*DrawFormatString(30, 30, 0xffff00, "%d", enemy[0].point, true);
	DrawFormatString(30, 40, 0xffff00, "%d", enemy[1].point, true);
	DrawFormatString(30, 50, 0xffff00, "%d", enemy[2].point, true);
	DrawFormatString(30, 60, 0xffff00, "%d", enemy[3].point, true);
	DrawFormatString(30, 70, 0xffff00, "%d", enemy[4].point, true);
	DrawFormatString(30, 80, 0xffff00, "%d", enemy[5].point, true);*/
}

void MoveEnemy(int num)
{
	int ID = GetStageID();

	// 移動制限
	if (!enemy[num].refrectFlagX || !enemy[num].refrectFlagY)
	{// x軸移動制限
		if (enemy[num].pos.x < 50)
		{
			enemy[num].pos.x = 50;
			enemy[num].refrectFlagX = true;
		}
		if (enemy[num].pos.x + enemy[num].size.x > SCREEN_SIZE_X - 50)
		{
			enemy[num].pos.x = SCREEN_SIZE_X - 50 - enemy[num].size.x;
			enemy[num].refrectFlagX = true;
		}
		// y軸移動制限
		if (enemy[num].pos.y < 50)
		{
			enemy[num].pos.y = 50;
			enemy[num].refrectFlagY = true;
		}
		if (enemy[num].pos.y + enemy[num].size.y > SCREEN_SIZE_Y - 50)
		{
			enemy[num].pos.y = SCREEN_SIZE_Y - 50 - enemy[num].size.y;
			enemy[num].refrectFlagY = true;
		}
	}

	// stageID = 0(左右移動のみ)
	if (ID == STAGE1)
	{
		RefrectMoveXY(num);			// 移動方向反転
		enemy[num].pos.x += enemy[num].speed.x;
	}

	// stageID = 1(上下左右)
	if (ID == STAGE2)
	{
		RefrectMoveXY(num);

		if (enemy[num].count % 90 == 0)
		{
			enemy[num].movePattern = rand() % 2;
		}
		if (enemy[num].movePattern == 0)
			enemy[num].pos.y += enemy[num].speed.y;
		if (enemy[num].movePattern == 1)
			enemy[num].pos.x += enemy[num].speed.x;
	}
	
	// プレイヤーに向かって移動()
	if (ID == STAGE3)
	{
		if (enemy[num].count % 90 == 0)
		{
			RefrectMoveXY(num);
			enemy[num].movePattern = rand() % 2;
		}

		// ここに敵の一定範囲内に入ったらプレイヤーのほうに移動してくる処理を書く


		if (enemy[num].movePattern == 0)
			enemy[num].pos.y += enemy[num].speed.y;
		if (enemy[num].movePattern == 1)
			enemy[num].pos.x += enemy[num].speed.x;

	}


}

void RefrectMoveXY(int num)
{
	if (enemy[num].refrectFlagX)
	{
		enemy[num].speed.x = -1 * enemy[num].speed.x;
		if (enemy[num].speed.x < 0)				// 速度が負の時
			enemy[num].div = DIV_LEFT;
		if (enemy[num].speed.x > 0)				// 速度が正の時
			enemy[num].div = DIV_RAHGT;
		enemy[num].refrectFlagX = false;
	}
	if (enemy[num].refrectFlagY)
	{
		enemy[num].speed.y = -1 * enemy[num].speed.y;

		enemy[num].refrectFlagY = false;
	}
}

void TypeEnemy()
{
	for(int i = 0; i < ENEMY_MAX;i++)
	{
		switch (enemyType)//エネミー別に初期化する
		{
		case TYPE_1:
			enemy[i].size = { 32,32 };
			enemy[i].type = TYPE_1;
			enemy[i].score = 100;
			break;
		case TYPE_2:
			enemy[i].size = { 32,32 };
			enemy[i].type = TYPE_2;
			enemy[i].score = 150;
			break;
		case TYPE_3:
			enemy[i].size = { 32,64 };
			enemy[i].type = TYPE_3;
			enemy[i].score = 170;
			break;
		default:
			break;
		}
	}

	enemy[0].type = TYPE_1; enemy[0].score = 100;
	enemy[1].type = TYPE_2; enemy[1].score = 150;
	enemy[2].type = TYPE_3; enemy[2].score = 170;
	enemy[3].type = TYPE_1; enemy[3].score = 100;
	enemy[4].type = TYPE_2; enemy[4].score = 150;
	enemy[5].type = TYPE_3; enemy[5].score = 170;
	enemy[6].type = TYPE_1; enemy[6].score = 100;
	enemy[7].type = TYPE_2; enemy[7].score = 150;
	enemy[8].type = TYPE_3; enemy[8].score = 170;
}
//被ダメージ時の処理
void DamageEnemy(int num)
{
	if (enemy[num].damageflag)
	{
		DrawGraph(enemy[num].pos.x - enemy[num].offSet.x,
			enemy[num].pos.y - enemy[num].offSet.y,
			enemyDamageImage[enemy[num].type], true);
		enemyTime[num]--;
		if (enemyTime[num] < 0 && enemy[num].hp > 0)		// 
		{
			enemy[num].damageflag = false;
			enemyTime[num] = TIME_FRAME * 3;
			enemy[num].hp = 3;
		}
	}
	if (enemy[num].hp == 0)
	{
		enemy[num].flag = false;
		enemy[num].changeFlag = true;
	}
	DrawFormatString(499, num * 18, 0xff0000, "eT;%d", enemyTime[num] / TIME_FRAME);
}


