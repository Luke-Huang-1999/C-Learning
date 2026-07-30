#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct HuffmanNode
{
	char data;                  // 字元
	int weight;                 // 權重(出現次數)
	
}snode;

int main()
{
	char str[] = "ACBABAADA";
	int size_str = sizeof(str) - 1;
	snode sort[4] = { 0 };

	int i;
	int num = 0;
	for (i = 0; i < size_str; i++)
	{
		num = str[i] - 'A';
		sort[num].data = str[i];
		sort[num].weight++;
	}

	for (i = 0; i < 4; i++)
	{
		printf("%c %d\n", sort[i].data, sort[i].weight);
	}

	return 0;
}

