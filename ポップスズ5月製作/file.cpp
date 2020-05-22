#include "file.h"
#include <windows.h>
#include <stdio.h>
#include "score.h"

static char FileName[] = "HighScore.txt";	// �n�C�X�R�A���i�[����t�@�C����

int HighScoreLoad(void)
{
    FILE *fp;
    int HighScore;

    if ((fopen_s(&fp, "HighScore.txt", "rb")) == 0)
        HighScore = 999;
    else
    {
        fscanf_s(fp, "%d", &HighScore);
        fclose(fp);
    }

    return (HighScore);
}

void HighScoreSave(int newScore)
{
    FILE* fp;
    char mes[80];

    if ((fopen_s(&fp, "HighScore.txt", "wb")) == 0)
    {
        //wsprintf(mes, "�f�[�^�t�@�C���̃I�[�v���Ɏ��s���܂����B�ۑ��𒆎~���܂����B\n");
        //OutputDebugString(mes);
        
        return;
    }

    fprintf_s(fp, "%d", newScore);
    fclose(fp);
}
