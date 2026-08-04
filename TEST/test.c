#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int test(int i);

int main()
{

	int i = 10;
	test(10);

	return 0;
}

int test(int n)
{
	if (n == 0)      // 終止條件
		return 0;

	return n + test(n - 1);
}