#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define row 7
#define col 7
struct BFS
{
	char data;
	struct BFS* next;
};
typedef struct BFS node;
//因為是BFS所以要使用佇立
//佇立需要兩個指標，front and rear
//欲處理的節點為front，新節點加在rear>next
node* create_node(char dat);
node* BFS(char start, int matrix[row][col]);
int search(char data);
int main()
{
	char vertex[row] = { 'A','B','C' ,'D' ,'E' ,'F' ,'G' };
    int adj_matrix[row][col] ={	{ 0, 1, 1, 1, 1, 0, 0 },
								{ 1, 0, 0, 0, 0, 0, 0 },
								{ 1, 0, 0, 0, 0, 0, 0 },
								{ 1, 0, 0, 0, 0, 0, 1 },
								{ 1, 0, 0, 0, 0, 1, 1 },
								{ 0, 0, 0, 0, 1, 0, 1 },
								{ 0, 0, 0, 1, 1, 1, 0 }	};
	node* queue =  NULL;
	


	return 0;
}

node* create_node(char data)
{
	node* newnode = (node*)malloc(sizeof(node));
	if (newnode == NULL)
	{
		printf("create_node is failed\n");
		exit(1);
	}
	newnode->data = data;
	newnode->next = NULL;

	return newnode;
}

node* BFS(char start, int matrix[row][col])
{
	node* current = NULL;
	node* rear = NULL;
	node* queue = NULL;
	int visited[row] = { 0 };

	//首頂點先入(單一)
	node* newnode = create_node(start);
	queue = newnode;
	current = newnode;
	rear = newnode;
	visited[search(start)] = 1;
	start = start + 1;

	while (current != NULL)
	{
		//先入再出
		if (visited[search(start)] == 0)
		{
			int i;
			for (i = 1; i < row; i++)
			{
				node* newnode = create_node(start);

			}
		}

		
	}

}

int search(char data)
{
	int num = 0;
	num = data - 'A';
	return num;
}