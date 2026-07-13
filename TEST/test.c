#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

/*請撰寫一個程式。

讓使用者輸入 5 個整數。

最後輸出其中的最大值。
*/

/*
題目分析 → 虛擬碼 →（必要時）流程圖 → C 程式
題目：請撰寫一個程式，讓使用者輸入 5 個整數，最後輸出其中的最大值。
題目分析 => 輸入：5個整數；輸出：其中的最大值。
虛擬碼：
	使用者輸入5個數字
	一個一維數列接收5個數字
	假設最大的數為第1個數

	建立迴圈(從第1個數到第5個數，每次往前加一個數)
		若最大值小於欲測試的數
			最大值等於欲測試的數
	
	輸出最大值
*/
int main()
{
	int i;
	int max = 0;
	int data[5] = { 0 };

	printf("請輸入5個數字：");
	for (i = 0; i < 5; i++)
		scanf("%d", &data[i]);
	
	max = data[0];
	for (i = 0; i < 5; i++)
	{
		if (max < data[i])
			max = data[i];
	}
	printf("max = %d\n", max);

	return 0;
}