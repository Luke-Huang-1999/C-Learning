#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#define row 6

void visited_modefiy(char p1, char p2, char visited[]);

int main()
{
	char visited[row] = { 0 };
	visited_modefiy('A', 'C', visited);

	int i;
	for (i = 0; i < row; i++)
	{
		printf("%d ", visited[i]);
	}

	return 0;
}

void visited_modefiy(char p1, char p2, char visited[])
{
	int num_1 = p1 - 'A';
	int num_2 = p2 - 'A';
	visited[num_1] = 1;
	visited[num_2] = 1;

}
