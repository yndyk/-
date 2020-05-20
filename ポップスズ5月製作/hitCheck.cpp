//-----------------------------------------------------
// HitCheckCircleToCircle()内の
// 
//-----------------------------------------------------

#include <math.h>
#include "main.h"

bool HitCheckRectToRect(CHARACTER a, int num, CHARACTER* b)
{
	XY distance;		// 当たらない最小距離
	bool hitFlag = false;	// ヒット判定用
	distance.x = abs(a.offSet.x + b[num].offSet.x);
	distance.y = abs(a.offSet.y + b[num].offSet.y);
	if (abs(a.pos.x - b[num].pos.x) < distance.x &&			// 中心間距離が最小距離以下になったら当たった
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
	float distance;			// 中心間距離
	float minDistance = a.r + b[num].r;		// 当たらない最小中心間距離
	bool hitFlag = false;
	XY_F length = { fabsf(a.pos.x - b[num].pos.x), fabsf(a.pos.y - b[num].pos.y) };			// 中心間距離のX,Y成分
	distance = sqrtf(length.x * length.x + length.y * length.y);
	if (minDistance > distance)
	{
		hitFlag = true;
	}
	return hitFlag;
}
