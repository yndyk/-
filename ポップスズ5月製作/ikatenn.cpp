#include "main.h"
#include "ikatenn.h"
#include "player.h"
#include "hitCheck.h"
#include"enemy.h"
#include "score.h"

CHARACTER ikatenn[IKATENN_MAX];
int ikatennImage;
//���[�h
void SysInitIkatenn()
{
	ikatennImage = LoadGraph("bmp/�C�J�V.png");
}
//������
void InitIkatenn() 
{
	for(int i = 0; i < IKATENN_MAX;i++)
	{
		ikatenn[i].pos = { 0, 0 };
		ikatenn[i].speed = { 1,1 };
		ikatenn[i].count = 0;
		ikatenn[i].flag = false;
		ikatenn[i].size = { 32, 32 };
		ikatenn[i].offSet = { ikatenn[i].size.x / 2, ikatenn[i].size.y / 2 };
		ikatenn[i].hp = 30;		// �C�J�V�擾���ɉ񕜂��郉�C�t�̗�
		ikatenn[i].onlyOnce = false;
	}
}

//�X�V
void UpdateIkatenn(XY pos, bool flag, int num)
{
	if (!ikatenn[num].onlyOnce)
	{
		if (!ikatenn[num].flag)
		{
			ikatenn[num].pos = pos;
			ikatenn[num].flag = flag;
			ikatenn[num].onlyOnce = true;
		}
	}


	if (ikatenn[num].flag)
	{
		ikatenn[num].pos.y += ikatenn[num].speed.y;
		PlaySoundMem(ChngSound, DX_PLAYTYPE_BACK);//�T�E���h
		if (ikatenn[num].pos.y > SCREEN_SIZE_Y)
		{
			ikatenn[num].flag = false;
			
		}

		if (HitCheckRectToRect(player, num, ikatenn))		// ��`�Ƌ�`�̓����蔻��
		{
			ikatenn[num].flag = false;
			if (player.hp + ikatenn[num].hp < TIME_FRAME * PLAYER_HP_MAX)
			{
				player.hp = player.hp + ikatenn[num].hp;
			}
			if (player.hp + ikatenn[num].hp >= TIME_FRAME * PLAYER_HP_MAX)
			{
				player.hp = TIME_FRAME * PLAYER_HP_MAX;
			}
			//enemyScore += 300;
			SetScore(SCORE, 300);//�X�R�A���Z
			
		}
		
	}
}

//�`��
void DrawIkatenn(int num)
{
	if (ikatenn[num].flag)
	{
		DrawGraph(ikatenn[num].pos.x - ikatenn[num].offSet.x,
			ikatenn[num].pos.y - ikatenn[num].offSet.y,
			ikatennImage, true);
		// �����蔻��̉���
		DrawBox(ikatenn[num].pos.x - ikatenn[num].offSet.x,
			ikatenn[num].pos.y - ikatenn[num].offSet.y,
			ikatenn[num].pos.x + ikatenn[num].offSet.x,
			ikatenn[num].pos.y + ikatenn[num].offSet.y,
			0x000000, false);
		
	}
}

void DeleteIkatenn()
{
	for (int i = 0; i < IKATENN_MAX; i++)
	{
		ikatenn[i].flag = false;
	}
}