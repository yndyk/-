//-----------------------------------------------------
// 
// 敵の移動用関数MoveEnemy(int)の追加
// 移動方向を反転させる関数RefrectMoveXY(int)の追加
// 
//-----------------------------------------------------

#pragma once
#define ENEMY_MAX 9
extern CHARACTER enemy[ENEMY_MAX];
extern bool enemyAllDeadFlag;
extern int enemyType;
extern int enemyType2;
extern int enemyType3;

void SysInitEnemy();
void InitEnemy();
void UpdetaEnemy();
void DrawEnemy();
void MoveEnemy(int);
void RefrectMoveXY(int);
