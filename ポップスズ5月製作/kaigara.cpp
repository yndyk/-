#include "main.h"
#include "kaigara.h"
#include "player.h"
#include "hitCheck.h"

CHARACTER shell[SHELL_MAX];
int shellImage;
int shellCnt;		// ŠL‚ªo‚½‰ñ”


void SysInitShell()
{
	shellImage = LoadGraph("bmp/kaigara.png");
}

void InitShell()
{
	for (int i = 0; i < SHELL_MAX; i++)
	{
		shell[i].pos = { 0, 0 };
		shell[i].flag = false;
		shell[i].hp = 5;
		shell[i].size = { 34, 32 };
		shell[i].speed = { 1, 1 };
		shell[i].changeFlag = false;
	}
	shellCnt = 0;
}

void UpdetaShell(CHARACTER p)
{
	for (int i = 0; i < SHELL_MAX; i++)
	{
		if (!shell[i].flag)
		{
			if (p.hp < PLAYER_HP_MAX * TIME_FRAME / 2 || p.hp < PLAYER_HP_MAX * TIME_FRAME / 3)
			{
				shell[i].pos = { 64 + rand() % 18 + 1 * 32, SCREEN_SIZE_Y - 32 * 3 };
				//shell[i].flag = true;
				shellCnt++;
			}
		}
		else
		{
			if (HitCheckRectToRect(p, i, shell))
			{
				if (shell[i].hp <= 0)
				{
					//ˆ—“à—e
					shell[i].changeFlag = true;
					shell[i].flag = false;
				}
				shell[i].hp--;
			}
		}
	}
}

void DrawShell()
{
	for (int i = 0; i < SHELL_MAX; i++)
	{
		if (shell[i].flag)
		{
			DrawGraph(shell[i].pos.x, shell[i].pos.y, shellImage, true);
		}
	}
}

void MoveShell(int)
{
}
