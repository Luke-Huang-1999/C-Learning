#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>



int main()
{
	int a = 5;
	int& ref = a;
	a = a + 10;
	return 0;
}

