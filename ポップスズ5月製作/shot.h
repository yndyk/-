#pragma once
#define SHOT_MAX 15

extern CHARACTER shot[SHOT_MAX];
extern int ShotSound;

void SysInitShot();
void InitShot();
void UpdetaShot();
void DrawShot();