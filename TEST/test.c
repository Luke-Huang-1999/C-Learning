#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

/*
請撰寫一個程式。

讓使用者輸入 10 個整數。

請輸出：

最大值
最小值
平均值（可使用整數除法）
*/

/*
題目分析 → 虛擬碼 →（必要時）流程圖 → C 程式
題目：一程式使用者輸入10個數字後，找出最大值/最小值/平均值
題目分析 => 輸入：10個數字；輸出：最大值/最小值/平均值

虛擬碼：
	宣告一個int型態的一維陣列
	宣告一個int型態的變數max
	宣告一個int型態的變數min
	宣告一個int型態的變數total，用於累積10個數字的總和
	宣告一個float型態的變數avg
	宣告一個int型態的變數i，用於迴圈控制

	列印"請輸入10個數字"
	迴圈(i從0到9，每次+1)
		記錄第i個數字的值

	設定max與min初始值為第一個數字

	迴圈(i從1到9，每次+1)
	{
		若第i個數字大於max
			max = 第i個數字

		若第i個數字小於min
			min = 第i個數字

		total等於total + 第i個數字
	}
	avg等於total/10;

	列印"max = ?"
	列印"min = ?"
	列印"avg = ?"
*/

int main()
{

}