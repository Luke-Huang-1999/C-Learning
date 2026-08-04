#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#define nums 9

//泡泡排序法(一維陣列首元素地址)
void bubble_sorting(int* arr);

//選擇排序法(一維陣列首地址);

//()列印一維陣列(一維陣列首元素地址)
void print_arr(int* arr);



/*
Bubble Sort（迴圈）
Selection Sort（迴圈）
Insertion Sort（迴圈）
Shell Sort（迴圈）
Merge Sort（遞迴）
Quick Sort（遞迴）
Heap Sort（迴圈）
*/

int main()
{
	//宣告
	int arr[nums] = { 37,41,19,81,41,25,56,61,49 };

	printf("Before sorting：");
	print_arr(arr);


	bubble_sorting(arr);
	printf("Bubble sorting：");
	print_arr(arr);

	return 0;
}

void bubble_sorting(int* arr)
{
	//宣告
	int i, j, tmp;
	int swapped = 0;//若內層循環皆無交換，表示排序完成，提早結束

	//泡泡排序
	for (i = 0; i < (nums - 1); i++)//外層循環從0到(數列個數 - 1)
	{
		for (j = 0; j < (nums - 1 - i); j++)//內層循環從0到(數列個數 - 1 - 內層循環第i次)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;

				swapped = 1;
			}	
		}
		if (swapped == 0)
			break;
	}
}

void print_arr(int* arr)
{
	int i;
	for (i = 0; i < nums; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n\n");
}