#include "main.h"
#include "box.h"
#include "hitCheck.h"
#include "player.h"
#include"enemy.h"
#include <math.h>

CHARACTER box;
int boxImage;
//���[�h
void SysInitBox()
{
	boxImage = LoadGraph("bmp/nextstage.png");
}
//������
void InitBox() 
{
	box.pos = { 320,400 };
	box.size = { 64,64 };
	box.offSet = { box.size.x / 2,box.size.y / 2 };
	box.flag = false;
}
//�����蔻��
bool HitBox(CHARACTER a, CHARACTER b )
{		
	XY distance;		// ������Ȃ��ŏ�����
	bool hitFlag = false;	// �q�b�g����p
	distance.x = abs(a.offSet.x + b.offSet.x);
	distance.y = abs(a.offSet.y + b.offSet.y);
	if (abs(a.pos.x - b.pos.x) < distance.x &&			// ���S�ԋ������ŏ������ȉ��ɂȂ����瓖������
		abs(a.pos.y - b.pos.y) < distance.y)
	{
		hitFlag = true;
	}
	return hitFlag;

}

//�`��
void DrawBox()
{
	if (NextFlag == true) 
	{
		DrawBox(box.pos.x - box.offSet.x,
			box.pos.y - box.offSet.y,
			box.pos.x + box.offSet.x,
			box.pos.y + box.offSet.y, 0x000000, false);
		DrawGraph(box.pos.x - box.offSet.x,
			box.pos.y - box.offSet.y,
			boxImage,true);
		/*DrawString(box.pos.x - 20, box.pos.y-10, "NEXT", 0xff0000, true);
		DrawString(box.pos.x - 30, box.pos.y+10, "STAGE", 0xff0000, true);*/
	}
}

