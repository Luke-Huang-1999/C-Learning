#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
/*
You are given two non-empty linked lists representing two non-negative integers.
The digits are stored in reverse order, and each of their nodes contains a single digit.
Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example 1:
	Input: l1 = [2,4,3], l2 = [5,6,4]
	Output: [7,0,8]
	Explanation: 342 + 465 = 807.

Example 2:
	Input: l1 = [0], l2 = [0]
	Output: [0]

Example 3:
	Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
	Output: [8,9,9,9,0,0,0,1]
*/

//Definition for singly - linked list.
struct ListNode
{
	int val;
	struct ListNode* next;
};
typedef struct ListNode node;

//(單向鏈結陣列首地址)建立鏈結陣列(單向鏈結陣列首地址, 一維陣列, 一維陣列大小)
node* create(node* head, int arr[], int size);

//全列印(單向鏈結陣列首地址)
void all_print(node* head);

//(相加後結果陣列首地址)陣列相加(第一條單向鏈結陣列首地址, 第二條單向鏈結陣列首地址)
node* addTwoNumbers(node* l1, node* l2);

int main()
{
	int arr1[] = { 2,4,3 };
	int arr2[] = { 5,6,9 };
	int size1 = sizeof(arr1) / sizeof(arr1[0]);
	int size2 = sizeof(arr2) / sizeof(arr2[0]);
	node* head1 = NULL;
	node* head2 = NULL;
	head1 = create(head1, arr1, size1);
	head2 = create(head2, arr2, size2);
	node* result = addTwoNumbers(head1, head2);
	printf("arr1==============================================================\n");
	all_print(head1);
	printf("arr2==============================================================\n");
	all_print(head2);
	printf("result==============================================================\n");
	all_print(result);

	return 0;
}

node* create(node* head, int arr[], int size)
{
	node* newnode;
	node* current = NULL;
	int i;
	for (i = 0; i < size; i++)
	{
		newnode = (node*)malloc(sizeof(node));
		if (newnode == NULL)
		{
			printf("create :: malloc faile\n");
			return head;
		}
		newnode->val = arr[i];
		newnode->next = NULL;

		if (head == NULL)
		{
			head = newnode;
			current = head;

		}
		else
		{
			current->next = newnode;
			current = newnode;
		}
	}
	return head;
}

void all_print(node* head)
{
	while (head != NULL)
	{
		printf("address = %p, data = %d, next address = %p\n", head, head->val, head->next);
		head = head->next;
	}
}

node* addTwoNumbers(node* l1, node* l2)
{
	node* current1 = l1;
	node* current2 = l2;
	node* head = NULL;
	node* tail = NULL;

	int carry = 0;			//紀錄進位，首區塊計算不須進位
	
	while (current1 != NULL || current2 != NULL|| carry != 0)
	{
		
		/*
		運算流程：
			先計算相同index下，相加結果 ==> 判斷是否須進位 ==> 申請新空間&新空間賦值 ==> 首區塊驗證 ==> 指標指向下一個index
		*/
		int x = (current1 != NULL) ? current1->val : 0;
		int y = (current2 != NULL) ? current2->val : 0;

		int sum = x + y + carry;
		carry = sum / 10;

		node* newnode = (node*)malloc(sizeof(node));
		if (newnode == NULL)
		{
			printf("addTwoNumbers::malloc fail\n");
			return head;
		}
		newnode->val = sum % 10;
		newnode->next = NULL;

		if (head == NULL)
		{
			head = newnode;
			tail = head;
		}
		else
		{
			tail->next = newnode;
			tail = newnode;
		}

		if (current1 != NULL)current1 = current1->next;
		if (current2 != NULL)current2 = current2->next;
	}
	return head;
}
