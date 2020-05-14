#pragma once

enum STAGE_ID {
	STAGE1,
	STAGE2,
	STAGE3
};


void StageSysinit();
void StageInit();
void StageUpdate();
void StageDraw();
