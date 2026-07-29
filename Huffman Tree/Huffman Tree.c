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

float cal_percent(char str[], int size_str, char target);
node* create_node(char data, int weight);

int main()
{
	//宣告
	char str[] = "AAAAABBC";
	int size_str = sizeof(str) - 1;//-1為扣除\0

	//test
	float a = cal_percent(str, size_str, 'A');
	printf("percent = %.3f\n", a);

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