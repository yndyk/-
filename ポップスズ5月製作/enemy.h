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
