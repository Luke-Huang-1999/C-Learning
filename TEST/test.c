#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct HuffmanNode
{
	char data;                  // 字元
	int weight;                 // 權重(出現次數)
	
}snode;

typedef struct Huffman
{
	char data;                  // 字元
	int weight;                 // 權重(出現次數)
	struct Huffman* right;
	struct Huffman* left;
}node;

node* create_node(char data, int weight);

int main()
{
	char str[] = "ACBABAADA";
	int size_str = sizeof(str) - 1;
	snode sort[4] = { 0 };

	int i;
	int num = 0;
	for (i = 0; i < size_str; i++)
	{
		num = str[i] - 'A';
		sort[num].data = str[i];
		sort[num].weight++;
	}

	for (i = 0; i < 4; i++)
	{
		printf("%c %d\n", sort[i].data, sort[i].weight);
	}

	for (i = 0; i < 4; i++)
	{
		node* Huffman[4] = { 0 };
		node* newnode = 
		Huffman[i] = 
	}

	return 0;
}

node* create_node(char data, int weight)
{
	node* newnode = (node*)malloc(sizeof(node));
	if (newnode == NULL)
	{
		printf("failed.\n");
		exit(1);
	}

	newnode->data = data;
	newnode->weight = weight;
	newnode->right = NULL;
	newnode->left = NULL;

	return newnode;
}