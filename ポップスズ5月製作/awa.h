//-----------------------------------------------
// 
// HitCheckBubble()削除
// 
//-----------------------------------------------
#pragma once

#define BUBBLE_MAX 4

extern CHARACTER bubble[BUBBLE_MAX];

void SysInitBubble();
void InitBubble();
void UpdetaBuble();
void DrawBuble();
void BubbleDelete();		// 画面上の泡をすべて消す