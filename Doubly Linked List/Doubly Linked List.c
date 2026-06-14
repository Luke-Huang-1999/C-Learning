#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

//建立節點結構體
struct list
{
	struct list* front;
	int data;
	struct list* next;
};
typedef struct list node;

//枚舉，用於insert函數；在區塊前或區塊後。
enum
{
	BEFORE, AFTER
};

//(回傳雙向鏈結首地址)建立雙向鏈結節點(一維陣列,陣列元素個數)
node* create(int array[], int size);

//打印全節點(接收雙向鏈結首地址)
void all_print(node* head);

//反向列印(接收雙向鏈結首地址)
void reverse_print(node* head);

//打印單一區塊(接收單一區塊地址)
void print(node* sch);

//(回傳搜尋節點地址)搜尋節點(雙向鏈結首區塊地址, 一維陣列中的變數)
node* search(node* head, int val);

//(回傳雙向鏈結首地址)新增區塊(雙向鏈結首區塊地址, 搜尋節點地址, 要新增的資料, 模式選擇)模式選擇[0]=區塊前新增，模式選擇[1]=區塊後新增
node* insert(node* head, node* sch, int val, int mode);

//(回傳雙向鏈結首地址)刪除區塊(雙向鏈結首區塊地址, 搜尋節點地址)
node* delete_node(node* head, node* sch);

int main()
{
	int array[] = { 1,2,3,4,5,6,7,8,9,10 };
	int size = sizeof(array) / sizeof(array[0]);//計算陣列元素個數
	node* head = create(array, size);
	printf("========================================================================================================\n");
	all_print(head);
	printf("========================================================================================================\n");
	reverse_print(head);
	printf("========================================================================================================\n");
	return 0;
}

node* delete_node(node* head, node* sch)
{
	if (sch == NULL)
	{
		printf("function[delete] :: sch == NULL");
		return head;
	}
	else if (sch->front == NULL && sch->next == NULL)
	{
		free(sch);
		head = NULL;
		return head;
	}
	else
	{
		if (sch->front == NULL)
		{
			sch->next->front = NULL;
			head = sch->next;
		}
		else if (sch->next == NULL)
		{
			sch->front->next = NULL;
		}
		else
		{
			sch->front->next = sch->next;
			sch->next->front = sch->front;
		}
	}
	free(sch);
	return head;
}

node* insert(node* head, node* sch, int val, int mode)
{
	node* newnode = NULL;
	newnode = (node*)malloc(sizeof(node));
	newnode->front = NULL;
	newnode->next = NULL;

	if (newnode == NULL)
	{
		printf("newnode create::failed\n");
		return NULL;
	}
	else
	{
		switch (mode)
		{
		case(0):										//模式選擇[0] = 區塊前新增
		{
			if (sch->front == NULL)						//首區塊建立
			{
				newnode->front = NULL;
				newnode->data = val;
				newnode->next = head;
				head->front = newnode;
				head = newnode;
			}
			else// if (sch->next != NULL)					//非首區塊建立
			{
				newnode->front = sch->front;
				newnode->data = val;
				newnode->next = sch;
				sch->front->next = newnode;
				sch->front = newnode;
			}
			/*else
			{
				printf("模式選擇錯誤。\n");
				return NULL;
			}*/
			break;
		}
		case(1):										//模式選擇[1] = 區塊後新增
		{
			if (sch->next == NULL)						//末區塊建立
			{
				newnode->front = sch;
				newnode->data = val;
				newnode->next = NULL;
				sch->next = newnode;
			}
			else										//非末區塊建立
			{
				newnode->front = sch;
				newnode->data = val;
				newnode->next = sch->next;
				sch->next = newnode;
				newnode->next->front = newnode;
			}
			break;
		}
		}
	}
	return head;
}

node* search(node* head, int val)
{
	node* current;
	current = head;
	while (current != NULL)
	{
		if (current->data == val)
			return current;
		else
			current = current->next;
	}
	return NULL;
}

node* create(int array[], int size)
{
	node* first = NULL;
	node* current = NULL;
	node* previous = NULL;
	int i;

	for (i = 0; i < size; i++)
	{
		current = (node*)malloc(sizeof(node));
		if (current == NULL)
		{
			printf("create::記憶體空間申請失敗。\n");
			return 1;
		}
		else
		{
			if (i == 0)
			{
				first = previous = current;
				first->front = NULL;
				first->data = array[i];
				first->next = NULL;
			}
			else
			{
				previous->next = current;
				current->front = previous;
				current->data = array[i];
				current->next = NULL;
				previous = current;
			}
		}
	}
	return first;
}

void all_print(node* head)
{
	node* ptr = head;
	if (head == NULL)
	{
		printf("print::head == NULL\n");
		exit(1);
	}
	else
	{
		while (ptr != NULL)
		{
			printf("data = %2d, front address = %p, address = %p, next address = %p\n", ptr->data, ptr->front, ptr, ptr->next);
			ptr = ptr->next;
		}
	}
}

void print(node* sch)
{
	if (sch == NULL)
		printf("print::sch == NULL::區塊打印失敗。\n");
	else
		printf("data = %2d, front address = %p, address = %p, next address = %p\n", sch->data, sch->front, sch, sch->next);
}

void reverse_print(node* head)
{
	node* tail = head;
	if (head == NULL)
	{
		printf("reverse_print::head == NULL\n");
		exit(1);
	}
	else
	{
		while (tail->next != NULL)
		{
			tail = tail->next;
		}

		while (tail != NULL)
		{
			printf("data = %2d, front address = %p, address = %p, next address = %p\n", tail->data, tail->front, tail, tail->next);
			tail = tail->front;
		}
	}
}