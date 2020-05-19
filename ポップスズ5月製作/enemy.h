//-----------------------------------------------------
// 
// 敵の移動用関数MoveEnemy(int)の追加
// 移動方向を反転させる関数RefrectMoveXY(int)の追加
// 
//-----------------------------------------------------

#pragma once
#define ENEMY_MAX 9
#define ENEMY_TYPE_MAX 3
extern CHARACTER enemy[ENEMY_MAX];
extern bool enemyAllDeadFlag;
extern TYPE_MODE enemyType;


void SysInitEnemy();
void InitEnemy();
void UpdetaEnemy();
void DrawEnemy();
void MoveEnemy(int);
void RefrectMoveXY(int);
void TypeEnemy();
