//-----------------------------------------------------
// 
// enemy[i].flag���o������true�A���j����false�ɕύX
// 
//-----------------------------------------------------

#include "main.h"
#include"keycheck.h"
#include"enemy.h"
#include"player.h"
#include"shot.h"
#include "ikayaki.h"

int enemyImage[2];
int enemyImage2[2];
int enemyImage3[2];
int enemyType;
int enemyType2;
int enemyType3;
CHARACTER enemy[ENEMY_MAX];
bool enemyAllDeadFlag;

//���[�h
void SysInitEnemy()
{
	LoadDivGraph("bmp/�C�J�v���[��.png", 2, 2, 1, 32, 32, enemyImage, true);
	LoadDivGraph("bmp/�C�J���J.png", 2, 2, 1, 32, 32, enemyImage2, true);
  	LoadDivGraph("bmp/�����C�J.png", 2, 2, 1, 32, 64, enemyImage3, true);
	enemyType = false;
	enemyType2 = false;
	enemyType3 = false;
}

//������
void InitEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy[i].pos = { 50 + i * 50,GetRand(20 + i * 50) };
		enemy[i].speed = 2;
		enemy[i].count = 0;
		enemy[i].flag = true;
		enemy[i].point = 0;
		enemy[i].size = { 32,32 };
		enemy[i].changeFlag = false;
		enemy[i].div = DIV_RAHGT;
	}
	
	enemyAllDeadFlag = false;
}
//�X�V
void UpdetaEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].flag == true)
		{
			//�ړ�
			enemy[i].pos.x += enemy[i].speed;
			//�ړ�����
			if (enemy[i].pos.x > 590)
			{
				enemy[i].speed = -enemy[i].speed;
				enemy[i].div = DIV_LEFT;
			}

			if (enemy[i].pos.x < 50)
			{
				enemy[i].speed = -enemy[i].speed;
				enemy[i].div = DIV_RAHGT;
			}

			//�e�̓����蔻��
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
				//�N���A����
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
						enemyType = true;//�G�l�~�[�^�C�v1
						if (enemyType == true) 
						{
							enemyType2 = true;//�G�l�~�[�^�C�v2
						}
						if(enemyType2 == false)
						{
							enemyType3 = true;//�G�l�~�[�^�C�v3
						}
						//gamemode = GMODE_CLERA;
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
//�`��
void DrawEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].flag == true) 
		{
			switch (enemy[i].div)
			{
			case DIV_RAHGT:
				enemy[i].count++;
				if (enemyType == false) 
				{
					DrawGraph(enemy[i].pos.x, enemy[i].pos.y, enemyImage2[enemy[i].count / 50 % 2], true);
				}
				if (enemyType2 == true)
				{
					DrawGraph(enemy[i].pos.x, enemy[i].pos.y, enemyImage[enemy[i].count / 50 % 2], true);
				}
				if (enemyType3 == true)
				{
					DrawGraph(enemy[i].pos.x, enemy[i].pos.y, enemyImage3[enemy[i].count / 50 % 2], true);
				}
				break;
			case DIV_LEFT:
				enemy[i].count++;
				if (enemyType == false)
				{
					DrawTurnGraph(enemy[i].pos.x, enemy[i].pos.y, enemyImage2[enemy[i].count / 50 % 2], true);
				}
				if (enemyType2 == true)
				{
					DrawTurnGraph(enemy[i].pos.x, enemy[i].pos.y, enemyImage[enemy[i].count / 50 % 2], true);
				}
				if (enemyType3 == true)
				{
					DrawTurnGraph(enemy[i].pos.x, enemy[i].pos.y, enemyImage3[enemy[i].count / 50 % 2], true);
				}
				break;
			default:
				break;
			}
			/*enemy[i].count++;
			DrawGraph(enemy[i].pos.x, enemy[i].pos.y, enemyImage[enemy[i].count / 50 % 2], true);	
			DrawGraph(enemy[i].pos.x, enemy[i].pos.y, enemyImage2[enemy[i].count / 50 % 2], true);*/
			
		}
		//DrawFormatString(0, 100 + i * 18, 0xff0000, "x:%d", enemy[i].pos.x);
		//DrawFormatString(50, 100 + i * 18, 0xff0000, "y:%d", enemy[i].pos.y);
		//DrawFormatString(100, 100 + i * 18, 0xff0000, "flag:%d", enemy[i].flag);
		//DrawFormatString(150, 100+i*18, 0xff0000, "point:%d", enemy[i].point);
		DrawIkayaki(i);
	}
	/*DrawFormatString(30, 30, 0xffff00, "%d", enemy[0].point, true);
	DrawFormatString(30, 40, 0xffff00, "%d", enemy[1].point, true);
	DrawFormatString(30, 50, 0xffff00, "%d", enemy[2].point, true);
	DrawFormatString(30, 60, 0xffff00, "%d", enemy[3].point, true);
	DrawFormatString(30, 70, 0xffff00, "%d", enemy[4].point, true);
	DrawFormatString(30, 80, 0xffff00, "%d", enemy[5].point, true);*/
}


