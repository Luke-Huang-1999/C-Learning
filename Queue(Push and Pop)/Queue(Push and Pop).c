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
node* create_queue(char str[], node* front);
void print_queue(node* ptr);
node* enqueue(char data, node* front);
node* dequeue(char data, node* front);
int main()
{
	char str[] = { 'A','B' ,'C' ,'1' ,'2' ,'3' ,'4' };
	node* queue = NULL;
	queue = create_queue(str, queue);
	queue = enqueue('5', queue);
	queue = dequeue('5', queue);

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

node* create_queue(char str[], node* front)
{
	int i;
	front = NULL;
	node* rear = NULL;
	for (i = 0 ; i < size; i++)
	{
		node* newnode = create_node(str[i]);
		if (front == NULL)
			front = newnode;
		else
			rear->next = newnode;

		rear = newnode;

	}
	return front;
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


node* enqueue(char data, node* front)
{
	node* rear = front;
	while (rear->next != NULL)
		rear = rear->next;

	node* newnode = create_node(data);
	rear->next = newnode;
	

	return front;
}

node* dequeue(char data, node* front)
{
	node* rear = front;
	node* previous = NULL;
	node* tmp = NULL;
	while (rear != NULL)
	{
		if (rear->data == data)
			break;

		previous = rear;
		rear = rear->next;
	}
	if (rear == NULL)
	{
		printf("Can not find the char.\n");
		exit(1);
	}

	if (rear->next == NULL)//末節點刪除
	{
		tmp = rear;
		rear = previous;
		rear->next = NULL;
		free(tmp);
	}
	else if (previous == NULL)//首節點刪除
	{
		tmp = rear;
		front = rear->next;
		rear = rear->next;
		free(tmp);
	}
	else
	{
		tmp = rear;
		rear = rear->next;
		previous->next = rear;
		free(tmp);
	}

	return front;
}