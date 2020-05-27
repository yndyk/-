//-------------------------------------
//
// �����蔻��̉���
// 
//
//-----------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "player.h"
#include "unti.h"
#include "hitCheck.h"

int UntiImage;
CHARACTER unti[UNTI_MAX];
int Untinum;
int UntiCount;
int UntiSound;

//���[�h
void SysinitUnti()
{
	UntiImage = LoadGraph("bmp/�E���R.png");
}

//������
void initUnti()
{
	for (int i = 0; i < UNTI_MAX;++i) 
	{
		unti[i].pos = { 64 + rand() % 18 + 1 * 32, 0 - 32 * 3 };
		unti[i].size = { UNTI_SIZE_X,UNTI_SIZE_Y };
		unti[i].offSet = { unti[i].size.x / 2, unti[i].size.y / 2 };
		unti[i].flag = false;
		unti[i].speed = { 6,6 };
		unti[i].count = false;
		unti[i].hp = TIME_FRAME * 20;
	}
	UntiCount = 0;
	Untinum = 0;
	UntiSound = LoadSoundMem("���f��/�E���`.mp3");
}


//�X�V
void UpdetaUnti()
{
	srand(time(NULL));
	UntiCount++;
		//�E���`�̃����_���o��
	ApperUnti();
	for (int i = 0; i < UNTI_MAX; i++)
	{
		if (unti[i].flag)
		{
			unti[i].pos.y += unti[i].speed.y;

			if (unti[i].pos.y + unti[i].size.y < 0)
			{
				unti[i].flag = false;
				unti[i].pos = { 64 + (rand() % 18 + 1) * 32, 0 + 32 };
			}
			StopSoundMem(UntiSound);
		}

		if(unti[i].pos.y > SCREEN_SIZE_Y)
		{
			unti[i].flag = false;
		}
	}

	for (int i = 0; i < UNTI_MAX; i++)
	{
		//�����蔻��
		if (player.flag && unti[i].flag)
		{
			if (HitCheckRectToRect(player, i, unti))		// ��`�Ƌ�`�̓����蔻��
			{
				unti[i].flag = false;
				player.damageflag = true;
				player.flag = false;
				if(player.hp <= 0)
				{
					unti[i].flag = false;
				}
				else if(player.hp > 0)
				{
					player.hp -= 10 * TIME_FRAME;
				}
				PlaySoundMem(UntiSound, DX_PLAYTYPE_BACK);
			}
		}
		else
		{
			player.flag = true;			// �Ƃ肠�����̏���(�E���`�����������Ƃ��Ƀv���C���[���\������Ȃ��Ȃ�o�O������������)
		}
	}
}

//�`��
void DrawUnti()
{
	for (int i = 0; i < UNTI_MAX; i++) 
	{
		if (unti[i].flag == true)
		{
			DrawGraph(unti[i].pos.x - unti[i].offSet.x,
				unti[i].pos.y - unti[i].offSet.y,
				UntiImage, true);
			//DrawFormatString(30, 60, 0xff0000, "%d", UntiCount, true);
			// �����蔻��̉���
			DrawBox(unti[i].pos.x - unti[i].offSet.x,
				unti[i].pos.y - unti[i].offSet.y,
				unti[i].pos.x + unti[i].offSet.x,
				unti[i].pos.y + unti[i].offSet.y,
				0x000000, false);
		}

		
		/*DrawFormatString(0, 50, 0xff0000, "UntiCount:%d", UntiCount);
		DrawFormatString(0, 120 + i * 18, 0xff0000, "y:%d", unti[i].pos.y);
		DrawFormatString(70, 120 + i * 18, 0xff0000, "x:%d", unti[i].pos.x);
		DrawFormatString(140, 120 + i * 18, 0xff0000, "flag:%d", unti[i].flag);*/
	}
}

void DeleteUnti()
{
	for (int i = 0; i < UNTI_MAX; i++) 
	{
		if (unti[i].flag) 
		{
			UntiCount = 0;
			unti[i].flag = false;
			Untinum++;
		}
	}
}

void ApperUnti()
{
	if (UntiCount % 120 == 0)
	{
		for (int i = 0; i < UNTI_MAX; i++)
		{
			if (unti[i].flag == false)
			{
				unti[i].flag = true;
				unti[i].pos = { 64 + (rand() % 18 + 1) * 32, 0 + 32 };
				break;
			}
		}
	}
}