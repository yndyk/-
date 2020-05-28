//#pragma once

enum KEY_MODE {
	P1_UP,
	P1_RIGHT,
	P1_DOWN,
	P1_LEFT,
	P1_SHOT,
	P1_B,

	START,
	PAUSE,
	
	QUIT,

	KEY_MAX
};

// ¸ŞÛ°ÊŞÙ•Ï”
extern bool newKey[KEY_MAX];
extern bool trgKey[KEY_MAX];
extern bool upKey[KEY_MAX];
//extern bool oldKey[KEY_MAX];

// ÌßÛÄÀ²ÌßéŒ¾
void KeyCheckSystemInit(void);
void KeyCheck(void);
