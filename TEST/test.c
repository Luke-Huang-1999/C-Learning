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

void prim_method(char start, node* adjlist[]);
void visited_modify(char p1, char p2, int visited[row]);
char nonvisited(char p1, char p2, int visited[row]);
node* delete_edgelist(char nxt, node* edgelist_head);
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
	
	printf("Testing prim_method：\n================================\n");
	prim_method('A', adjlist);

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
			printf("p1 = %c, p2 = %c, weight = %d, address = %p, next address = %p\n", current->p1, current->p2, current->weight, current,current->next);
			//printf("p1 = %c, p2 = %c, weight = %d\n", current->p1, current->p2, current->weight);
			current = current->next;
		}
		//printf("\n");
	}

}

void prim_method(char start, node* adjlist[])
{
	int visited[row] = { 0 };
	char nxt = start;
	node* edgelist_head = NULL;
	node* edgelist = NULL;
	node* current_adjlist = NULL;
	int line_cnt = 0;
	//將含有特定點的節點加入edge list
	while (line_cnt < (row - 1))
	{
		int i;
		for (i = 0; i < row; i++)
		{
			current_adjlist = adjlist[i];

			while (current_adjlist != NULL)
			{
				if (current_adjlist->p1 == nxt || current_adjlist->p2 == nxt)
				{

					node* newnode = create_node(current_adjlist->p1, current_adjlist->p2, current_adjlist->weight);
					if (edgelist_head == NULL)
					{
						edgelist_head = newnode;
						edgelist = newnode;
					}
					else
					{
						edgelist->next = newnode;
						edgelist = newnode;
					}
					line_cnt++;
				}
				current_adjlist = current_adjlist->next;
			}
		}

		//找最小並列印
		node* find_min = edgelist_head->next;
		node* min = edgelist_head;
		while (find_min != NULL)
		{
			if (min->weight > find_min->weight)
				min = find_min;

			find_min = find_min->next;
		}


		//edgelist先去除皆已走訪的節點
		edgelist_head = delete_edgelist(nxt, edgelist_head);


		//列印
		printf("選擇邊%c%c => weight = %d\n", min->p1, min->p2, min->weight);

		//更新已拜訪節點
		visited_modify(min->p1, min->p2, min);

		//決定current_adjlist指向
		nxt = nonvisited(min->p1, min->p2, visited);
	}
	

	//測試
	//printf("min ==> p1 = %c, p2 = %c, weight = %d\n", min->p1, min->p2, min->weight);
	/*node* test = edgelist_head;
	while (test != NULL)
	{
		printf("p1 = %c, p2 = %c, weight = %d\n", test->p1, test->p2, test->weight);
		test = test->next;
	}*/


}

void visited_modify(char p1, char p2, int visited[row])
{
	int num_1 = p1 - 'A';
	int num_2 = p2 - 'A';
	visited[num_1] = 1;
	visited[num_2] = 1;

}

char nonvisited(char p1, char p2, int visited[row])
{
	int num_1 = p1 - 'A';
	int num_2 = p2 - 'A';

	if (visited[num_1] == 0)
		return p1;
	else
		return p2;
}

node* delete_edgelist(char nxt, node* edgelist_head)
{
	node* current = edgelist_head;
	node* previous = NULL;
	node* tmp = NULL;
	while (current != NULL)
	{
		if (current->p1 == nxt || current->p2 == nxt)
		{
			if (previous == NULL)//單一節點或初始節點
			{
				tmp = current;
				current = current->next;
				free(tmp);
				tmp = NULL;
			}
			else if (current->next)//末節點刪除
			{
				tmp = current;
				current = previous;
				free(tmp);
				tmp = NULL;
			}
			else
			{
				tmp = current;
				previous->next = current->next;
				current = current->next;
				free(tmp);
				tmp = NULL;
			}
		}
		previous = current;
		current = current->next;
	}
	return edgelist_head;
}