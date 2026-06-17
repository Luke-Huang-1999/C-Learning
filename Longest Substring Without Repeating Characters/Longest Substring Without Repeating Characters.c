#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
/*
Given a string s, find the length of the longest substring without duplicate characters.

Example 1:
	Input: s = "abcabcbb"
	Output: 3
	Explanation: The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.
Example 2:
	Input: s = "bbbbb"
	Output: 1
	Explanation: The answer is "b", with the length of 1.
Example 3:
	Input: s = "pwwkew"
	Output: 3
	Explanation: The answer is "wke", with the length of 3.
	Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

Constraints:
	0 <= s.length <= 5 * 104
	s consists of English letters, digits, symbols and spaces.
*/
int lengthOfLongestSubstring(char* s);

int main()
{
	char s[] = "abcabcbb";
	
	int result = lengthOfLongestSubstring(s);
	printf("%d\n", result);
	return 0;
}


int lengthOfLongestSubstring(char* s)
{
	int max = 0;
	char* current = &s[0];
	char* left = &s[0];
	char* right = &s[0];
	char* tail = &s[0];
	while (*tail != '\0')
		tail++;

	while (right != tail)
	{
		//1.檢查是否有重複
		int dup = 0;
		int cnt = 0;
		for (current = left; current <= right; current++)
		{
			if (*current == *right && current != right) dup = 1;
			cnt++;
		}
		//2.檢查是否須更新max值
		if (max < cnt && dup != 1) max = cnt;
		//3.決定指標下一步方向
		if (dup == 1)
			(left == right) ? right++ : left++;
		else
			right = right + 1;
	}
	return max;
}