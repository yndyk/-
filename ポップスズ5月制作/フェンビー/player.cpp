#include "main.h"
#include"keycheck.h"
#include"player.h"
#include"enemy.h"

int playerImage;
CHARACTER player;
//���[�h
void SysInitPlayer()
{
	playerImage = LoadGraph("bmp/������1.png");
}
//������
void InitPlayer()
{
	player.pos = { 500,430 };
	player.speed = 5;
	player.div = DIV_RAHGT;
	player.hp = 100;
	player.flag = false;
}
//�X�V
void UpdetaPlayer()
{
	//�ړ�
	if(CheckHitKey(KEY_INPUT_RIGHT))
	{
		player.pos.x += player.speed;
		player.div = DIV_LEFT;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		player.pos.x -= player.speed;
		player.div = DIV_RAHGT;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		player.pos.y -= player.speed;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		player.pos.y += player.speed;
	}
	
	//�ړ�����
	if (player.pos.x >= 590)
	{
		player.pos.x = 590;
	}
	if (player.pos.x < 0)
	{
		player.pos.x = 0;
	}
	if (player.pos.y >= 430)
	{
		player.pos.y = 430;
	}
	if (player.pos.y < 0)
	{
		player.pos.y = 0;
	}
	for (int i = 0; i < ENEMY_MAX; i++) 
	{
		if ((player.pos.x < enemy[i].pos.x + enemy[i].size.x
			&&enemy[i].pos.x < player.pos.x + player.size.x
			&&player.pos.y < enemy[i].pos.y + enemy[i].size.y
			&&enemy[i].pos.y < player.pos.y + player.size.y))
		{
			player.flag = true;
			enemy[i].flag = false;
			player.hp -= 1; 
			if (player.hp == 0) 
			{
				gamemode = GMODE_OVER;
			}
		}
	}
	if(gamemode == GMODE_OVER)
	{
		player.flag = false;
		for(int i = 0; i < ENEMY_MAX;i++)
		{
			enemy[i].flag = false;
		}
	}
}

//�`��
void DrawPlayer()
{
	switch (player.div) 
	{
	case DIV_RAHGT:
		DrawGraph(player.pos.x, player.pos.y, playerImage, true);
		break;
	case DIV_LEFT:
		DrawTurnGraph(player.pos.x, player.pos.y, playerImage, true);
		break;
	}
	DrawFormatString(30, 30, 0xff0000, "%d", player.hp, true);
	DrawBox(0, 440, player.hp, 450,0xff0000,true);
	DrawBox(0, 440, player.hp, 450, 0x000000, false);
}