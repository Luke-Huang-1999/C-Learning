#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#define nums 9

//泡泡排序法(一維陣列首元素地址)
void bubble_sorting(int* arr);

//選擇排序法(一維陣列首地址)
void selection_sort(int* arr);

//插入排序法(一維陣列首元素地址)
void insertion_sort(int* arr);

//合併排序法(一維陣列首元素地址)
void merge_sort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

//()列印一維陣列(一維陣列首元素地址)
void print_arr(int* arr);




/*
Bubble Sort（迴圈）ok
Selection Sort（迴圈）ok
Insertion Sort（迴圈）ok

Merge Sort（遞迴）
Quick Sort（遞迴）
Heap Sort（迴圈）
*/

int main()
{
	//宣告
	int arr[nums] = { 37,41,19,81,41,25,56,61,49 };
	//原版
	printf("Before sorting：");
	print_arr(arr);
	printf("Correct answer：19 25 37 41 41 49 56 61 81\n\n");

	//泡泡排序
	//bubble_sorting(arr);
	//printf("Bubble sorting：");
	//print_arr(arr);

	//選擇排序
	//selection_sort(arr);
	//printf("Selection Sort：");
	//print_arr(arr);

	//插入排序
	//insertion_sort(arr);
	//printf("Insertion Sort：");
	//printf("    Merge Sort：");
	//print_arr(arr);

	//合併排序
	merge_sort(arr,0,nums - 1);
	printf("    Merge Sort：");
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

void selection_sort(int* arr)
{
	int i, j;
	int tmp;
	int min_index;

	for (i = 0; i < (nums - 1); i++)//i為控制最小值比對
	{
		min_index = i;//假設最小值是第i個

		for (j = (i + 1); j < nums; j++)//找出i + 1個之後的數是否比第i個小，如果比較小就紀錄
		{
			if (arr[min_index] > arr[j])
				min_index = j;
		}

		if (arr[i] > arr[min_index])//最小值交換
		{
			tmp = arr[i];
			arr[i] = arr[min_index];
			arr[min_index] = tmp;
		}
	}
}

void insertion_sort(int* arr)
{
	int i, i_index;
	int key;
	for (i = 1; i < nums; i++)
	{
		key = arr[i];
		i_index = i - 1;
		while (i_index >= 0 && key < arr[i_index])
		{
			arr[i_index + 1] = arr[i_index];
			i_index--;
		}
		//if(key < arr[i_index + 1])
		arr[i_index + 1] = key;
	}
}

void merge_sort(int arr[], int left, int right)
{
	if (left >= right)
		return;

	int mid = (left + right) / 2;

	merge_sort(arr, left, mid);

	merge_sort(arr, mid + 1, right);

	merge(arr, left, mid, right);
}

void merge(int arr[], int left, int mid, int right)
{
	int temp[nums];

	int i = left;
	int j = mid + 1;
	int k = left;

	while (i <= mid && j <= right)
	{
		if (arr[i] <= arr[j])
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}

	while (i <= mid)
		temp[k++] = arr[i++];

	while (j <= right)
		temp[k++] = arr[j++];

	for (i = left; i <= right; i++)
		arr[i] = temp[i];
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