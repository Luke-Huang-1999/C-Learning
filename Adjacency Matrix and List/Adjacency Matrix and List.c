#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define row 7
#define col 7
//建立結構體
typedef struct list
{
    char data;
    struct list* next;
}node;
//()檢查檔案是否開啟成功(指向檔案的指標)
void check_fopen(FILE* fptr);

//()建立鄰接矩陣(指向檔案的指標, 二維陣列)
//該函數會將檔案內的二維矩陣輸出至matrix[row][col]
void create_adjmatrix(FILE* fptr, int matrix[row][col]);

//()建立鄰接陣列(二維陣列, 一維的node*陣列)
//這個函數會將二維矩陣的資料建立鏈結陣列
void create_adjlist(int matrix[row][col], node* adj_list[row]);

//(node類型的指標)建立節點(欲存的char data)
//這個函數除了malloc一個節點還初始化該節點，newnode->data = data，newnode->next = NULL
node* create_node(char data);

//()列印鄰接矩陣(二維鄰接陣列)
void print_adjmatrix(int matrix[row][col]);

//()列印鄰接陣列(一維的node*陣列)
void print_adjlist(node* adj_list[row]);

int main()
{
    FILE* fptr = fopen("adj_list.txt", "r");
    check_fopen(fptr);
    int matrix[row][col] = { 0 };
    node* adj_list[row] = { NULL };
    create_adjmatrix(fptr, matrix);
    create_adjlist(matrix, adj_list);
    print_adjlist(adj_list);


    fclose(fptr);
    return 0;
}

void check_fopen(FILE* fptr)
{
    if (fptr == NULL)
    {
        printf("File open failed.\n");
        exit(1);
    }
    else
        printf("File opened successfully.\n");
}

void create_adjmatrix(FILE* fptr, int matrix[row][col])
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            fscanf(fptr, "%d", &matrix[i][j]);
        }
    }
}

void create_adjlist(int matrix[row][col], node* adj_list[row])
{
    int i, j;
    node* current = NULL;
    char vertex[row] = { 'A','B','C','D','E','F','G' };

    for (i = 0; i < row; i++)
    {
        adj_list[i] = create_node(vertex[i]);
        current = adj_list[i];

        for (j = 0; j < col; j++)
        {
            if (matrix[i][j] == 1 && i != j)
            {
                current->next = create_node(vertex[j]);
                current = current->next;
            }
        }
    }
}

node* create_node(char data)
{
    node* newnode = (node*)malloc(sizeof(node));
    if (newnode == NULL)
    {
        printf("create_node::newnode malloc failed\n");
        exit(1);
    }

    newnode->data = data;
    newnode->next = NULL;

    return newnode;
}

void print_adjmatrix(int matrix[row][col])
{
    int i, j;

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
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