/*--------1---------2---------3---------4---------5---------6---------7-------*/
//
//   asoulquest = keycheck.cpp
//
//   2018.07.2     Name
//
/*--------1---------2---------3---------4---------5---------6---------7-------*/
#include <DxLib.h>		//Dxlib���C�u�������g�p����
#include "main.h"
#include "keycheck.h"

bool oldKey[KEY_MAX];
bool newKey[KEY_MAX];
bool trgKey[KEY_MAX];
bool upKey[KEY_MAX];

// ----- �Ƃ肠�����S���ر
void KeyCheckSystemInit()
{
	for (int i = 0; i < KEY_MAX; i++) {
		newKey[i] = false;
		trgKey[i] = false;
		upKey[i] = false;
		oldKey[i] = false;
	}
}

void KeyCheck()
{
	// ----- ������
	for (int i = 0; i < KEY_MAX; i++) {
		newKey[i] = false;	// �S�������Ă��Ȃ����ɂ���
		trgKey[i] = false;	// �S�������Ă��Ȃ����ɂ���
		upKey[i] = false;	// �S�������Ă��Ȃ����ɂ���
	}

	// ----- newKey
	if (CheckHitKey(KEY_INPUT_UP)) newKey[P1_UP] = true;
	if (CheckHitKey(KEY_INPUT_RIGHT)) newKey[P1_RIGHT] = true;
	if (CheckHitKey(KEY_INPUT_DOWN)) newKey[P1_DOWN] = true;
	if (CheckHitKey(KEY_INPUT_LEFT)) newKey[P1_LEFT] = true;
	if (CheckHitKey(KEY_INPUT_RCONTROL)) newKey[P1_A] = true;
	if (CheckHitKey(KEY_INPUT_RCONTROL)) newKey[P1_B] = true;

	if (CheckHitKey(KEY_INPUT_W)) newKey[P2_UP] = true;
	if (CheckHitKey(KEY_INPUT_D)) newKey[P2_RIGHT] = true;
	if (CheckHitKey(KEY_INPUT_S)) newKey[P2_DOWN] = true;
	if (CheckHitKey(KEY_INPUT_A)) newKey[P2_LEFT] = true;
	if (CheckHitKey(KEY_INPUT_LCONTROL)) newKey[P2_A] = true;
	if (CheckHitKey(KEY_INPUT_LCONTROL)) newKey[P2_B] = true;

	if (CheckHitKey(KEY_INPUT_SPACE)) newKey[START] = true;
	if (CheckHitKey(KEY_INPUT_SPACE)) newKey[PAUSE] = true;

	// ----- trgKey & upKey & oldKey
	for (int i = 0; i < KEY_MAX; i++) {
		trgKey[i] = newKey[i] & ~oldKey[i];	// trgKey
		upKey[i] = ~newKey[i] & oldKey[i];	// upKey
		oldKey[i] = newKey[i];	// oldKey
	}
}
