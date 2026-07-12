#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define size 7
struct queue
{
	char data;
	struct queue* next;
};
typedef struct queue node;

node* create_node(char data);
node* create_queue(char str[], node* ptr);
void print_queue(node* ptr);
int main()
{
	char str[] = { 'A','B' ,'C' ,'1' ,'2' ,'3' ,'4' };
	node* queue = NULL;
	queue = create_queue(str, queue);
	print_queue(queue);
	return 0;
}

node* create_node(char data)
{
	node* newnode = NULL;
	newnode = (node*)malloc(sizeof(node));
	if (newnode == NULL)
	{
		printf("create_node::failed\n");
		exit(1);
	}
	newnode->data = data;
	newnode->next = NULL;
	return newnode;
}

node* create_queue(char str[], node* ptr)
{
	int i;
	for (i = 0 ; i < size; i++)
	{
		node* newnode = create_node(str[i]);
		if (ptr != NULL)
			newnode->next = ptr;
		ptr = newnode;
	}
	return ptr;
}

void print_queue(node* ptr)
{
	if (ptr == NULL)
		printf("queue is empty\n");
	else
	{
		while (ptr != NULL)
		{
			printf("data = %c\taddress = %p\tnext address = %p\n", ptr->data, ptr, ptr->next);
			ptr = ptr->next;
		}
	}
}




