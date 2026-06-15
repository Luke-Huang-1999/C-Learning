#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//(肚患癹挡狦)单畉计(程, 畉, 程)
int diff_sum(int min, int diff, int max);

//(肚患癹挡狦)单畉计い案计兜羆㎝(程, 畉, 程)

int even_diff_sum(int min, int diff, int max);

//(肚患癹挡狦)单畉计い计兜羆㎝(程, 畉, 程)
int odd_diff_sum(int min, int diff, int max);

//()单畉计い碝т程案计籔程案计(程, 畉, 程,程案计, 程案计)
void even_min_max(int min, int diff, int max, int* min_even, int* max_even);

//()患癹璸衡计羆㎝ + 程计 + 计(程, 畉, 程, 计羆㎝, 计, 程计)
void odd_stat(int min, int diff, int max, int* sum, int* count, int* max_odd);

//(案计㎝)单畉计い程硈尿案计㎝(程, 畉, 程)
int max_even_sum(int min, int diff, int max);

//(计计羆㎝)患癹璸衡计计羆㎝(饼璸衡计)
int digit_sum(int n);

//(计计羆㎝)患癹璸衡计い案计计计(饼璸衡计)
int count_even_digits(int n);

int main()
{
	//跑计
	int result = count_even_digits(12360);

	printf("计羆㎝ = %d\n", result);

	return 0;
}

int diff_sum(int min, int diff, int max)
{
	
	if (min == max)
		return min;
	else if (min > max)
		return 0;
	 
	return min + diff_sum(min + diff, diff, max);
}

int even_diff_sum(int min, int diff, int max)
{
	int next_sum;
	if (min > max)
		return 0;
	else if (min % 2 != 0)
		return even_diff_sum(min + diff, diff, max);
	else
		return min + even_diff_sum(min + diff, diff, max);
}

int odd_diff_sum(int min, int diff, int max)
{
	if (min > max)
		return 0;

	int result = odd_diff_sum(min + diff, diff, max);

	if (min % 2 == 0)//案计ぃ魁
		return result;
	else
		return min + result;
}

void even_min_max(int min, int diff, int max, int* min_even, int* max_even)
{
	if (min > max)
		return;

	even_min_max(min + diff, diff, max, min_even, max_even);
	
	if (min % 2 == 0)
	{
		if (*min_even > min || *min_even == 0)
			*min_even = min;
		if (*max_even < min || *max_even == 0)
			*max_even = min;
	}
}

void odd_stat(int min, int diff, int max, int* sum, int* count, int* max_odd)
{
	if (min > max)
		return;

	odd_stat(min + diff, diff, max, sum, count, max_odd);

	if (min % 2 != 0)
	{
		*sum += min;
		(*count)++;
		if (*max_odd == 0 || *max_odd < min)
			*max_odd = min;
	}
}

int max_even_sum(int min, int diff, int max)
{
	if (min > max)
		return 0;
	int sum = max_even_sum(min + diff, diff, max);
	if (min % 2 == 0)
		return sum + min;
	else
		return sum;

}

int digit_sum(int n)
{
	if (n == 0)
		return 0;
	else
		return digit_sum(n / 10) + (n % 10);
}

int count_even_digits(int n)
{
	if (n == 0)
		return 0;
	else
	{
		if ((n % 10) % 2 == 0)
			return count_even_digits(n / 10) + 1;
		else
			return count_even_digits(n / 10);
	}
}