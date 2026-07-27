#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct tree
{
	struct tree* left;
	char data;
	struct tree* right;
};
typedef struct tree node;

node* create_node(char data);
node* create_tree(node* root, char str[]);

int main()
{
	char str[20] = "ABDH000E00CF00G00";
	node* root = NULL;
	create_tree(root, str);
	return 0;
}

node* create_node(char data)
{
	node* newnode = (node*)malloc(sizeof(node));
	if (newnode == NULL)
	{
		printf("create_node is failed.\n");
		exit(1);
	}

	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;

	return newnode;
}

node* create_tree(node* root, char str[])
{
	//左子樹 => 右子樹 => 前一節點的左子樹 =>...
	root = NULL;
	node* current = NULL;
	node* nxt = NULL;
	//根節點先建立
	node* newnode = create_node(str[0]);
	root = newnode;
	current = root;
	nxt = current->left;


	int i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 0)
		{
			node* newnode = create_node(str[i]);
			nxt = newnode;
			
		}


	}

}