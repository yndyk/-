#pragma once

#define IKATENN_MAX 9

extern CHARACTER ikatenn[IKATENN_MAX];

void SysInitIkatenn();
void InitIkatenn();
void UpdateIkatenn(XY pos, bool flag, int num);
void DrawIkatenn(int num);
void DeleteIkatenn();