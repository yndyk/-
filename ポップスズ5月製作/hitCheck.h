#pragma once

#include "main.h"

typedef struct
{
	XY c;		// ���S���W
	float width;	// ��
	float hight;	// ����

}Rect;

bool HitCheckSquareToSquare(CHARACTER, int, CHARACTER*);




bool HitCheckSquareToSquare(CHARACTER a, int num, CHARACTER *b)
{
	XY distance;		// ������Ȃ��ŏ�����
	bool hitFlag = false;	// �q�b�g����p
	distance.x = abs(a.offSet.x + b[num].offSet.x);
	distance.y = abs(a.offSet.y + b[num].offSet.y);
	if (abs(a.pos.x - b[num].pos.x) < distance.x &&			// ���S�ԋ������ŏ������ȉ��ɂȂ����瓖������
		abs(a.pos.y - b[num].pos.y) < distance.y)
	{
		hitFlag = true;
	}
	return hitFlag;
}

bool HitCheckCircleToSquare(XY, int, XY, XY)
{
	return false;
}

bool HitCheckCircleToCircle(XY, int, XY, int)
{
	return false;
}
