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
#include "box.h"
#include "kaigara.h"
#include"Unti.h"
#include"shot.h"
#include"map.h"

int playerImage[2];
int playerdamageImage;
int damageCnt;
CHARACTER player;

//���[�h
void SysInitPlayer()
{
	LoadDivGraph("bmp/�������A�j���[�V����.png", 2, 2, 1, 32, 32, playerImage);
	playerdamageImage = LoadGraph("bmp/�v���C���[�_���[�W.png");
}
//������
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
	damageCnt = 0;
}

//�X�V
void UpdetaPlayer()
{
	//�ړ�
	if (newKey[P1_RIGHT])
	{
		player.pos.x += player.speed.x;
		player.div = DIV_LEFT;
	}
	if (newKey[P1_LEFT])
	{
		player.pos.x -= player.speed.x;
		player.div = DIV_RAHGT;
	}
	if (newKey[P1_UP])
	{
		player.pos.y -= player.speed.y;
	}
	if (newKey[P1_DOWN])
	{
		player.pos.y += player.speed.y;
	}

	//�ړ�����
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
		if (enemy[i].flag && !player.damageflag)				// �����ǉ�
		{
			if (HitCheckRectToRect(player, i, enemy))		// ��`�Ƌ�`�̓����蔻��
			{
				player.flag = false;
				player.damageflag = true;
				damageCnt = 0;
				enemy[i].flag = false;

				player.hp -= TIME_FRAME * 10;

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
					if (HitBox(player, box))//�����ŃX�e�[�W�؂�ւ�������
					{
						enemyAllDeadFlag = true;
					}
					//enemyAllDeadFlag = true;
				}
			}
		}
	}

	if (player.hp / TIME_FRAME <= 0)
	{
		gamemode = GMODE_OVER;
	}

	if (player.damageflag)
	{
		if (damageCnt > TIME_FRAME * 2)
		{
			player.flag = true;
			player.damageflag = false;
		}
		damageCnt++;
	}

	if (gamemode == GMODE_OVER)
	{
		player.flag = false;
		for (int i = 0; i < ENEMY_MAX;i++)
		{
			enemy[i].flag = false;
		}
		StopSoundMem(UntiSound);
		StopSoundMem(Sound);
		StopSoundMem(ShotSound);
		StopSoundMem(ChngSound);
		PlaySoundMem(OverSound, DX_PLAYTYPE_LOOP);//�T�E���h
		stageID = STAGE1;//����������
	}
	player.hp--;
	player.count++;
	UpdetaShell(player);
}

//�`��
void DrawPlayer()
{
	switch (player.div)
	{
	case DIV_RAHGT:
			player.count++;
			if (!player.damageflag)		// flag��true�̎��ɕ`��
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
			if (!player.damageflag)		// flag��true�̎��ɕ`��
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

	//player.damageflag = false;
	DrawFormatString(30, 30, 0xff0000, "%d", player.hp / TIME_FRAME, true);
	DrawFormatString(30, 50, 0xff0000, "cnt:%d", damageCnt);
	DrawFormatString(30, 70, 0xff0000, "flag:%d", player.damageflag);

	// �����蔻��̉���
	DrawBox(player.pos.x - player.offSet.x,
		player.pos.y - player.offSet.y,
		player.pos.x + player.offSet.x,
		player.pos.y + player.offSet.y, 0x000000, false);
	DrawCircle(player.pos.x, player.pos.y, player.r, 0x000000, false);
	DrawBox(0, 440, player.hp / 60, 450 , 0xff0000, true);
	DrawBox(0, 440, player.hp / 60, 450, 0x000000, false);
}