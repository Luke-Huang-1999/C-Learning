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
node* sort(node* adjlist[row]);
void short_path(node* sortlist_head);//Kruskal method
void print_Kruskal_path(node* current);
char find(char vertex, char parent[]);
void modify_parent(char from, char to, char parent[]);
int main()
{
	FILE* fptr = file_open("adjmatrix.txt");
	int adjmatrix[row][col] = { 0 };
	node* adjlist[row] = { NULL };
	create_adjmatrix(fptr, adjmatrix);
	printf("adjmatrix print:\n");
	print_adjmatrix(adjmatrix);

	create_adjlist(adjlist, adjmatrix);
	print_adjlist(adjlist);
	printf("================================\n\n");
	node* sortlist_head = sort(adjlist);

	printf("================================\n\n");

	short_path(sortlist_head);

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
		printf("\n");
	}

}

void short_path(node* sortlist_head)
{
	char parent[row] = { 'A','B' ,'C' ,'D' ,'E' ,'F' };
	int i;
	node* current = NULL;
	current = sortlist_head;
	int visited[row] = { 0 };
	int line_cnt = 0;

	//終止條件 = 邊的數量大於(點 - 1)
	while (current != NULL && line_cnt < (row - 1))
	{
		if (find(current->p1, parent) != find(current->p2, parent))
		{
			print_Kruskal_path(current);
			line_cnt++;
			modify_parent(current->p2, current->p1, parent);
			visited[current->p1 - 'A'] = 1;
			visited[current->p2 - 'A'] = 1;
		}

		current = current->next;
	}
}

node* sort(node* adjlist[row])
{
	int i, j;
	int line_cnt = 0;
	node* current = NULL;
	node* sortlist = NULL;
	node* sortlist_head = NULL;
	for (i = 0; i < row; i++)
	{
		current = adjlist[i];
		while (current != NULL)
		{
			node* newnode = create_node(current->p1, current->p2, current->weight);
			if (sortlist == NULL)
			{
				sortlist_head = newnode;
				sortlist = newnode;
			}
			else
			{
				sortlist->next = newnode;
				sortlist = newnode;
			}

			line_cnt++;
			current = current->next;
		}
	}

	for (i = 0; i < (line_cnt - 1); i++)
	{
		sortlist = sortlist_head;
		while (sortlist->next != NULL)
		{
			if (sortlist->weight > sortlist->next->weight)
			{
				char tmp_p1 = sortlist->p1;
				char tmp_p2 = sortlist->p2;
				int tmp_weight = sortlist->weight;

				sortlist->p1 = sortlist->next->p1;
				sortlist->p2 = sortlist->next->p2;
				sortlist->weight = sortlist->next->weight;

				sortlist->next->p1 = tmp_p1;
				sortlist->next->p2 = tmp_p2;
				sortlist->next->weight = tmp_weight;
			}
			sortlist = sortlist->next;
		}
	}

	node* test = sortlist_head;
	while (test != NULL)
	{
		printf("p1 = %c, p2 = %c, weight = %d\n", test->p1, test->p2, test->weight);
		test = test->next;
	}

	return sortlist_head;
}

void print_Kruskal_path(node* current)
{
	printf("使用線段%c%c == > weight = %d\n", current->p1, current->p2, current->weight);
}

char find(char vertex, char parent[])
{
	char test = vertex;
	while (parent[test - 'A'] != test)
		test = parent[test - 'A'];

	if (parent[vertex - 'A'] != test)
		parent[vertex - 'A'] = test;

	return test;
}

void modify_parent(char from, char to, char parent[])
{
	char parent_from = find(from, parent);
	char parent_to = find(to, parent);
	int i;
	for (i = 0; i < row; i++)
	{
		if (parent[i] == parent_from)
			parent[i] = parent_to;
	}
}

