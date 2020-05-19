//-----------------------------------------------------
// 
// 
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
void DamageEnemy();