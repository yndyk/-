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

//���[�h
void SysInitBenemy()
{
	LoadDivGraph("bmp/�A�����i�C�g.png", 2, 2, 1, 32, 32, BenemyImage, true);
	BenemyDamegeImage = LoadGraph("bmp/�A�����i�C�g�_���[�W.png");
	
}

//������
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
	BenemyTime = TIME_FRAME*3;//�_���[�W�̕`�掞��
	BsearchDistance = 96;	// �G�̍��G����(���͈͓̔��ɓ���ƓG�������Ɍ������Ă���) �v�����I
}

//�X�V
void UpdetaBenemy()
{
	//�ړ�
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
				SetScore(SCORE, 600);//�X�R�A���Z
			}		
		}
		if (HitBox(benemy, player))
		{
			benemy.flag = true;
		}
		moveBenemy();//����
	}
	DamegeBenemy();
}

//�`��
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
	DrawFormatString(0, 360, 0xff0000, "�e�X�g;%d", benemy.hp);
}

void DamegeBenemy()
{
	//�_���[�W�󂯂���
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

//�ړ�����
void moveBenemy()
{
	//�ړ�����
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

	// �����ɓG�̈��͈͓��ɓ�������v���C���[�̂ق��Ɉړ����Ă��鏈��������
	length = { (float)(player.pos.x - benemy.pos.x), (float)(player.pos.y - benemy.pos.y) };			// ���S�ԋ�����X,Y����
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
			//�������牺�̏������e��+����|�ɕύX
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

//��܂��ȓ���
void BrefrectMoveXY()
{
	if (benemy.refrectFlagX)
	{
		benemy.speed.x = -1 * benemy.speed.x;
		if (benemy.speed.x < 0)				// ���x�����̎�
			benemy.div = DIV_LEFT;
		if (benemy.speed.x > 0)				// ���x�����̎�
			benemy.div = DIV_RAHGT;
		benemy.refrectFlagX = false;
	}
	if (benemy.refrectFlagY)
	{
		benemy.speed.y = -1 * benemy.speed.y;

		benemy.refrectFlagY = false;
	}
}
