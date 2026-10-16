#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#define ROW 3
#define COL 3

typedef struct block
{
	char str[20];

	struct block* up;
	struct block* down;
	struct block* right;
	struct block* left;
}block;

block* create_block(char s[]);

int main()
{
	char s[ROW][COL][20] = 
	{
		{"選項 0", "選項 1", "選項 2"},
		{"選項 3", "選項 4", "選項 5"},
		{"選項 6", "選項 7", "選項 8"}
	};
	block* head = NULL;
	block* current = NULL;
	int i,j;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (i == 0 && j == 0)
			{
				head = create_block(s[i][j]);
				current = head;
			}
			else
			{
				current->right = create_block(s[i][j]);
				current = current->right;
			}
		}
	}

	return 0;
}

block* create_block(char s[])
{
	block* newblock = (block*)malloc(sizeof(block));
	if (newblock == NULL)
	{
		printf("malloc is failed.\n");
		exit(1);
	}

	strcpy(newblock->str, s);
	newblock->up = NULL;
	newblock->down = NULL;
	newblock->right = NULL;
	newblock->left = NULL;

	return newblock;
}