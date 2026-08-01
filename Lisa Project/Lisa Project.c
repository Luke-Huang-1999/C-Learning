#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define row 6
#define col 7
typedef struct node
{
	int day;
	char employee_1[10];
	char employee_2[10];
}node;

char employee_all[4][15] = {"AAAAA","BBBBB","CCCCC" ,"DDDDD"};

void recieve_data(int* year, int* month);
//(回傳當年當月的1號星期幾)蔡勒公式(年份, 月份)

int Zeller(int year, int month);
//()建立月曆(當年當月的1號星期幾)
void calendar(int year, int month, node cale[row][col]);

//(回傳當月天數)計算當月天數(年份, 月份)
int month_days(int year, int month);

void print_calendar(node cale[row][col]);
// A/B/C三人，做三休一

int main()
{
	//宣告變數
	int year, month;
	node cale[row][col] = { 0 };
	year = 2026;
	month = 8;

	//1.接收初始資訊
	//recieve_data(&year, &month);	//年月

	//生成月曆
	calendar(year, month, cale);

	//列印月曆
	print_calendar(cale);



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

void calendar(int year, int month, node cale[row][col])
{
	int week = Zeller(year, month); //6
	//星期標題建立
	char all_week[7][4] = { "Mon","Tue","Wed" ,"Thu" ,"Fri" ,"Sat" ,"Sun" };
	int i, j;
	for (i = 0; i < 7; i++)
	{
		printf("%15s", all_week[i]);
	}
	printf("\n");

	int day_cnt = 1;
	int week_cnt = 0;
	int max_day = month_days(year, month);
	int blank_day = week - 1; //5
	int empolyee_source_1 = 0;
	int empolyee_source_2 = 0;

	while (day_cnt < max_day)
	{
		for (i = 0; i < row; i++)
		{
			for (j = 0; j < col; j++)
			{
				if (blank_day > 0)							//前面空格
				{
					cale[i][j].day = 32;
					strcpy(cale[i][j].employee_1, "###");
					strcpy(cale[i][j].employee_2, "###");
					blank_day--;
				}
				else if (day_cnt <= max_day)				//中間班表
				{
					empolyee_source_1 = day_cnt / 4;
					empolyee_source_2 = day_cnt / 4;

					cale[i][j].day = day_cnt;
					strcpy(cale[i][j].employee_1, employee_all[empolyee_source_1]);
					strcpy(cale[i][j].employee_2, "BBBBB");
					day_cnt++;
				}
				else										//後面空格
				{
					cale[i][j].day = 32;
					strcpy(cale[i][j].employee_1, "##");
					strcpy(cale[i][j].employee_2, "##");
				}
			}
		}
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

void print_calendar(node cale[row][col])
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		//列印日期
		for (j = 0; j < col; j++)
		{
			if (cale[i][j].day != 32)
				printf("%15d", cale[i][j].day);
			else
				printf("%15s", " ");
		}
		printf("\n");
		//列印員工1
		for (j = 0; j < col; j++)
		{
			if (cale[i][j].day != 32)
				printf("%15s", cale[i][j].employee_1);
			else
				printf("%15s", " ");
		}
		printf("\n");
		//列印員工2
		for (j = 0; j < col; j++)
		{
			if (cale[i][j].day != 32)
				printf("%15s", cale[i][j].employee_2);
			else
				printf("%15s", " ");
		}
		printf("\n");
	}
}