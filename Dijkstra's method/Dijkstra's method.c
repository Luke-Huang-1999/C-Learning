#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define row 7
#define col 7
#define inf 99

typedef struct node
{
	char p1;
	char p2;
	int weight;
	struct node* next;
}node;


FILE* file_open(char file_name[]);
void create_adjmatrix(FILE* fptr, int adjmatrix[row][col]);
void print_adjmatrix(int adjmatrix[row][col]);
void Dijkstra_method(char start, int adjmatrix[row][col]);

int main()
{
	//開檔案
	char file_name[] = "adjmatrix.txt";
	FILE* fptr = file_open(file_name);
	int adjmatrix[row][col] = { 0 };
	//建立鄰接矩陣
	create_adjmatrix(fptr, adjmatrix);
	//列印鄰接矩陣
	print_adjmatrix(adjmatrix);

	//最短路徑
	Dijkstra_method('A', adjmatrix);


	fclose(fptr);
	return 0;
}

FILE* file_open(char file_name[])
{
	FILE* fptr = fopen(file_name, "r");
	if (fptr == NULL)
	{
		printf("file_open::fail\n");
		exit(1);
	}

	return fptr;
}

void create_adjmatrix(FILE* fptr, int adjmatrix[row][col])
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < row; j++)
		{
			fscanf(fptr, "%d", &adjmatrix[i][j]);
		}
	}
}

void print_adjmatrix(int adjmatrix[row][col])
{
	int i, j;
	printf("adjmatrix[row][col]\n\n");
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < row; j++)
		{
			printf("%2d ", adjmatrix[i][j]);
		}
		printf("\n");
	}
	printf("===================================\n");
}

void Dijkstra_method(char start, int adjmatrix[row][col])
{
	//宣告
	int dist[row] = { 0 };
	int i;
	for (i = 0; i < row; i++)
	{
		dist[i] = inf;
	}
	int visited[row] = { 0 };
	int dot_cnt = 0;
	char nxt = start;
	int new_dist;
	//初始值設定
	dist[start - 'A'] = 0;

	while (dot_cnt < row)
	{
		for (i = 0; i < row; i++)
		{
			new_dist = dist[nxt - 'A'] + adjmatrix[nxt - 'A'][i];
			if (visited[i] == 0 && new_dist < dist[i])
			{
				dist[i] = new_dist;
			}
		}

		//更新已拜訪節點
		visited[nxt - 'A'] = 1;
		dot_cnt++;

		//尋找下一個nxt
		int min = 99;
		int min_index = 0;
		for (i = 0; i < row; i++)
		{
			if (visited[i] == 0 && min > dist[i])
			{
				min = dist[i];
				nxt = 'A' + i;
			}
		}
	}

	for (i = 0; i < row; i++)
		printf("%c ==> %c dist = %d\n", start, 'A' + i, dist[i]);
}
