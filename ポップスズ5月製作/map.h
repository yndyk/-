//-----------------------------------
//
// stageID1取得用関数の追加
//
//-----------------------------------
#pragma once

enum STAGE_ID 
{
	STAGE1,
	STAGE2,
	STAGE3
};

extern STAGE_ID stageID;

void StageSysinit();
void StageInit();
void StageUpdate();
void StageDraw();
int GetStageID();		// stageID取得用関数
