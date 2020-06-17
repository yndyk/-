#include "main.h"
#include "kaigara.h"
#include "player.h"
#include "shot.h"
#include "hitCheck.h"
#include "sinju.h"

CHARACTER shell;
int shellImage;
int shellCnt;		// äLÇ™èoÇΩâÒêî


void SysInitShell()
{
	shellImage = LoadGraph("bmp/kaigara.png");
}

void InitShell()
{
	shell.pos = { 0, 0 };
	shell.flag = false;
	shell.hp = 5;
	shell.size = { 34, 32 };
	shell.speed = { 1, 1 };
	shell.offSet = { shell.size.x / 2, shell.size.y / 2 };
	shell.changeFlag = false;
	shell.count = 0;
	shell.onlyOnce = false;
}

void UpdetaShell(CHARACTER p)
{
	for (int i = 0; i < SHOT_MAX; i++)
	{
		if (!shell.flag)
		{
			if (p.hp < PLAYER_HP_MAX * TIME_FRAME / 2)
			{
				if (!shell.onlyOnce)
				{
					shell.pos = { p.pos.x, -shell.size.y };
					shell.flag = true;
					shell.onlyOnce = true;
				}
			}
		}
		else
		{
			if (shot[i].flag)
			{
				if (HitCheckRectToRect(shell, i, shot))
				{
					shot[i].flag = false;
					shell.hp--;
				}
				if (shell.pos.x > SCREEN_SIZE_Y + shell.size.y)
				{
					shell.flag = false;
				}
			}

			if (shell.hp == 0)
			{
				//èàóùì‡óe
				shell.changeFlag = true;
				shell.flag = false;
			}
			shell.count++;
			if(shell.count % 30 == 0)
				shell.pos.y += shell.speed.y;
		}
	}

	UpdataPearl(p, shell);
}

void DrawShell()
{
	if (shell.flag)
	{
		DrawGraph(shell.pos.x - shell.offSet.x, shell.pos.y - shell.offSet.y, shellImage, true);


		/*DrawBox(shell.pos.x - shell.offSet.x,
			shell.pos.y - shell.offSet.y,
			shell.pos.x + shell.offSet.x,
			shell.pos.y + shell.offSet.y,
			0x000000, false);*/

		//DrawFormatString(50, 50, 0xff0000, "cnt:%d", shellCnt);
		//DrawFormatString(50, 70, 0xff0000, "x:%d", shell.pos.x);
		//DrawFormatString(50, 90, 0xff0000, "y:%d", shell.pos.y);
		//DrawFormatString(50, 110, 0xff0000, "f:%d", shell.flag);
		//DrawFormatString(50, 130, 0xff0000, "hp:%d", shell.hp);
	}
	
	if (shell.changeFlag)
	{
		DrawPearl();
	}
}

void MoveShell(int)
{
}
