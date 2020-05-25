//-------------------------------
//
// �����蔻��̉���
// HitCheckIkayaki()�̍폜
//
//-------------------------------

#include "main.h"
#include "ikayaki.h"
#include "player.h"
#include "hitCheck.h"
#include"enemy.h"
#include "score.h"

int ikayakiImage;

CHARACTER ikayaki[IKAYAKI_MAX];

void SysInitIkayaki()
{
	ikayakiImage = LoadGraph("bmp/�C�J�Ă�.png");
	
}

void InitIkayaki()
{
	for (int i = 0; i < IKAYAKI_MAX; i++)
	{
		ikayaki[i].pos = { 0, 0 };
		ikayaki[i].speed = { 1,1 };
		ikayaki[i].count = 0;
		ikayaki[i].flag = false;
		ikayaki[i].size = { 32, 32 };
		ikayaki[i].offSet = { ikayaki[i].size.x / 2, ikayaki[i].size.y / 2 };
		ikayaki[i].hp = 30;		// �C�J�Ă��擾���ɉ񕜂��郉�C�t�̗�
		ikayaki[i].onlyOnce = false;
	}
}

void UpdateIkayaki(XY pos,bool flag, int num)	// pos:���W�@flag:�t���O�@num:�z��ԍ�
{
	if (!ikayaki[num].onlyOnce)
	{
		if (!ikayaki[num].flag)
		{
			ikayaki[num].pos = pos;
			ikayaki[num].flag = flag;
			ikayaki[num].onlyOnce = true;
		}
	}

		
	if (ikayaki[num].flag)
	{
		ikayaki[num].pos.y += ikayaki[num].speed.y;

		if (ikayaki[num].pos.y > SCREEN_SIZE_Y)
		{
			ikayaki[num].flag = false;
		}

		if (HitCheckRectToRect(player, num, ikayaki))		// ��`�Ƌ�`�̓����蔻��
		{
			ikayaki[num].flag = false;
			if (player.hp + ikayaki[num].hp < TIME_FRAME * PLAYER_HP_MAX)
			{
				player.hp = player.hp + ikayaki[num].hp;
			}
			if (player.hp + ikayaki[num].hp >= TIME_FRAME * PLAYER_HP_MAX)
			{
				player.hp = TIME_FRAME * PLAYER_HP_MAX;
			}
			//enemyScore += 300;
			SetScore(SCORE, 300);//�X�R�A���Z
			
		}
		PlaySoundMem(ChngSound, DX_PLAYTYPE_LOOP);//�T�E���h
	}
}

void DrawIkayaki(int num)
{
	if (ikayaki[num].flag)
	{
		DrawGraph(ikayaki[num].pos.x - ikayaki[num].offSet.x,
				  ikayaki[num].pos.y - ikayaki[num].offSet.y,
				  ikayakiImage, true);
		// �����蔻��̉���
		DrawBox(ikayaki[num].pos.x - ikayaki[num].offSet.x,
			ikayaki[num].pos.y - ikayaki[num].offSet.y,
			ikayaki[num].pos.x + ikayaki[num].offSet.x,
			ikayaki[num].pos.y + ikayaki[num].offSet.y,
			0x000000, false);
		
	}

	

	//DrawFormatString(0, 100 + num * 18, 0xff0000, "f;%d", ikayaki[num].flag);
	//DrawFormatString(50, 100 + num * 18, 0xff0000, "x:%d", ikayaki[num].pos.x);
	//DrawFormatString(100, 100 + num * 18, 0xff0000, "y:%d", ikayaki[num].pos.y);
	//DrawFormatString(150, 100 + num * 18, 0xff0000, "num;%d", num);
}

void DeleteIkayaki()
{
	for (int i = 0; i < IKAYAKI_MAX; i++)
	{
		ikayaki[i].flag = false;
		
	}
}
