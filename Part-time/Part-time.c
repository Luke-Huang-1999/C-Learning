#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define hourly_wage 200

struct parttime
{
	int month;
	int day;
	int weekday;
	int start;
	int end;
};
typedef struct parttime PT;

enum Weekday
{
	MON = 1,
	TUE,
	WED,
	THU,
	FRI,
	SAT,
	SUN
};

enum Month
{
	January = 1,
	Febuary,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};

float check_time(PT work[], int size);
int wage(float total_time);
void print(PT work[], int start_month, int start_day, int end_month, int end_day);
int day_time(PT work[]);
int main()
{
	int total = 0;
	PT work[] = {	{ June, 15, MON, 1600, 1900 },
					{ June, 16, TUE, 1600, 1900 },
					{ June, 18, THU, 1600, 1900 },
					{ June, 22, MON, 1600, 1900 },
					{ June, 23, TUE, 1600, 1900 },
					{ June, 29, MON, 1600, 1900 },
					{ June, 30, TUE, 1600, 1900 },
					{ July,  3, FRI, 1400, 1700 },
	};
	int size = sizeof(work) / sizeof(work[0]);
	print(work, 6, 16, 7, 3);

	return 0;
}


float check_time(PT work[], int size)
{
	int i;
	int start;
	int day_cnt = 0;
	int end;
	float day_time;
	float total_time = 0;
	for (i = 0; i < size; i++)
	{
		start = (work[i].start / 100) * 60 + work[i].start % 100;
		end = (work[i].end / 100) * 60 + work[i].end % 100;
		day_time = (end - start) / 60.0;
		total_time += day_time;
		day_cnt++;
		printf("第%d天  %2d月%2d日  從%d到%d  共%.1f小時\n", i + 1, work[i].month, work[i].day, work[i].start, work[i].end, day_time);
	}
	printf("===================================\n");
	printf("工作天數%2d天\n", day_cnt);
	printf("時數共%.1f小時\n", total_time);

	return total_time;
}

void print(PT work[], int start_month, int start_day, int end_month, int end_day)
{
	int i = 0;
	int j = 0;
	int start;
	int end;
	float day_time;

	while (work[i].month != start_month || work[i].day != start_day)
		i++;

	while (work[j].month != end_month || work[j].day != end_day)
		j++;

	start = (work[i].start / 100) * 60 + work[i].start % 100;
	end = (work[i].end / 100) * 60 + work[i].end % 100;
	day_time = (end - start) / 60.0;

	for (start = i, end = j; start <= end; start++)
		printf("第%d天  %2d月%2d日  從%d到%d  共%.1f小時\n", start, work[start].month, work[start].day, work[start].start, work[start].end, day_time);

}

int wage(float total_time)
{
	int wage = total_time * hourly_wage;
	printf("薪水共%d元\n", wage);
	return wage;
}

