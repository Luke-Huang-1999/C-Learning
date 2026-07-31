#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct HuffmanNode
{
	char data;                  // 字元
	int weight;                 // 權重(出現次數)
	struct HuffmanNode* left;   // 左子樹
	struct HuffmanNode* right;  // 右子樹
}node;

typedef struct simplenode
{
	char data;                  // 字元
	int weight;                 // 權重(出現次數)
}snode;

float cal_percent(char str[], int size_str, char target);
node* create_node(char data, int weight);
void weightlist(char str[], snode sort[], int size_str);
void sortlist(snode sort[]);
node* Huffman(snode sort[]);
void inorder(node* root);
int main()
{
	//宣告
	char str[] = "ACBABAADA";
	int size_str = sizeof(str) - 1;//-1為扣除\0

	snode sort[4] = { 0 };
	weightlist(str, sort, size_str);

	sortlist(sort);

	//int i;
	//for (i = 0; i < 4; i++)
	//{
	//	printf("%c %d\n", sort[i].data, sort[i].weight);
	//}

	node* root = Huffman(sort);

	inorder(root);

	return 0;
}

float cal_percent(char str[], int size_str, char target)
{
	char* current = &str[0];
	int cnt = 0;
	float percent = 0.0;
	while (*current != '\0')
	{
		if (*current == target)
		{
			cnt++;
		}
		current = current + 1;
	}
	percent = (cnt * 1.0) / size_str;
	return percent;
}

node* create_node(char data, int weight)
{
	node* newnode = (node*)malloc(sizeof(node));
	if (newnode == NULL)
	{
		printf("creating newnode failed.\n");
		exit(1);
	}
	newnode->data = data;
	newnode->weight = weight;
	newnode->right = NULL;
	newnode->left = NULL;

	return newnode;
}

void weightlist(char str[], snode sort[],int size_str)
{
	int i;
	int cnt = 0;
	for (i = 0; i < size_str; i++)
	{
		cnt = str[i] - 'A';
		sort[cnt].data = str[i];
		sort[cnt].weight++;
	}
}

void sortlist(snode sort[])
{
	int i, j;
	for (i = 0; i < (4 - 1); i++)
	{
		for (j = 0; j < (3-i); j++)
		{
			if (sort[j].weight > sort[j + 1].weight)
			{
				snode tmp = { 0 };
				tmp = sort[j];
				sort[j] = sort[j + 1];
				sort[j + 1] = tmp;
			}
		}
	}
}

node* Huffman(snode sort[])
{
	node* newnode = NULL;
	node* list[4] = { 0 };
	int i;
	for (i = 0; i < 4; i++)
	{
		list[i] = create_node(sort[i].data, sort[i].weight);
	}



	for (i = 0; i < 3; i++)
	{
		int weight_newnode = list[i]->weight + list[i + 1]->weight;
		newnode = create_node('#', weight_newnode);
		newnode->right = list[i + 1];
		newnode->left = list[i];

		list[i + 1] = newnode;
	}

	return newnode;
}

void inorder(node* root)
{
	if (root == NULL)
		return;

	inorder(root->left);
	printf("%c(%d) ", root->data, root->weight);
	inorder(root->right);
}