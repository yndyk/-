#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "awa.h"
#include"player.h"

CHARACTER bubble;

int bubbleImage;
int bubbleCnt;
int cnt;

void SysInitBubble()
{
	bubbleImage = LoadGraph("bmp/awa.png");
}

void InitBubble()
{
	bubble.pos = { 64 + rand() % 18 + 1 * 32, SCREEN_SIZE_Y + 32 };
	bubble.speed = 1;
	bubble.hp = 20;			// �A�ɂ��񕜂��郉�C�t�̗�
	bubble.flag = false;	// �\�����邩���Ȃ���

	cnt = 0;				// ���t���[�����Z�����J�E���g
	bubbleCnt = 0;			// ���݉�ʏ�ɕ\������Ă���A�̐�

}

void UpdetaBuble()
{
	srand(time(NULL));

	cnt++;
	if (cnt % 120 == 0) {
		bubble.flag = true;
	}


	if (bubble.flag == true) {
		bubble.pos.y -= bubble.speed;
	}
	else {
		bubble.flag = true;
	}

	if (bubble.pos.y + 32 < 0) {
		bubble.flag = false;
		bubble.pos = { 64 + (rand() % 18 + 1) * 32, SCREEN_SIZE_Y + 32 };
	}


}

void DrawBuble()
{
	if (bubble.flag == true)
		DrawGraph(bubble.pos.x, bubble.pos.y, bubbleImage, true);

	//DrawFormatString(0, 50, 0xff0000, "cnt:%d", cnt);
	//DrawFormatString(0, 120, 0xff0000, "y:%d", bubble.pos.y);
	//DrawFormatString(0, 150, 0xff0000, "x:%d", bubble.pos.x);
}
