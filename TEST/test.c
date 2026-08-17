#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct data
{
	char data0[20];
	char data1[20];
	char data2[20];
	char data3[20];
	char data4[20];
	char name_list[5][10];
}node;

int main()
{
	char str_1[20] = { "Alice" };
	char str_2[20] = { "Due" };

	int a = 5;
	a = strcmp(str_1, "Ali");
	printf("%d", a);
	//strcpy(str_1, str_2);
	return 0;
}

