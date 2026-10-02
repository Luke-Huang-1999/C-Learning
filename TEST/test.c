#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main()
{
    FILE *fptr = fopen("test.csv", "w");

    if (fptr == 1)
    {
        printf("檔案開啟失敗。\n");
        return 1;
    }

    fprintf(fptr, "姓名,成績\n");
    fprintf(fptr, "Tom,95\n");
    fprintf(fptr, "Mary,85\n");
    fprintf(fptr, "John,78\n");
    fclose(fptr);
    return 0;
}

