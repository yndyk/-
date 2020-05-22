#include "main.h"
#include "box.h"
#include "hitCheck.h"
#include "player.h"
#include"enemy.h"
#include <math.h>

CHARACTER box;
//ロード
void SysInitBox()
{
	
}
//初期化
void InitBox() 
{
	box.pos = { 320,400 };
	box.size = { 64,64 };
	box.offSet = { box.size.x / 2,box.size.y / 2 };
	box.flag = false;
}
//当たり判定
bool HitBox(CHARACTER a, CHARACTER b )
{		
	XY distance;		// 当たらない最小距離
	bool hitFlag = false;	// ヒット判定用
	distance.x = abs(a.offSet.x + b.offSet.x);
	distance.y = abs(a.offSet.y + b.offSet.y);
	if (abs(a.pos.x - b.pos.x) < distance.x &&			// 中心間距離が最小距離以下になったら当たった
		abs(a.pos.y - b.pos.y) < distance.y)
	{
		hitFlag = true;
	}
	return hitFlag;

}

//描画
void DrawBox()
{
	DrawBox(box.pos.x - box.offSet.x,
		box.pos.y - box.offSet.y,
		box.pos.x + box.offSet.x,
		box.pos.y + box.offSet.y, 0x000000, false);
}

