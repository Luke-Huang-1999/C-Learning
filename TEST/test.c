#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void change(int* num);

void show(int a);

int main()
{
    int num = 100;
    show(num);

    return 0;
}

void change(int* num)
{
    *num = 100;
}
void show(int a)
{
    a = 100;
    printf("num = %d\n", a);
}

