#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define size 6
struct stack_list
{
	char data;
	struct stack_list *next;
};
typedef struct stack_list node;

node* create_stack(node* top, char str[]);
node* create_node(char data);
void print_stack(node* top);
int main()
{
	char str[size] = { 'A', 'B', 'C', '1', '2', '3' };
	node* stack = NULL;
	stack = create_stack(stack, str);
	print_stack(stack);

	free(stack);
	return 0;
}

node* create_stack(node* top, char str[])
{
	int i;
	for (i = 0; i < size; i++)
	{
		node* newnode = NULL;
		newnode = create_node(str[i]);
		if (top != NULL)
		{
			newnode->next = top;
		}
		top = newnode;
	}
	return top;
}

node* create_node(char data)
{
	node* newnode = (node*)malloc(sizeof(node));
	if (newnode == NULL)
	{
		printf("create_node::newnode is NULL\n");
		printf("malloc failed\n");
		exit(1);
	}

	newnode->data = data;
	newnode->next = NULL;

	return newnode;
}

void print_stack(node* top)
{
	while (top != NULL)
	{
		printf(" %c \n", top->data);
		if (top->next != NULL)
		{
			printf("\n");
			printf(" | \n");
			printf(" V \n");
			printf("\n");
		}
		top = top->next;
	}
}