//-----------------------------------------------------
// 
// 1:1の当たり判定処理の追加
// 
// 
// 
//-----------------------------------------------------

#pragma once

// 1：複数の当たり判定
bool HitCheckRectToRect(CHARACTER, int, CHARACTER*);
bool HitCheckRectToCircle(CHARACTER, int, CHARACTER*);
bool HitCheckCircleToCircle(CHARACTER, int, CHARACTER*);

// 複数：複数の当たり判定
bool HitCheckShotToEnemy(CHARACTER*, int, CHARACTER*, int);

// 1：1の当たり判定
bool HitCheck(CHARACTER, CHARACTER);
