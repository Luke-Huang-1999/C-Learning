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
node* DFS(char data, node* adj_list[row]);
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

	DFS('A', adj_list);

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

		for (j = 0; j < col; j++)
		{
			fscanf(fptr, "%d", &ch);

			if (ch == 1)
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

node* DFS(char data, node* adj_list[row])
{
	node* adj_ptr = NULL;
	node* stack_top = NULL;

	int visited[row] = { 0 };
	int num = 0;

	//搜尋第一個頂點
	adj_ptr = search_adjlist(data, adj_list);

	//先處理第一個頂點_入stack_top
	stack_top = creat_node(data);

	//紀錄已走訪
	num = data - 'A';
	visited[num] = 1;

	//pop->push
	while (stack_top != NULL)
	{
		//pop()
		printf("%c", stack_top->data);
		if (stack_top != NULL)
			printf(" => ");
		//建立指向下一層節點的指標
		node* tmp = stack_top;
		stack_top = stack_top->next;
		//釋放stack_top記憶體空間
		free(tmp);
		tmp = NULL;
		//指向下一個要處理的節點
		adj_ptr = adj_ptr->next;

		//push()
		while (adj_ptr != NULL)
		{
			num = adj_ptr->data - 'A';
			if (visited[num] == 0)
			{
				node* newnode = creat_node(adj_ptr->data);
				newnode->next = stack_top;
				stack_top = newnode;

				visited[num] = 1;
			}
			
			//指向下一個要處理的節點
			adj_ptr = adj_ptr->next;
		}
		if(stack_top != NULL)
		adj_ptr = search_adjlist(stack_top->data, adj_list);
	}

}