#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define row 7
#define col 7
struct node
{
	int data;
	struct node* next;
};
typedef struct node node;

FILE* file_open(char file_name[]);
void create_adjmatrix(FILE* fptr, int adj_matrix[row][col]);
void create_adjlist(int adj_matrix[row][col], node* adjlist[]);
node* create_node(int data);
void print_adjlist(node* adjlist[]);
void print_adjmatrix(int adj_matrix[row][col]);
void BFS(int start, node* adj_list[]);
void DFS(int start, node* adj_list[]);

int main()
{
	FILE* fptr = file_open("adj_list.txt");
	int adj_matrix[row][col] = { 0 };
	node* adj_list[row] = { NULL };
	create_adjmatrix(fptr, adj_matrix);
	create_adjlist(adj_matrix, adj_list);
	printf("adjmatrix\n---------------------------------------\n");
	print_adjmatrix(adj_matrix);
	printf("adjlist\n---------------------------------------\n");
	print_adjlist(adj_list);
	printf("BFS\n---------------------------------------\n");
	BFS(5,adj_list);
	printf("DFS\n---------------------------------------\n");
	DFS(1,adj_list);

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

void create_adjlist(int adj_martrix[row][col], node* adjlist[])
{
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
	printf("\n");
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

void BFS(int start, node* adj_list[])//廣度探索_佇立
{
	//佇立用
	node* front = NULL;
	node* rear = NULL;
	//鄰接串列
	node* current = NULL;
	//是否被拜訪
	int visited[row] = { 0 };
	//第一個點進入佇立
	front = create_node(start);
	rear = front;
	visited[front->data - 1] = 1;

	while (front != NULL)
	{
		//pop
		int num = front->data;
		printf("%d ", front->data);
		
		//push
		current = adj_list[num - 1];
		while (current != NULL)
		{
			if (visited[current->data-1] == 0)
			{
				node* newnode = create_node(current->data);
				rear->next = newnode;
				rear = newnode;

				visited[current->data-1] = 1;
			}
			current = current->next;
		}
		node* tmp = front;
		front = front->next;
		free(tmp);
		tmp = NULL;
	}
	rear = NULL;
	printf("\n\n");
}

void DFS(int start, node* adj_list[])//堆疊
{
	//堆疊用
	node* top = NULL;
	//鄰接串列用
	node* current = NULL;
	int visited[row] = { 0 };
	
	//首點建立
	top = create_node(start);
	visited[start - 1] = 1;

	while (top != NULL)
	{
		current = adj_list[top->data - 1];
		//pop
		printf("%d ", top->data);
		top = top->next;
		
		//push
		while (current != NULL)
		{
			if (visited[current->data - 1] == 0)
			{
				node* newnode = create_node(current->data);
				newnode->next = top;
				top = newnode;

				visited[current->data - 1] = 1;
			}
			current = current->next;
		}
		
	}
}