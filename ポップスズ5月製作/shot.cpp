//--------------------------------------------
// 
// �I�t�Z�b�g�̒ǉ�
// �`����I�t�Z�b�g�����炷
// 
//--------------------------------------------
#include "main.h"
#include"player.h"
#include"keycheck.h"
#include"shot.h"

int ShotImage;
bool DivFlag;//����
CHARACTER shot;
//���[�h
void SysInitShot()
{
	ShotImage = LoadGraph("bmp/�U����.png");
}
//������
void InitShot()
{
	shot.pos = { 0,0 };
	shot.speed = { 8, 8 };
	shot.size = { 32,32 };
	shot.offSet = { shot.size.x / 2, shot.size.y / 2 };
	shot.count = 0;
	shot.flag = false;
	DivFlag = false;//false���E�Atrue����
}
//�X�V
void UpdetaShot()
{
	if(CheckHitKey(KEY_INPUT_SPACE))
	{
		if(shot.flag == false)
		{
			shot.pos.x = player.pos.x;
			shot.pos.y = player.pos.y;
			shot.flag = true;
		}
		if(shot.pos.x > SCREEN_SIZE_X
			||shot.pos.x < 0 - shot.size.x/2
			|| shot.pos.y > SCREEN_SIZE_Y
			|| shot.pos.y < 0 - shot.size.y / 2)
		{
			shot.flag = false;
		}
		if (player.div == DIV_RAHGT)
		{
			DivFlag = false;
		}
		if (player.div == DIV_LEFT)
		{
			DivFlag = true;
		}
	}
	if (DivFlag == false) 
	{
		shot.pos.x -= shot.speed.x;
	}
	if (DivFlag == true)
	{
		shot.pos.x += shot.speed.x;
	}
}
//�`��
void DrawShot()
{
	if (shot.flag == true) 
	{
		DrawGraph(shot.pos.x - shot.offSet.x,
			shot.pos.y - shot.offSet.y,
			ShotImage, true);

		// �����蔻��̉���
		DrawBox(shot.pos.x - shot.offSet.x,
			shot.pos.y - shot.offSet.y,
			shot.pos.x + shot.offSet.x,
			shot.pos.y + shot.offSet.y,
			0x000000, false);
	}
}
