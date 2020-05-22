#include "file.h"
#include <windows.h>
#include <stdio.h>
#include "score.h"

static char FileName[] = "HighScore.txt";	// ハイスコアを格納するファイル名

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
        //wsprintf(mes, "データファイルのオープンに失敗しました。保存を中止しました。\n");
        //OutputDebugString(mes);
        
        return;
    }

    fprintf_s(fp, "%d", newScore);
    fclose(fp);
}
