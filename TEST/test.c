#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
int main()
{
    char test[100] = { "==============================" };
    char test1[100] = { "===" };
    int i = 0;
    while (test[i] != '\0')
    {
        i++;
    }
    printf("有%d個=\n", i);
    return 0;
}


