#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define row 7
#define col 7
struct stack
{
	int data;
	struct stack* next;
};
typedef struct stack node;

FILE* file_open(char file_name[]);
void create_adjmatrix(FILE* fptr, int adj_matrix[row][col]);
node* create_adjlist(int adj_martrix[row][col]);
node* create_node(int data);

int main()
{
	FILE* fptr = file_open("adj_list.txt");
	int adj_matrix[row][col] = { 0 };
	create_adjmatrix(fptr, adj_matrix);
	

}

FILE* file_open(char file_name[])
{
	FILE* fptr = fopen(file_name, "r");

	if (fptr == NULL)
	{
		printf("Failed to open the file.\n");
		exit(1);
	}
	else
		printf("good.\n");
	return fptr;
}

void create_adjmatrix(FILE* fptr, int adj_matrix[row][col])
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
			fscanf(fptr, "%d", &adj_matrix[i][j]);
	}
}

node* create_adjlist(int adj_martrix[row][col])
{
	node* adjlist[row] = { NULL };

}

node* create_node(int data)
{
	node* newnode = (node*)malloc(sizeof(node));
	if (newnode == NULL)
	{
		printf("Failed to create newnode.\n");
		exit(1);
	}
	return newnode;
}

