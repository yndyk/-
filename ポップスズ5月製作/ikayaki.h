//-------------------------------
// 
// ŠÖ”HitCheckIkayaki()‚Éˆø”int‚ğ’Ç‰Á‚µ‚Ü‚µ‚½
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