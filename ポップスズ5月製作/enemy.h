#pragma once
#define ENEMY_MAX 9
extern CHARACTER enemy[ENEMY_MAX];
extern bool enemyAllDeadFlag;

void SysInitEnemy();
void InitEnemy();
void UpdetaEnemy();
void DrawEnemy();