#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

void change(int str_1[], int str_2[]);

int main()
{
	int str_1[3] = { 1,2,3 };
	int str_2[3] = { 0 };

	change(str_1, str_2);


	int i;
	for (i = 0; i < 3; i++)
	{
		printf("%d ", str_2[i]);
	}
	return 0;
}

void change(int str_1[], int str_2[])
{
	int i;
	for (i = 0; i < 3; i++)
	{
		str_2[i] = str_1[i];
	}
	
}