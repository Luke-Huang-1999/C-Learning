#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct listnode
{	
	int data;
	struct listnode* next;
};
typedef struct listnode node;

//(node*類型的指標地址)建立新的鏈結陣列節點(節點資料)
node* create_node(char data);

node* create_node(char data)
{
    node* ptr = (node*)malloc(sizeof(node));
    if (ptr == NULL)
    {
        printf("create_node::malloc failed\n");
        exit(EXIT_FAILURE);
    }
    ptr->next = NULL;
    ptr->data = data;
    return ptr;
}