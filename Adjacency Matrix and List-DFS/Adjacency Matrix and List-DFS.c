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
void create_adjlist(FILE* fptr, node* adj_list[row]);
node* creat_node(char data);
void print_adjlist(node* adj_list[row]);
node* search_adjlist(char data, node* adj_list[row]);
void print_single_adjlist(char data, node* adj_list[row]);
node* DFS(node* adj_list[row]);
int main()
{
	//開檔
	FILE* fptr = fopen("adj_list.txt", "r");
	check_file_open(fptr);
	//建立鄰接陣列
	node* adj_list[row] = { NULL };
	create_adjlist(fptr, adj_list);
	//列印鄰接陣列
	printf("Adjacency List:\n");
	print_adjlist(adj_list);
	printf("========================\n");
	printf("Single Adjacency List:\n");
	print_single_adjlist('G', adj_list);
	printf("========================\n");



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

void create_adjlist(FILE* fptr, node* adj_list[row])
{
	int i, j;
	int ch;
	node* start = NULL;
	node* end = NULL;
	node* current = NULL;
	char vertex[row] = { 'A','B','C' ,'D' ,'E' ,'F' ,'G' };
	for (i = 0; i < row; i++)
	{
		node* newnode = creat_node(vertex[i]);

		adj_list[i] = newnode;
		end = newnode;

		for (j = 0; j < col;j++)
		{
			fscanf(fptr, "%d", &ch);

			if (ch == 1 )
			{
				node* newnode = creat_node(vertex[j]);

				end->next = newnode;
				end = newnode;
			}
		}
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

void print_adjlist(node* adj_list[row])
{
	int i;
	for (i = 0; i < row; i++)
	{
		node* current = adj_list[i];
		while (current != NULL)
		{
			printf("%c", current->data);
			if (current->next != NULL)
				printf(" -> ");
			current = current->next;
		}
		printf("\n");
	}
}

node* search_adjlist(char data, node* adj_list[row])
{
	int i;
	for (i = 0; i < row; i++)
	{
		if (adj_list[i]->data == data)
			return adj_list[i];
	}
	printf("search failed\n");
	exit(1);
}

void print_single_adjlist(char data, node* adj_list[row])
{
	node* current = search_adjlist(data, adj_list);
	while (current != NULL)
	{
		printf("%c", current->data);
		if (current->next != NULL)
		{
			printf(" -> ");
		}
		current = current->next;
	}
	printf("\n");
}

node* DFS(node* adj_list[row])
{
	node* stack = NULL;
	node* top = NULL;
	node* bot = NULL;
	node* current = NULL;


}