#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
//製作一個鏈結陣列，會將處理多項式的相加結果
struct Polynomial
{
	int coef;
	int exp;
	struct Polynomial* next;
};
typedef struct Polynomial node;

node* attach(node* head, int coef, int exp);
void print(node* head);
node* combine(node* pa, node* pb, node* pc);
int main()
{
	//3x^3+5x^1+2
	node* pa = NULL;
	pa = attach(pa, 3, 3);
	pa = attach(pa,-1, 2);
	pa = attach(pa, 5, 1);
	pa = attach(pa, 2, 0);
	printf("The first polynomial:\t");
	print(pa);
	printf("\n");
	//4x^5+2x2-5x^1+3
	node* pb = NULL;
	pb = attach(pb, 4, 5);
	pb = attach(pb, 2, 2);
	pb = attach(pb, -5, 1);
	pb = attach(pb, 3, 0);
	printf("The second polynomial:\t");
	print(pb);
	node* pc = NULL;
	printf("\n");
	pc = combine(pa, pb, pc);
	printf("Adding polynomial:\t");
	print(pc);
	printf("\n");
	return 0;
}

node* attach(node* head, int coef, int exp)
{
	node* newnode = NULL;
	newnode = (node*)malloc(sizeof(node));
	if (newnode == NULL)
	{
		printf("attach::malloc fail\n");
		return head;
	}

	newnode->next = NULL;
	newnode->coef = coef;
	newnode->exp = exp;
	node* current = NULL;
	node* previous = NULL;
	if (head == NULL)
		head = newnode;
	else
	{
		current = head;
		previous = head;
		while (current->next != NULL)
		{
			previous = current;
			current = current->next;
		}
		current->next = newnode;
		previous = current;
		current = newnode;
	}
	return head;
}

void print(node* head)
{
	int first = 1;
	while (head != NULL)
	{
		if (head->exp == 0)
		{
			if ((head->coef) > 0 && first != 1)
				printf("+%d ", head->coef);
			else
				printf("%d ", head->coef);
		}
		else
		{
			if ((head->coef) > 0 && first != 1)
				printf("+%dx^(%d) ", head->coef, head->exp);
			else
				printf("%dx^(%d) ", head->coef, head->exp);
		}

		first = 0;
		head = head->next;
	}
}

node* combine(node* pa, node* pb, node* pc)
{
	node* newnode = NULL;
	node* tail = NULL;
	int exp;
	int coef;
	while (pa != NULL && pb != NULL)
	{
		if ((pa->exp) > (pb->exp))
		{
			exp = pa->exp;
			coef = pa->coef;
			pa = pa->next;
		}
		else if ((pa->exp) == (pb->exp))
		{
			exp = pa->exp;
			coef = (pa->coef) + (pb->coef);
			pa = pa->next;
			pb = pb->next;
		}
		else
		{
			exp = pb->exp;
			coef = pb->coef;
			pb = pb->next;
		}

		if (coef == 0)
			continue;
		else
		{
			newnode = (node*)malloc(sizeof(node));
			if (newnode == NULL)
			{
				printf("combine::malloc fail\n");
				return pc;
			}
			newnode->next = NULL;
			newnode->coef = coef;
			newnode->exp = exp;

			if (pc == NULL)
			{
				pc = newnode;
				tail = newnode;
			}
			else
			{
				tail->next = newnode;
				tail = newnode;
			}
		}
	}
	while (pa != NULL)
	{
		pc = attach(pc, pa->coef, pa->exp);
		pa = pa->next;
	}

	while (pb != NULL)
	{
		pc = attach(pc, pb->coef, pb->exp);
		pb = pb->next;
	}

	return pc;
}