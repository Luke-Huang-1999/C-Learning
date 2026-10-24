#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdbool.h>
int main()
{
	int i = 2;
	bool d = false;
	if(d)
		printf("i = %d\n", i);
	else
		printf("i * 2 = %d\n", i * 2);

	return 0;
}