#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define row 7
#define col 7
struct linklist
{
	char data;
	struct linklist* next;
};
typedef struct linklist node;

void check_file_open(FILE* fptr);
node* create_adjlist(FILE* fptr, node* adj_list[row]);
node* creat_node(char data);
int main()
{
	FILE* fptr = fopen("adj_list.txt", "r");
	check_file_open(fptr);

	node* adj_list[row] = { NULL };



	fclose(fptr);
	return 0;
}

void check_file_open(FILE* fptr)
{
	if (fptr == NULL)
	{
		printf("check_file_open::failed\n");
		exit(1);
	}
}

node* create_adjlist(FILE* fptr, node* adj_list[row])
{
	int i, j;
	int ch;
	node* current = NULL;
	char vertex[row] = { 'A','B','C' ,'D' ,'E' ,'F' ,'G' };
	for (i = 0; i < row; i++)
	{
		current = 
		for (j = 0; j < col;j++)
		{
			fscanf(fptr, "%d", &ch);
			if (ch == 1)
			{
				
				current = creat_node(vertex[j]);
			}
		}
		adj_list[i] = current;
	}
}

node* creat_node(char data)
{
	node* newnode = (node*)malloc(sizeof(node));
	if (newnode == NULL)
	{
		printf("creat_node::failed\n");
		printf("newnode == NULL\n");
		exit(1);
	}
	newnode->data = data;
	newnode->next = NULL;
	return newnode;
}