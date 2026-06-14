#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//(肚患癹挡狦)单畉计(程, 畉, 程)
int diff_sum(int min, int diff, int max);

int main()
{
	//跑计
	int min, max, diff,result;

	//钡程 畉 程
	printf("叫块程 畉 程");
	scanf("%d %d %d", &min, &diff, &max);

	//块
	result = diff_sum(min, diff, max);
	printf("羆㎝ = %d\n", result);

	return 0;
}

int diff_sum(int min, int diff, int max)
{
	
	if (max == min)
		return min;
	else if (max < min)
		return 0;
	 
	return max + diff_sum(min, diff, max - diff);
}