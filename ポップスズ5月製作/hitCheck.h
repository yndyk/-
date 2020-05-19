#pragma once

#include "main.h"

typedef struct
{
	XY c;		// 中心座標
	float width;	// 幅
	float hight;	// 高さ

}Rect;

bool HitCheckSquareToSquare(CHARACTER, int, CHARACTER*);




bool HitCheckSquareToSquare(CHARACTER a, int num, CHARACTER *b)
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

bool HitCheckCircleToSquare(XY, int, XY, XY)
{
	return false;
}

bool HitCheckCircleToCircle(XY, int, XY, int)
{
	return false;
}
