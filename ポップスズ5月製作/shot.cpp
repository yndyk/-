//--------------------------------------------
// 
// UpdateShot()�̑啝�ȃR�[�h�̕ύX
// shot��z��ɕύX
// 
//--------------------------------------------
#include "main.h"
#include"player.h"
#include"keycheck.h"
#include"shot.h"

int ShotImage;
bool DivFlag;//����
CHARACTER shot[SHOT_MAX];
int shotCnt;
int ShotSound; 
//���[�h
void SysInitShot()
{
	ShotImage = LoadGraph("bmp/�U����.png");
}
//������
void InitShot()
{
	for (int i = 0; i < SHOT_MAX; i++)
	{
		shot[i].pos = { 0,0 };
		shot[i].speed = { 8, 8 };
		shot[i].size = { 32, 32 };
		shot[i].offSet = { shot[i].size.x / 2, shot[i].size.y / 2 };
		shot[i].flag = false;
		DivFlag = false;//false���E�Atrue����
	}
	shotCnt = 0;
	ShotSound = LoadSoundMem("���f��/�V���b�g.mp3");
}
//�X�V
void UpdetaShot()
{
	if (trgKey[P1_SHOT])
	{
		for (int i = 0; i < SHOT_MAX; i++)
		{
			if (!shot[i].flag)
			{
				//int tmpSpd = shot[i].speed.x;
				shot[i].flag = true;
				shot[i].pos = player.pos;
				if (player.div == DIV_RAHGT)
				{
					if (shot[i].speed.x > 0)
						shot[i].speed.x = -1 * shot[i].speed.x;
				}
				if (player.div == DIV_LEFT)
				{
					if (shot[i].speed.x < 0)
						shot[i].speed.x = -1 * shot[i].speed.x;
				}
				break;
			}
		}
	PlaySoundMem(ShotSound, DX_PLAYTYPE_BACK);
	}
	

	for (int i = 0; i < SHOT_MAX; i++)
	{
		if (shot[i].flag)
		{
			shot[i].pos.x += shot[i].speed.x;

			if (shot[i].pos.x < -shot[i].size.x ||
				shot[i].pos.x > SCREEN_SIZE_X + shot[i].size.x ||
				shot[i].pos.y < -shot[i].size.y ||
				shot[i].pos.y > SCREEN_SIZE_Y + shot[i].size.y)
			{
				shot[i].flag = false;
			}
		}
	}
	shotCnt++;
}
//�`��
void DrawShot()
{
	for (int i = 0; i < SHOT_MAX; i++)
	{
		if (shot[i].flag == true)
		{
			DrawGraph(shot[i].pos.x - shot[i].offSet.x,
				shot[i].pos.y - shot[i].offSet.y,
				ShotImage, true);

			// �����蔻��̉���
			/*DrawBox(shot[i].pos.x - shot[i].offSet.x,
				shot[i].pos.y - shot[i].offSet.y,
				shot[i].pos.x + shot[i].offSet.x,
				shot[i].pos.y + shot[i].offSet.y,
				0x000000, false);*/
		}
	}
}
