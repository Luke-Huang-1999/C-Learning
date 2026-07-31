#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct node
{
	char day;
	char name[10];
}node;


void recieve_data(int* year, int* month);
//(回傳當年當月的1號星期幾)蔡勒公式(年份, 月份)
int Zeller(int year, int month);
//()建立月曆(當年當月的1號星期幾)
void calendar(int year, int month);
//(回傳當月天數)計算當月天數(年份, 月份)
int month_days(int year, int month);

// A/B/C三人，做三休一

int main()
{
	int year, month;
	year = 2026;
	month = 1;
	recieve_data(&year, &month);
	calendar(year,month);

	return 0;
}

void recieve_data(int* year, int* month)
{
	printf("請輸入年份與月份：");
	scanf("%d %d", year, month);

}

int Zeller(int year, int month)
{
	//q = 日期（day） m = 月份（3~14） K = 年份後兩位 J = 世紀
	int input_year = year;
	int input_month = month;
	
	int day = 1;
	int year_ar = 0;
	int century = 0;
	int Zeller_week = 0;
	int week = 0;
	if (month == 1 || month == 2)
	{
		month = month + 12;
		year = year - 1;
	}

	year_ar = year % 100;
	century = year / 100;
	Zeller_week = (day + (13 * (month + 1)) / 5 + year_ar + (year_ar / 4) + (century / 4) + (5 * century)) % 7;

	week = (Zeller_week + 5) % 7 + 1;

	//printf("%4d/%2d/%2d week = %d\n", input_year, input_month, day, week);

	return week;
}

void calendar(int year, int month)
{
	int week = Zeller(year, month);
	//星期標題建立
	char all_week[7][10] = { "Mon","Tue","Wed" ,"Thu" ,"Fri" ,"Sat" ,"Sun" };
	int i;
	for (i = 0; i < 7; i++)
	{
		printf("%5s", all_week[i]);
	}
	printf("\n");

	int day_cnt = 1;
	int week_cnt = 1;
	int max_day = month_days(year, month);
	while (day_cnt <= max_day)
	{
		for (i = 1; i <= 7; i++)//符合週一到周日，1~7
		{
			if (i < (week) && week_cnt == 1)
				printf("%5s", " ");
			else
			{
				printf("%5d", day_cnt);
				day_cnt++;

			}
			if (day_cnt > max_day)
				break;
		}
		week_cnt++;
		printf("\n");
	}
}

int month_days(int year, int month)
{
	int days;

	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		days = 31;
		break;

	case 4:
	case 6:
	case 9:
	case 11:
		days = 30;
		break;

	case 2:
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			days = 29;
		else
			days = 28;
		break;
	}

	return days;
}