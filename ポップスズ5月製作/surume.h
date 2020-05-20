#pragma once
#define SURUME_MAX 9

extern CHARACTER surume[SURUME_MAX];

void SysInitSurume();
void InitSurume();
void UpdetaSurume(XY pos, bool flag, int num);
void DrawSurume(int num);
void DeleteSurume();