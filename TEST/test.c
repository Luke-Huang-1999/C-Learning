#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>



int main()
{
	int i;
	for (i = 0; i < 5; i++)
	{
		if (i != 1 || i != 3)
			printf("%d ", i);
	}

	return 0;
}

