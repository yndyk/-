#include "score.h"
#include "main.h"
#include "file.h"

int number[10];
int number_r[10];
int scoreBoard[2];
int scoreBoard_r[2];
int high_score = 0;
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
	score = 0;//�X�R�A�̏�����
}

void SetScore(SCOREDATA data, int val)	// ���Z����ΏۂƗ�
{
	switch (data)
	{
	case HIGH_SCORE:
		if (val >= high_score)
		{
			high_score = val;
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
	char buf[100];		// �������p�o�b�t�@�[
	int num;

	//�X�R�A
	DrawGraph(SCREEN_SIZE_X - 76 - 16 * 7, 0, scoreBoard[1], true);


	//�X�R�A�\��
	num = sprintf_s(buf, "%*d", 6, score);
	for (int i = 0; i < num; i++)
	{
		DrawGraph((SCREEN_SIZE_X + i * 16) -  16 * 6, 0, number[(buf[i] - '0')], true);
	}
}

void HighScoreDraw()
{
	char buf[100];
	int num;

	DrawGraph(SCREEN_SIZE_X / 2 - 137 / 2, SCREEN_SIZE_Y / 5 * 2, scoreBoard_r[0], true);

	num = sprintf_s(buf, "%d", high_score);
	for (int i = 0; i < num; i++)
	{
		DrawGraph((SCREEN_SIZE_X / 2 + i * 16) - num / 2 * 16, SCREEN_SIZE_Y / 5 * 2 + 32, number_r[(buf[i] - '0')], true);
	}
}
