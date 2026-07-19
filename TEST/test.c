#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define row 6
#define col 6

typedef struct node
{
	char p1;
	char p2;
	int weight;
	struct node* next;
}node;

FILE* file_open(char file_name[]);
node* create_node(char p1, char p2, int weight);
void create_adjmatrix(FILE* fptr, int adjmatrix[row][col]);
void print_adjmatrix(int adjmatrix[row][col]);
node* create_adjlist(node* adjlist[row], int adjmatrix[row][col]);
void print_adjlist(node* adjlist[row]);



int main()
{
	//宣告
	int adjmatrix[row][col] = { 0 };
	node* adjlist[row] = { NULL };

	//檔案開啟
	FILE* fptr = file_open("adjmatrix.txt");

	//將檔案內容記錄至鄰接矩陣
	create_adjmatrix(fptr, adjmatrix);
	printf("adjmatrix print:\n");//列印紀錄結果
	print_adjmatrix(adjmatrix);
	printf("================================\n\n");

	//將鄰接矩陣轉換成鄰接鏈結串列
	create_adjlist(adjlist, adjmatrix);
	printf("adjlist print:\n");
	print_adjlist(adjlist);//鄰接鏈結串列
	printf("================================\n\n");
	

	//關閉檔案
	fclose(fptr);
	return 0;
}

FILE* file_open(char file_name[])
{
	FILE* fptr = fopen(file_name, "r");
	if (fptr == NULL)
	{
		printf("Failed to open file.\n");
		exit(1);
	}

	return fptr;
}

node* create_node(char p1, char p2, int weight)
{
	node* newnode = (node*)malloc(sizeof(node));
	if (newnode == NULL)
	{
		printf("create_node function error.\n");
		printf("newnode is NULL\n");
		exit(1);
	}

	newnode->p1 = p1;
	newnode->p2 = p2;
	newnode->weight = weight;
	newnode->next = NULL;

	return newnode;
}

void create_adjmatrix(FILE* fptr, int adjmatrix[row][col])
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			fscanf(fptr, "%d", &adjmatrix[i][j]);
		}
	}
}

void print_adjmatrix(int adjmatrix[row][col])
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf(" %d ", adjmatrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

node* create_adjlist(node* adjlist[row], int adjmatrix[row][col])
{
	int i, j;
	node* current = NULL;
	for (i = 0; i < row; i++)
	{
		current = adjlist[i];
		for (j = i; j < col; j++)
		{
			if (adjmatrix[i][j] != 0)
			{
				node* newnode = create_node(('A' + i), ('A' + j), adjmatrix[i][j]);
				if (current == NULL)
				{
					current = newnode;
					adjlist[i] = newnode;
				}
				else
				{
					current->next = newnode;
					current = newnode;
				}
			}
		}
	}
	return adjlist[0];
}

void print_adjlist(node* adjlist[row])
{
	int i;
	node* current = NULL;
	for (i = 0; i < row; i++)
	{
		current = adjlist[i];
		while (current != NULL)
		{
			//printf("p1 = %c, p2 = %c, weight = %d, address = %p, next address = %p\n", current->p1, current->p2, current->weight, current,current->next);
			printf("p1 = %c, p2 = %c, weight = %d\n", current->p1, current->p2, current->weight);
			current = current->next;
		}
		//printf("\n");
	}

}


