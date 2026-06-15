#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize);

/*
Two Sum

Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]
*/

int main()
{
	int nums[] = { 2,3,7,8,10 };
	int target = 100;
	int returnSize;
	int nums_size = sizeof(nums) / sizeof(nums[0]);
	int* ans = twoSum(nums, nums_size, target, &returnSize);

	if (ans != NULL)
	{
		printf("[%d %d]\n", ans[0], ans[1]);
		free(ans);
	}
	else
		printf("No solution\n");

	return 0;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
	int* result = (int*)malloc(2 * sizeof(int));
	if (result == NULL)
	{
		printf("twoSum::malloc fail\n");
		exit(1);
	}
	int i, j;
	for (i = 0; i < numsSize; i++)
	{
		for (j = i + 1; j < numsSize; j++)
		{
			if (nums[i] + nums[j] == target)
			{
				result[0] = i;
				result[1] = j;
				*returnSize = 2;
				return result;
			}
		}
	}
	*returnSize = 0;
	return NULL;
}