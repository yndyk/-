//-----------------------------------------------------
// HitCheckCircleToCircle()����
// 
//-----------------------------------------------------

#include <math.h>
#include "main.h"

bool HitCheckRectToRect(CHARACTER a, int num, CHARACTER* b)
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

bool HitCheckRectToCircle(CHARACTER a, int num, CHARACTER* b)
{

	return false;
}

bool HitCheckCircleToCircle(CHARACTER a, int num, CHARACTER* b)
{
	float distance;			// ���S�ԋ���
	float minDistance = a.r + b[num].r;		// ������Ȃ��ŏ����S�ԋ���
	bool hitFlag = false;
	XY_F length = { fabsf(a.pos.x - b[num].pos.x), fabsf(a.pos.y - b[num].pos.y) };			// ���S�ԋ�����X,Y����
	distance = sqrtf(length.x * length.x + length.y * length.y);
	if (minDistance > distance)
	{
		hitFlag = true;
	}
	return hitFlag;
}
