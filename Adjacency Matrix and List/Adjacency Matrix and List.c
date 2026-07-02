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

void list(int matrix[SIZE][SIZE], node* adj_list[SIZE]);

int main()
{

    int matrix[SIZE][SIZE] = { {0,1,1,1},
                               {1,0,0,1},
                               {1,0,0,1},
                               {1,1,1,0}, };
    node* adj_list[SIZE] = { NULL };

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
        head = (node*)malloc(sizeof(node));
        head->data = vertex[row];
        head->next = NULL;
        tail = head;

        /* 找相鄰頂點 */
        for (int col = 0; col < SIZE; col++)
        {
            if (matrix[row][col] == 1)
            {
                node* newnode = (node*)malloc(sizeof(node));

                if (newnode == NULL)
                {
                    printf("malloc fail\n");
                    return;
                }

                newnode->data = vertex[col];
                newnode->next = NULL;

                tail->next = newnode;
                tail = newnode;
            }
        }

        adj_list[row] = head;
    }
}