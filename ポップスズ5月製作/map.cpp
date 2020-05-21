//----------------------------------------------
// 
// switch���̊ecase�ɃC�J�Ă��̏��������������܂���
// 
//----------------------------------------------
#include "main.h"
#include "map.h"
#include "player.h"
#include "enemy.h"
#include "awa.h"
#include "unti.h"
#include "ikayaki.h"
#include"ikatenn.h"
#include"surume.h"

int MapImage;
int MapImage2;//2�X�e�[�W
int MapImage3;//3�X�e�[�W

STAGE_ID stageID;

void StageSysinit()
{
	MapImage = LoadGraph("bmp/map_big.bmp");
	MapImage2 = LoadGraph("bmp/EDGE1.bmp");
	MapImage3 = LoadGraph("bmp/EDGE2.bmp");
}

void StageInit()
{
	stageID = STAGE1;
}

void StageUpdate()
{
	switch (stageID)
	{
	case STAGE1:
		if (enemyAllDeadFlag) {	// �����ɓG�����ׂē|�����Ƃ��̏���������
			InitEnemy();
			InitPlayer();
			InitIkayaki();
			InitIkatenn();
			InitSurume();
			BubbleDelete();
			DeleteUnti();
			DeleteIkatenn();
			DeleteIkayaki();
			DeleteSurume();
			leftTime = TIME_FRAME * 31;
			stageID = STAGE2;
		}
		break;
	case STAGE2:
		if (enemyAllDeadFlag) {	// �����ɓG�����ׂē|�����Ƃ��̏���������
			InitEnemy();
			InitPlayer();
			InitIkayaki();
			InitIkatenn();
			InitSurume();
			BubbleDelete();
			DeleteUnti();
			DeleteIkatenn();
			DeleteIkayaki();
			DeleteSurume(); 
			leftTime = TIME_FRAME * 31;
			stageID = STAGE3;
		}
		break;
	case STAGE3:
		if (enemyAllDeadFlag) {	// �����ɓG�����ׂē|�����Ƃ��̏���������

			gamemode = GMODE_CLERA;
			stageID = STAGE1;//����������
		}
		break;
	}
}

void StageDraw()
{
	int image;

	if (stageID == STAGE1)		image = MapImage;
	if (stageID == STAGE2)		image = MapImage2;
	if (stageID == STAGE3)		image = MapImage3;

	DrawGraph(0, 0, image, true);

	DrawFormatString(0, 0, 0xff0000, "stageID:%d", stageID);

}

int GetStageID()
{
	return stageID;
}
