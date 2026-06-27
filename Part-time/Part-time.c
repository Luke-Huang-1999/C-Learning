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

//
float check_time(PT work[], int size);


int wage(float total_time);

//()列印值班狀況(指向PT結構體陣列首元素的指標, 開始月份, 開始日期, 結束月份, 結束日期)ok
void print(PT work[], int start_month, int start_day, int end_month, int end_day);


int day_time(PT work[]);

//(陣列中的index)搜尋日期在陣列中的index(指向PT結構體陣列首元素的指標, 陣列大小, 月份, 日期)ok
int search(PT work[],int size, int month, int day);

int main()
{
	int total = 0;
	int month;
	int day;
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
	int index = search(work, size, 6, 19);

	return 0;
}

int search(PT work[], int size, int month, int day)
{
	int i = 0;
	while (i<=size)
	{
		if (work[i].month == month && work[i].day == day)
		{
			printf("%d", i);
			return i;
		}
		i++;
	}
	printf("該日沒有上班。\n");
	return -1;
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
	int i = 0;			//       i會接收開始的index
	int j = 0;			//       j會接收結束的index
	int start;			//	 start會接收"上"班時間的總分鐘數(如：1300即轉換為13*60+00=780分鐘)
	int end;			//	   end會接收"下"班時間的總分鐘數(如：1530即轉換為15*60+30=930分鐘)
	float day_time;		//day_time紀錄開始於結束之間的分鐘數並轉換成小時

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

