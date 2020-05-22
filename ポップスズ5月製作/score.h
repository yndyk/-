#pragma once

enum SCOREDATA
{
	HIGH_SCORE,
	SCORE,

};

void ScoreSysInit();
void ScoreInit();
void SetScore(SCOREDATA, int);
int GetScore(SCOREDATA);
void ScoreUpdate();
void ScoreDraw();
void HighScoreDraw();