#include "score.h"
#include "main.h"

int number[10];
int scoreBoard[2];
int high_score;
int score;

void ScoreSysInit()
{
	LoadDivGraph("bmp/number.png", 10, 10, 1, 16, 16, number);
	LoadDivGraph("bmp/score.png", 2, 1, 2, 136, 16, scoreBoard);
	
}

void SetScore(SCOREDATA data, int val)	// 加算する対象と量
{
	switch (data)
	{
	case HIGH_SCORE:
		high_score += val;
		break;
	case SCORE:
		score += val;
		break;
	}
}

int GetScore(SCOREDATA data)
{
	switch (data)
	{
	case HIGH_SCORE:
		return high_score;
		break;
	case SCORE:
		return score;
		break;
	}
	return -1;
}

void ScoreUpdate()
{
}

void ScoreDraw()
{
	char buf[100];		// 文字数用バッファー
	int num;

	//スコア
	DrawGraph(SCREEN_SIZE_X - 76 - 16 * 7, 0, scoreBoard[1], true);



	num = sprintf_s(buf, "%*d", 6, score);
	for (int i = 0; i < num; i++)
	{
		DrawGraph((SCREEN_SIZE_X + i * 16) -  16 * 6, 0, number[(buf[i] - '0')], true);
	}
}
