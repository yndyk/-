#include "file.h"
#include <windows.h>
#include <stdio.h>
#include "score.h"

#define BUFFER 256

const char *file = "scoreData.dat";	// �n�C�X�R�A���i�[����t�@�C����
int HighScore = 0;


int HighScoreLoad()
{
    FILE *fp;

    fopen_s(&fp, file, "rb");
    char stlen[BUFFER];
    while (fgets(stlen, BUFFER, fp) != NULL)
    {
        printf("%s", stlen);
        int num = atoi(stlen);
        if (num > HighScore)
        {
            HighScore = num;
        }
        else
        {
            HighScore = 0;
        }
            
    }

    if (fp  == NULL)
    {
        printf("%s�̃I�[�v���Ɏ��s���܂����B\n", file);
        getchar();
    }
    else
    {
        fprintf(fp, "%d", HighScore);
        //fwrite(&HighScore, sizeof(int), 1, fp);
        fclose(fp);
    }

    return (HighScore);
}

void HighScoreSave(int newScore)
{
    FILE* fp;
    char mes[80];

    if ((fopen_s(&fp, file, "w")) != 0)
    {
        wsprintf(mes, "�f�[�^�t�@�C���̃I�[�v���Ɏ��s���܂����B�ۑ��𒆎~���܂����B\n");
        OutputDebugString(mes);
        return;
    }

    fprintf(fp, "%d", newScore);
    //fwrite(&newScore, sizeof(int), 1, fp);
    fclose(fp);
}
