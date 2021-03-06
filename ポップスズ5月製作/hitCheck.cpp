//-----------------------------------------------------
// 
// 1:1の当たり判定処理の追加
// 
//-----------------------------------------------------

#include <math.h>
#include "main.h"
#include "hitCheck.h"

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

bool HitCheckShotToEnemy(CHARACTER *a, int num1, CHARACTER *b, int num2)
{
	XY distance;		// 当たらない最小距離
	bool hitFlag = false;	// ヒット判定用
	distance.x = abs(a[num1].offSet.x + b[num2].offSet.x);
	distance.y = abs(a[num1].offSet.y + b[num2].offSet.y);
	if (abs(a[num1].pos.x - b[num2].pos.x) < distance.x &&			// 中心間距離が最小距離以下になったら当たった
		abs(a[num1].pos.y - b[num2].pos.y) < distance.y)
	{
		hitFlag = true;
	}
	return hitFlag;
}

bool HitCheck(CHARACTER a, CHARACTER b)
{
	XY distance;		// 当たらない最小距離
	bool hitFlag = false;	// ヒット判定用
	distance.x = abs(a.offSet.x + b.offSet.x);
	distance.y = abs(a.offSet.y + b.offSet.y);
	if (abs(a.pos.x - b.pos.x) < distance.x &&	// 中心間距離が最小距離以下になったら当たった
		abs(a.pos.y - b.pos.y) < distance.y)
	{
		hitFlag = true;
	}
	return hitFlag;
}
