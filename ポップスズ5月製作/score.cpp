#include "score.h"
#include "main.h"
#include "file.h"

int number[10];
int number_r[10];
int scoreBoard[2];
int scoreBoard_r[2];
int high_score = 0;
int before_high_score = 0;	// ハイスコア一時格納用
int score;

void ScoreSysInit()
{
	LoadDivGraph("bmp/number.png", 10, 10, 1, 16, 16, number);
	LoadDivGraph("bmp/number_reverse.png", 10, 10, 1, 16, 16, number_r);
	LoadDivGraph("bmp/score.png", 2, 1, 2, 136, 16, scoreBoard);
	LoadDivGraph("bmp/score_reverse.png", 2, 1, 2, 136, 16, scoreBoard_r);
}

void ScoreInit()
{
	score = 0;//スコアの初期化
	high_score = HighScoreLoad();
	before_high_score = high_score;
}

void SetScore(SCOREDATA data, int val)	// 加算する対象と量
{
	switch (data)
	{
	case HIGH_SCORE:
		if (val >= high_score)
		{
			high_score = val;
			HighScoreSave(high_score);
		}
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


	//スコア表示
	num = sprintf_s(buf, "%*d", 6, score);
	for (int i = 0; i < num; i++)
	{
		DrawGraph((SCREEN_SIZE_X + i * 16) -  16 * 6, 0, number[(buf[i] - '0')], true);
	}

	//char buf1[100];
	//int num1;

	//num1 = sprintf_s(buf1, "%*d", 6, high_score);
	//for (int i = 0; i < num1; i++)
	//{
	//	DrawGraph(i*16, 0, number[(buf1[i] - '0')], true);
	//}
}

void HighScoreDraw()
{
	char buf[100];
	int num;

	if (score > before_high_score)
	{
		DrawGraph(SCREEN_SIZE_X / 2 - 137 / 2, SCREEN_SIZE_Y / 10 * 6, scoreBoard_r[0], true);

		//num = sprintf_s(buf, "%d", high_score);
		//for (int i = 0; i < num; i++)
		//{
		//	DrawGraph((SCREEN_SIZE_X / 2 + i * 16) - num / 2 * 16, SCREEN_SIZE_Y / 10 * 6 + 32, number_r[(buf[i] - '0')], true);
		//}
	}
	else
	{
		//スコア
		DrawGraph(SCREEN_SIZE_X / 2 - 76 / 2, SCREEN_SIZE_Y / 10 * 6, scoreBoard_r[1], true);

	}
	//スコア表示
	num = sprintf_s(buf, "%d", score);
	for (int i = 0; i < num; i++)
	{
		DrawGraph((SCREEN_SIZE_X / 2 + i * 16) - num * 16 / 2, SCREEN_SIZE_Y / 10 * 6 + 32, number_r[(buf[i] - '0')], true);
	}

}
