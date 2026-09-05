#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

int main()
{
    time_t now;
    struct tm* current;

    now = time(NULL);

    current = localtime(&now);
    
    printf("年份：%d\n", current->tm_year + 1900);
    printf("月份：%d\n", current->tm_mon + 1);
    printf("日期：%d\n", current->tm_mday);

    return 0;
}

