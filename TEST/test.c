#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef struct tagnode
{
	struct tagnode* left_c;
	char data;
	struct tagnode* right_c;
}Tnode;

Tnode* CreateBinaryTree();

int main()
{
	Tnode* myTree;
	myTree = CreateBinaryTree();

	return 0;
}

Tnode* CreateBinaryTree()
{
	Tnode* ptr;
	char data;
	data = _getche();

	if (data == '0')
	{
		return NULL;
	}

	ptr = (Tnode*)malloc(sizeof(Tnode));
	ptr->data = data;
	ptr->left_c = CreateBinaryTree();
	ptr->right_c = CreateBinaryTree();
	return ptr;

}