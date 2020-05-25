//-----------------------------------------------------
// 
// CHARACTER�\���̂ɔ��a�p�ϐ�r��ǉ����܂���
// �����̕ύX�ɂ��ϐ��̈Ӗ����ς�����̂ŁA�R�����g��ǉ����܂���
// 
// 
//-----------------------------------------------------

#pragma once
#include "Dxlib.h"

enum GAMEMODE
{
	GMODE_INIT,
	GMODE_MAIN,
	GMODE_TITLE,
	GMODE_CLERA,
	GMODE_OVER
};

enum GAMEDIV
{
	DIV_UP,
	DIV_RAHGT,
	DIV_LEFT,
	DIV_DOWN
};

enum TYPE_MODE
{
	TYPE_1,
	TYPE_2,
	TYPE_3,
	TYPE_MAX
};

typedef struct
{
	int x;
	int y;
}XY;


typedef struct
{
	float x;
	float y;
}XY_F;

typedef struct
{
	XY pos;					// ���S���W
	XY speed;
	int count;
	int point;
	bool flag;				// �`��t���O
	GAMEDIV div;
	XY size;				// �摜�T�C�Y
	XY offSet;				// �I�t�Z�b�g(�摜�̒��S��pos�����炷�p)
	int r;					// ���a
	int type;
	int hp;
	bool damageflag;
	bool changeFlag;		// �摜�؂�ւ��p�ϐ�
	bool onlyOnce;			// 1�x�������s����p�̕ϐ�
	bool refrectFlagX;		// x�����˃t���O
	bool refrectFlagY;		// y�����˃t���O
	int movePattern;		// �ړ��p�^�[��
	int score;				//�X�R�A�ϐ�
}CHARACTER;

#define SCREEN_SIZE_X 640
#define SCREEN_SIZE_Y 480
#define TIME_FRAME 60

#define PI 3.141592
extern GAMEMODE gamemode;
extern int leftTime;
extern int Sound;

//�v���g�^�C�v�錾
void GameInit(void);
bool SystmeInit(void);
void GameTitlr(void);
void GameMain(void);
void GameDraw(void);
void GameClera(void);
void GameOver(void);
bool FadeOutScreen(int fadeStep);
bool FadeinScreen(int fadeStep);

