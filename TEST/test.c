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
node* create_adjlist(int adj_matrix[row][col], node* adjlist[]);
node* create_node(int data);
void print_adjlist(node* adjlist[]);
void print_adjmatrix(int adj_matrix[row][col]);

int main()
{
	FILE* fptr = file_open("adj_list.txt");
	int adj_matrix[row][col] = { 0 };
	node* adjlist[row] = { NULL };
	create_adjmatrix(fptr, adj_matrix);
	create_adjlist(adj_matrix, adjlist);

	print_adjmatrix(adj_matrix);
	print_adjlist(adjlist);
	fclose(fptr);
	return 0;
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

node* create_adjlist(int adj_martrix[row][col], node* adjlist[])
{
	//adjlist[row] = { NULL };
	node* current = NULL;
	node* newnode = NULL;
	int i, j;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (adj_martrix[i][j] == 1)
			{
				newnode = create_node(j + 1);
				if (current == NULL)
					adjlist[i] = newnode;
				else
					current->next = newnode;

				current = newnode;
			}
		}
		current = NULL;
	}
	return adjlist[0];
}

node* create_node(int data)
{
	node* newnode = (node*)malloc(sizeof(node));
	if (newnode == NULL)
	{
		printf("Failed to create newnode.\n");
		exit(1);
	}
	newnode->data = data;
	newnode->next = NULL;

	return newnode;
}


void print_adjlist(node* adjlist[])
{
	int i;
	node* current = NULL;
	for (i = 0; i < row; i++)
	{
		current = adjlist[i];
		while (current != NULL)
		{
			printf("%d ", current->data);
			current = current->next;
		}
		printf("\n");
	}
}

void print_adjmatrix(int adj_matrix[row][col])
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf("%d ", adj_matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}