//-----------------------------------------------------
// 
// “G‚ÌˆÚ“®—pŠÖ”MoveEnemy(int)‚Ì’Ç‰Á
// ˆÚ“®•ûŒü‚ğ”½“]‚³‚¹‚éŠÖ”RefrectMoveXY(int)‚Ì’Ç‰Á
// 
//-----------------------------------------------------

#pragma once
#define ENEMY_MAX 9
#define ENEMY_TYPE_MAX 3
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
