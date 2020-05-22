#pragma once

enum SCOREDATA
{
	HIGH_SCORE,
	SCORE,

};

void ScoreSysInit();
void SetScore(SCOREDATA, int);
int GetScore(SCOREDATA);
void ScoreUpdate();
void ScoreDraw();