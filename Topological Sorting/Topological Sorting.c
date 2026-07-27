#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#define row 9
#define col 9

typedef struct node
{
    char act;
    struct node* next;
}node;

void create_adjmatrix(FILE* fptr, int adjmatrix[row][col]);
FILE* file_open(char name[], char mode[]);
void print_adjmatrix(int adjmatrix[row][col]);
void vertex_sorting(int vertex[row], int adjmatrix[row][col]);
void print_vertex(int vertex[row]);
void topological_sorting(int vertex[row], int adjmatrix[row][col], char activity[][15]);
int main()
{
    //宣告
    char activity[][15] = { "起床","刷牙","洗臉","穿衣","發動汽車","打開音響","吃早餐","打領帶","開車上班" };
    int adjmatrix[row][col] = { 0 };
    char file_name[20] = "adj_matrix.txt";
    int vertex[row] = { 0 };

    //開啟檔案，讀取檔案
    FILE* fptr = file_open(file_name,"r");
    //建立鄰接矩陣
    create_adjmatrix(fptr, adjmatrix);
    //分支度紀錄
    vertex_sorting(vertex, adjmatrix);
    
    print_adjmatrix(adjmatrix);
    
    print_vertex(vertex);
    printf("\n");
    topological_sorting(vertex, adjmatrix, activity);


    fclose(fptr);
	return 0;
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

FILE* file_open(char name[],char mode[])
{
    FILE* fptr = fopen(name, mode);
    if (fptr == NULL)
    {
        printf("failed to opened file.\n");
        exit(1);
    }
    //else
    //    printf("good\n");

    return fptr;
}

void print_adjmatrix(int adjmatrix[row][col])
{
    int i, j;
    printf("adjmatrix[row][col] = \n");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%d ", adjmatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void vertex_sorting(int vertex[row], int adjmatrix[row][col])
{
    int i, j;
    int sum;
    for (j = 0; j < col; j++)
    {
        sum = 0;
        for (i = 0; i < row; i++)
        {
            sum = sum + adjmatrix[i][j];
        }
        vertex[j] = sum;
    }

}

void print_vertex(int vertex[row])
{
    int i;
    printf("vertex[row] = ");
    for (i = 0; i < row; i++)
    {
        printf("%d ", vertex[i]);
    }
    printf("\n");
}

void topological_sorting(int vertex[row], int adjmatrix[row][col], char activity[][15])
{
    printf("topological_sorting = ");
    int dot_cnt = 0;
    int visited[row] = { 0 };
    //找出vertex[i] = 0 ==> 將i行的資料都 = 0 ==> 更新vertex資料
    while (dot_cnt < row)
    {
        int i = 0;
        while (vertex[i] != 0 || visited[i] != 0)
        {
            i++;
        }
        printf("%s ", activity[i]);

        dot_cnt++;
        visited[i] = 1;

        int j;
        for (j = 0;j < col; j++)
        {
            adjmatrix[i][j] = 0;
        }

        //print_adjmatrix(adjmatrix);

        vertex_sorting(vertex, adjmatrix);

    }


}