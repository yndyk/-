#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "awa.h"
#include "player.h"

CHARACTER bubble;

int bubbleImage;
int bubbleCnt;	// ���݉�ʏ�ɕ\������Ă���A�̐�
int randNum;	// �����i�[�p�ϐ�
int cnt;

void SysInitBubble()
{
	bubbleImage = LoadGraph("bmp/awa.png");
}

void InitBubble()
{
	bubble.size = { 26, 26 };
	bubble.pos = { 64 + rand() % 18 + 1 * 32, SCREEN_SIZE_Y + 32 };
	bubble.speed = 1;
	bubble.hp = 20;			// �A�ɂ��񕜂��郉�C�t�̗�
	bubble.flag = false;	// �\�����邩���Ȃ���
	cnt = 0;				// ���t���[�����Z�����J�E���g
	bubbleCnt = 0;			// ���݉�ʏ�ɕ\������Ă���A�̐�
	randNum = 0;

}

void UpdetaBuble()
{
	srand(time(NULL));
	cnt++;
	if (cnt % 120 == 0)
	{
		bubble.flag = true;
	}

	if (bubble.flag == true)
	{

		if (bubbleCnt <= BUBBLE_MAX)
		{
			if (bubble.count % 120 == 0)
			{
				bubble.flag = true;
			}
		}

		if (bubble.flag == true)
		{

			bubble.pos.y -= bubble.speed;

			if (bubble.pos.y + 32 < 0)
			{
				bubble.flag = false;
				bubble.pos = { 64 + (rand() % 18 + 1) * 32, SCREEN_SIZE_Y + 32 };
			}
		}
		else
		{
			bubble.flag = true;
		}

		if (bubble.pos.y + 32 < 0)
		{
			bubble.flag = false;
			bubble.pos = { 64 + (rand() % 18 + 1) * 32, SCREEN_SIZE_Y + 32 };
		}
		else
		{
			bubble.count = 0;

			if (bubble.count % 180 == 0)
			{
				bubble.pos = { 64 + (rand() % 18 + 1) * 32, SCREEN_SIZE_Y + 32 };
				bubble.flag = true;
			}
		}
	}
}

void DrawBuble()
{
	if (bubble.flag == true)
	{
		DrawGraph(bubble.pos.x, bubble.pos.y, bubbleImage, true);
	}
	//DrawFormatString(0, 50, 0xff0000, "cnt:%d", bubble.count);
	//DrawFormatString(0, 120, 0xff0000, "y:%d", bubble.pos.y);
	//DrawFormatString(70, 120, 0xff0000, "x:%d", bubble.pos.x);
	//DrawFormatString(140, 120, 0xff0000, "flag:%d", bubble.flag);
}


void HitCheckBubble()
{
	if (bubble.flag == true) 
	{
		if (player.pos.x < bubble.pos.x + bubble.size.x &&
			player.pos.x + player.size.x > bubble.pos.x &&
			player.pos.y < bubble.pos.y + bubble.size.y &&
			player.pos.y + player.size.y > bubble.pos.y) 
		{
			bubble.flag = false;

			if (player.hp < PLAYER_HP_MAX) 
			{
				player.hp = player.hp + bubble.hp;
			}
			if (player.hp + bubble.hp >= PLAYER_HP_MAX) 
			{
				player.hp = PLAYER_HP_MAX;
			}
		}
	}
}
