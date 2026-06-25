#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int day_find(int, int);//尋找year_now的1月1日星期幾
int main()
{
	int year_now;
	int month_now;
	printf("請入今年年份與月份：");
	scanf("%d %d", &year_now, &month_now);

	day_find(year_now, month_now);


	return 0;
}

int day_find(int year_now, int month_now)
{
	int start = 2000;//起始年份
	int end = year_now - 1;//結束不包含year_now
	int year = start;//從2000年開始
	int loop = 1;//每次年份增加1年
	int leap_cnt = 0;//紀錄閏年數量
	int not_leap_cnt = 0;//紀錄非閏年數量
	int year_now_day = 0;//year_now年1月1日星期幾
	int month_now_day = 0;//year_now年month_now月1日星期幾
	int month = 1;
	while (year <= end)
	{
		if (year % 4 == 0)//閏年一定可以被4整除
		{
			leap_cnt++;
			if (year % 100 == 0 && year % 400 != 0)//再扣掉能被 100 整除，但不能被 400 整除的年份
				leap_cnt--;
		}
		year = start + loop;
		loop++;
	}
	//開始尋找year_now的1月1日星期幾
	not_leap_cnt = (year_now - start) - leap_cnt;
	year_now_day = (5 + (leap_cnt * 2) + (not_leap_cnt * 1) + 1) % 7;
	//printf("%4d/01/01 星期%d\n", year_now, year_now_day);

	//開始尋找year_now年month_now月1日星期幾

	int leap;
	if (year % 4 == 0)//閏年一定可以被4整除
	{
		if (year % 100 == 0 && year % 400 != 0)//再扣掉能被 100 整除，但不能被 400 整除的年份，不是閏年
			leap = 0;
		else//是閏年
			leap = 1;
	}
	else
		leap = 0;
	//大1/3/5/7/10/12
	//小2/4/6/8/9/11

	int i = year_now_day;
	while (month <= month_now)
	{
		if (month_now == 1)
		{
			month_now_day = year_now_day;
			printf("%4d年%d月1日 星期%d\n", year_now, month_now, month_now_day);
			break;
		}
		else
		{
			if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
				i = i + 2;
			else if (month == 2)
			{
				if (leap == 1)
					i = i - 1;
				else
					i = i;
			}
			else
				i = i + 1;
			month++;
		}
	}
	month_now_day = (i % 7) + 1;
	printf("%4d年%d月1日 星期%d\n", year_now, month_now, month_now_day);
}
