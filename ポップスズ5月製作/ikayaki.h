//-------------------------------
// 
// 関数HitCheckIkayaki()に引数intを追加しました
//
//-------------------------------

#pragma once
#define IKAYAKI_MAX 9

extern CHARACTER ikayaki[IKAYAKI_MAX];


void SysInitIkayaki();
void InitIkayaki();
void UpdateIkayaki(XY, bool, int);
void DrawIkayaki(int);
void HitCheckIkayaki(int);
void DeleteIkayaki();