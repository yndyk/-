#include "main.h"
#include"player.h"
#include"unti.h"

int UntiImage;
CHARACTER unti;

//���[�h
void SysinitUnti()
{
	UntiImage = LoadGraph("bmp/�E���R.png");
}

//������
void initUnti() 
{
	unti.pos = { 400,350 };
	unti.size = { UNTI_SIZE_X,UNTI_SIZE_Y };
	unti.flag = false;
	unti.speed = 6;

}

//�X�V
void UpdetaUnti()
{
	
	if (unti.flag == false)
	{
		//unti.pos.y += unti.speed;
	}
		if ((player.pos.x < unti.pos.x + unti.size.x
			&&unti.pos.x < player.pos.x + player.size.x
			&&player.pos.y < unti.pos.y + unti.size.y
			&&unti.pos.y < player.pos.y + player.size.y))
		{
			player.flag = false;
			unti.flag = true;
			player.hp -= 1;
		}

		if (unti.flag == true)
		{
			
			unti.pos.x = GetRand(320);
			
			unti.flag = false;
		}
	
}

//�`��
void DrawUnti()
{
	if (unti.flag == false)
	{
		DrawGraph(unti.pos.x, unti.pos.y, UntiImage, true);
		/*DrawBox(unti.pos.x, unti.pos.y,
			unti.size.x, unti.size.y, 0xff0000, true);*/
	}
	
}