#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define SIZE 9

//結構體list
struct list
{
    int data;
    struct list* next;
};
typedef struct list node;

//(回傳鏈結陣列首地址)建立鏈結陣列(一維數列,數列大小)
node* create(int array[], int);

//()打印鏈結陣列(鏈結陣列首地址)_全列印
void all_print(node*);

//()打印鏈結陣列(欲打印的鏈結陣列地址)_列印一區塊
void print(node*);

//(回傳新增的區塊地址)新增1個區塊至鏈結陣列(鏈結陣列首地址,搜尋到的區塊地址,新區塊的data,模式選擇)模式[1]=>首區塊新增；模式[2]=>區塊新增至sch後方；模式[3]=>末區塊新增
node* insert(node* head, node* sch, int val, int mode);

//(回傳搜尋到的區塊地址)尋找鏈結陣列中某一個區塊(鏈結陣列首地址,要尋找的data)
node* search(node* head, int);

//(回傳鏈結陣列首地址)刪除位址為del的區塊(鏈結陣列首地址,要刪除的區塊位址)
node* delete(node* head, node* del);

int main()
{
    int array[SIZE] = { 1,2,3,4,6,7,8,9,0 };
    int del_num;
    node* head = create(array, SIZE);
    all_print(head);

    printf("===============================================\n");

    printf("請輸入要刪除的資料：");
    scanf("%d", &del_num);
    node* sch = search(head, del_num);
    head = delete(head, sch);

    all_print(head);


    return 0;
}




node* search(node* head, int val)
{
    node* find = head;
    while (find != NULL)
    {
        if (find->data == val)
            return find;
        else
            find = find->next;
    }
    return NULL;
}

node* insert(node* head, node* sch, int val, int mode)
{
    printf("請輸入新增模式：\n");
    printf("模式[1]=>首區塊新增；模式[2]=>區塊新增至sch後方；模式[3]=>末區塊新增\n");

    //建立一個大小為node的新區塊
    node* new = malloc(sizeof(node));

    switch (mode)
    {
    case(1):
    {
        new->data = val;
        new->next = head;
        head = new;
        break;
    }
    case(2):
    {
        new->data = val;
        new->next = sch->next;
        sch->next = new;
        break;
    }
    case(3):
    {
        sch->next = new;
        new->data = val;
        new->next = NULL;
        break;
    }
    default:
    {
        printf("insert：：錯誤。\n");
        break;
    }
    }
    return new;
}

node* create(int array[], int val)
{
    node* first, * cur, * previous;
    first = cur = previous = NULL;
    int i;
    for (i = 1; i <= val; i++)
    {
        if (i == 1)
        {
            first = (node*)malloc(sizeof(node));
            cur = first;
            previous = first;
            cur->data = array[0];
            cur->next = NULL;
        }
        else
        {
            cur = (node*)malloc(sizeof(node));
            cur->data = array[i - 1];
            cur->next = NULL;
            previous->next = cur;
            previous = cur;
        }
    }
    return first;
}

void all_print(node* head)
{
    while (head != NULL)
    {
        printf("address = %p, data = %d, next address = %p\n", head, head->data, head->next);
        head = head->next;
    }
}

void print(node* ads)
{
    if (ads != NULL)
        printf("address = %p, data = %d, next address = %p\n", ads, ads->data, ads->next);
    else
        printf("區塊打印失敗。\n");
}

node* delete(node* head, node* del)
{
    node* ptr = head;

    if (ptr == NULL)                    //空指標
    {
        printf("這是空指標。\n");
        return NULL;
    }
    else if (ptr == del)                //首區塊
    {
        head = head->next;
        free(del);
    }
    else                                //首區塊以外
    {
        while (ptr->next != del)
        {
            ptr = ptr->next;
        }
        ptr->next = del->next;
        free(del);
    }
    return head;
}