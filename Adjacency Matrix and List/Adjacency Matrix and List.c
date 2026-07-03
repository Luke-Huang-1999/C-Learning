#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#define SIZE 4

struct listnode
{
    char data;
    struct listnode* next;
};
typedef struct listnode node;

//()將鄰接矩陣轉換成鏈接陣列(二維矩陣, 一維鏈結陣列)
void list(int matrix[SIZE][SIZE], node* adj_list[SIZE]);
//()列印鏈結陣列(一維鏈結陣列)
void print_list(node* adj_list[]);
//(node*類型的指標地址)建立新的鏈結陣列節點(節點資料)
node* create_node(char data);

//()將鏈結陣列轉換成鄰接矩陣(二維矩陣, 一維鏈結陣列)
void create_matrix(int matrix[SIZE][SIZE], node* adj_list[SIZE]);

//()將鄰接矩陣列列印(二維矩陣)
void print_matrix(int matrix[SIZE][SIZE]);

int main()
{
    int matrix[SIZE][SIZE] = { {0,1,1,1},
                               {1,0,0,1},
                               {1,0,0,1},
                               {1,1,1,0}, };
    node* adj_list[SIZE] = { NULL };
    list(matrix, adj_list);
    print_list(adj_list);
    int test_matrix[SIZE][SIZE] = { 0 };

    create_matrix(test_matrix, adj_list);
    print_matrix(test_matrix);
    return 0;
}

void list(int matrix[SIZE][SIZE], node* adj_list[SIZE])
{
    char vertex[SIZE] = { 'A','B','C','D' };

    for (int row = 0; row < SIZE; row++)
    {
        node* head = NULL;
        node* tail = NULL;

        /* 建立每一列的第一個節點 (A、B、C、D...) */
        head = create_node(vertex[row]);
        tail = head;

        /* 找相鄰頂點 */
        for (int col = 0; col < SIZE; col++)
        {
            if (matrix[row][col] == 1)
            {
                node* newnode = create_node(vertex[col]);

                tail->next = newnode;
                tail = newnode;
            }
        }
        adj_list[row] = head;
    }
}

void print_list(node* adj_list[])
{
    int i;
    for (i = 0; i < SIZE; i++)
    {
        node* current = adj_list[i];
        while (current != NULL)
        {
            printf("data = %c ==> address = %p  ==> next = %p\n", current->data, current, current->next);
            current = current->next;
        }
        printf("====================================\n");
    }
}

node* create_node(char data)
{
    node* ptr = (node*)malloc(sizeof(node));
    if (ptr == NULL)
    {
        printf("test::malloc failed\n");
        exit(EXIT_FAILURE);
    }
    ptr->next = NULL;
    ptr->data = data;
    return ptr;
}

void create_matrix(int matrix[SIZE][SIZE], node* adj_list[SIZE])
{
    int row, col, i;
    char vertex[SIZE] = { 'A', 'B', 'C', 'D' };
    for (row = 0; row < SIZE; row++)
    {
        node* current = adj_list[row];
        while (current != NULL)
        {
            for (col = 0; col < SIZE; col++)
            {
                if (current->data == vertex[col] && current->data != vertex[row])
                    matrix[row][col] = 1;
            }
            current = current->next;
        }
    }

}

void print_matrix(int matrix[SIZE][SIZE])
{
    int row, col;
    for (row = 0; row < SIZE; row++)
    {
        for (col = 0;col < SIZE; col++)
        {
            printf("%d ", matrix[row][col]);
        }
        printf("\n");
    }
}