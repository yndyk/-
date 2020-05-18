//-----------------------------------------------------
// 
// 敵の初期座標の取得乱数の変更
// 描画をオフセット分ずらした
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
int enemyImage[ENEMY_TYPE_MAX][2];//エネミー3種類,2パターン
int enemyType;
int enemyType2;
int enemyType3;
CHARACTER enemy[ENEMY_MAX];
bool enemyAllDeadFlag;

//ロード
void SysInitEnemy()
{
	LoadDivGraph("bmp/イカプレーン.png", 2, 2, 1, 32, 32, enemyImage[0], true);
	LoadDivGraph("bmp/イカメカ.png", 2, 2, 1, 32, 32, enemyImage[1], true);
  	LoadDivGraph("bmp/長足イカ.png", 2, 2, 1, 32, 64, enemyImage[2], true);
	enemyType = false;
	enemyType2 = false;
	enemyType3 = false;
}
//初期化
void InitEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		switch (enemy[i].type)//エネミー別に初期化する
		{
		case TYPE_1:
			enemy[i].size = { 32,32 };
			enemy[i].type = TYPE_1;
			break;
		case TYPE_2:
			enemy[i].size = { 32,32 };
			enemy[i].type = TYPE_2;
			break;
		case TYPE_3:
			enemy[i].size = { 32,64 };
			enemy[i].type = TYPE_3;
			break;
		default:
			break;
		}

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
		enemy[i].changeFlag = false;
		enemy[i].div = DIV_RAHGT;
		enemy[i].refrectFlagX = false;			// x軸進行方向反転フラグ　true:反転　false:そのまま
		enemy[i].refrectFlagY = false;			// y軸進行方向反転フラグ
		enemy[i].movePattern = 0;
	}
	enemyAllDeadFlag = false;
}

//更新
void UpdetaEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].flag == true)
		{
			//移動
			MoveEnemy(i);// 敵の移動制御
			//弾の当たり判定
			if ((shot.pos.x < enemy[i].pos.x + enemy[i].size.x
				&& enemy[i].pos.x < shot.pos.x + shot.size.x
				&& shot.pos.y < enemy[i].pos.y + enemy[i].size.y
				&& enemy[i].pos.y < shot.pos.y + shot.size.y))
			{
				shot.flag = false;
				enemy[i].flag = false;
				enemy[i].changeFlag = true;
				shot.pos.x = player.pos.x;
				shot.pos.y = player.pos.y;
				//クリア判定
				if (enemy[i].flag == false)
				{
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
						//
						enemy[i].type = enemy[i].type + stageID;
						
					}
				}
			}
		}

		else
		{
			if (enemy[i].changeFlag)
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
		
		if (enemy[i].flag == true)
		{
			switch (enemy[i].div)
			{
			case DIV_RAHGT:
				enemy[i].count++;	
				//エネミータイプにステージを足す
					DrawGraph(enemy[i].pos.x, enemy[i].pos.y,
						enemyImage[enemy[i].type + stageID][enemy[i].count / 50 % 2], true);
				break;
			case DIV_LEFT:
				enemy[i].count++;			
					DrawTurnGraph(enemy[i].pos.x,enemy[i].pos.y,
						enemyImage[enemy[i].type + stageID][enemy[i].count / 50 % 2], true);
				break;
			default:
				break;
			}
		
			/*DrawGraph(enemy[i].pos.x - enemy[i].offSet.x, enemy[i].pos.y - enemy[i].offSet.y,
				enemyImage[enemy[i].type][enemy[i].count / 50 % 2], true);*/
			//DrawCircle(enemy[i].pos.x, enemy[i].pos.y, 2, 0xffff00, true);
		}
		//DrawFormatString(0, 100 + i * 18, 0xff0000, "x:%d", enemy[i].pos.x);
		//DrawFormatString(50, 100 + i * 18, 0xff0000, "y:%d", enemy[i].pos.y);
		//DrawFormatString(100, 100 + i * 18, 0xff0000, "flag:%d", enemy[i].refrectFlag);
		//DrawFormatString(150, 100 + i * 18, 0xff0000, "ptn:%d", enemy[i].movePattern);
		DrawIkayaki(i);
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


