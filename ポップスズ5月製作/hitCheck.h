//-----------------------------------------------------
// 
// 各関数のSquareをRectに変更しました
// HitCheckCircleToCircle()の処理を追加しました
// 処理をhitCheck.cppに移行しました
// 
//-----------------------------------------------------

#pragma once

// 1：複数の当たり判定
bool HitCheckRectToRect(CHARACTER, int, CHARACTER*);
bool HitCheckRectToCircle(CHARACTER, int, CHARACTER*);
bool HitCheckCircleToCircle(CHARACTER, int, CHARACTER*);
bool HitCheckShotToEnemy(CHARACTER*, int, CHARACTER*, int);
