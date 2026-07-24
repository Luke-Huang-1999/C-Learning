#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define row 7
#define col 7

typedef struct node
{
	char p1;
	char p2;
	int weight;
	struct node* next;
}node;


FILE* file_open(char file_name[]);



int main()
{
	char file_name[] = "adjmatrix.txt";
	FILE* fptr = file_open(file_name);



	fclose(fptr);
	return 0;
}

FILE* file_open(char file_name[])
{
	FILE* fptr = fopen(file_name, "r");
	if (fptr == NULL)
	{
		printf("file_open::fail\n");
		exit(1);
	}

	return fptr;
}