#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"main.h"
#include"player.h"
#include"same.h"
#include"hitCheck.h"
#include"unti.h"
#include"enemy.h"
#include"shot.h"

CHARACTER same;
int SameCount;
int SameImage[2];

//���[�h
void SysInitSame()
{  
	LoadDivGraph("bmp/shark.png", 2, 2, 1, 96, 64, SameImage, true);
}

//������
void InitSame()
{
	same.pos = { 0 - 96 * 3 , 64 + rand() % 18 + 1 * 32 };
	same.size = { 96,64 };
	same.speed = {4,4};
	same.offSet = { same.size.x / 2,same.size.y / 2 };
	same.hp -= TIME_FRAME  * 30;
	same.flag = false;
	SameCount = 0;
}

//�X�V
void UpdetaSame()
{
	srand(time(NULL));
	SameCount++;
	ApprSame();
	//�ړ�
	if (same.flag == true) 
	{
		same.pos.x += same.speed.x;
		if (same.pos.x + same.size.x < 0)
		{
			same.flag = false;
			same.pos = { 0 + 96 ,64 + (rand() % 18 + 1) * 32 };
		}
	}

	if(same.pos.x > SCREEN_SIZE_X)
	{
		same.flag = false;
	}
	
	if (!player.damageflag && same.flag)
	{
		if (HitCheck(player, same))
		{
			player.damageflag = true;
			player.flag = false;
			same.flag = false;
			if (player.hp <= 0)
			{
			same.flag = false;
			}
			else if (player.hp > 0)
			{
				player.hp -= 40 * TIME_FRAME;
			}
		}
	}
	else
	{
		player.flag = true;
	}

}

//�`��
void DrawSame()
{
	if (same.flag == true)
	{
		DrawBox(same.pos.x - same.offSet.x, same.pos.y - same.offSet.y,
			same.pos.x + same.offSet.x, same.pos.y + same.offSet.y,
			0xff0000, false);

		DrawGraph(same.pos.x - same.offSet.x,
			same.pos.y - same.offSet.y, 
			SameImage[0], true);
	}
	else
	{
		DrawGraph(same.pos.x - same.offSet.x,
			same.pos.y - same.offSet.y,
			SameImage[1], true);
	}
	DrawFormatString(0, 250, 0xff0000, "%d",SameCount, true);
}
//�o������
void ApprSame()
{
	if (SameCount % 120 == 0) 
	{
		if (same.flag == false)
		{
			same.flag = true;
			same.pos = { 0 + 96, 64 + (rand() % 18 + 1) * 32 };
		}
	}
}