#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define num 4
typedef struct HuffmanNode
{
	char data;                  // 字元
	int weight;                 // 權重(出現次數)
	struct HuffmanNode* left;   // 左子樹
	struct HuffmanNode* right;  // 右子樹
}node;

float cal_percent(char str[], int size_str, char target);
node* create_node(char data, int weight);
node* sortlist(char str[], int weight);

int main()
{
	//宣告
	char str[] = "AAAAABBCD";
	int size_str = sizeof(str) - 1;//-1為扣除\0
	

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

node* sortlist(char str[], int weight)
{

}