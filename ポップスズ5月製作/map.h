//-----------------------------------
//
// stageID1æ“¾—pŠÖ”‚Ì’Ç‰Á
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
int GetStageID();		// stageIDæ“¾—pŠÖ”
