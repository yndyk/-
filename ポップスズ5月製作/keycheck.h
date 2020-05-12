//#pragma once

enum KEY_MODE {
	P1_UP,
	P1_RIGHT,
	P1_DOWN,
	P1_LEFT,
	P1_A,
	P1_B,

	P2_UP,
	P2_RIGHT,
	P2_DOWN,
	P2_LEFT,
	P2_A,
	P2_B,

	START,
	PAUSE,

	KEY_MAX
};

// ��۰��ٕϐ�
extern bool newKey[KEY_MAX];
extern bool trgKey[KEY_MAX];
extern bool upKey[KEY_MAX];
//extern bool oldKey[KEY_MAX];

// �������ߐ錾
void KeyCheckSystemInit(void);
void KeyCheck(void);
