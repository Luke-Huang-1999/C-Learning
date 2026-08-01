#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define CAL_ROWS 6			//6行
#define CAL_COLS 7			//一週7天
#define EMPLOYEE_NUMS 6		//員工人數
#define WORK_DAY_MAX 3		//最多連續做幾天
#define EMPTY_DAY 0			//月曆中空白日的賦值
#define SHIFT_NUMS 3		//班別(早班午班晚班)
#define NAME_LEN 20			//員工名字長度限制20bytes

typedef struct node
{
	int date;
	char employee[SHIFT_NUMS][NAME_LEN];
	int work_day[SHIFT_NUMS];
	//int work_day_2;
}node;

typedef struct employinfo
{
	char employee[10];
	int day;
}epinfo;

char employee_all[EMPLOYEE_NUMS][NAME_LEN] = {"Alice","Bruce","Carol" ,"David","Eason","Frank"};

void receive_data(int* year, int* month);
//(回傳當年當月的1號星期幾)蔡勒公式(年份, 月份)

int Zeller(int year, int month);
//()建立月曆(當年當月的1號星期幾)
void create_calendar(int year, int month, node cale[CAL_ROWS][CAL_COLS]);

//(回傳當月天數)計算當月天數(年份, 月份)
int month_days(int year, int month);

//()列印月曆(node型態的二維矩陣)
void print_calendar_console(node cale[CAL_ROWS][CAL_COLS]);



int main()
{
	//宣告變數
	int year, month;
	node cale[CAL_ROWS][CAL_COLS] = { 0 };
	year = 2026;
	month = 8;

	//1.接收初始資訊
	//receive_data(&year, &month);	//年月

	//生成月曆
	create_calendar(year, month, cale);

	//列印月曆
	print_calendar_console(cale);


	//system("pause");

	return 0;
}

void receive_data(int* year, int* month)
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

void create_calendar(int year, int month, node cale[CAL_ROWS][CAL_COLS])
{
	int week = Zeller(year, month); //6
	int i, j;

	int day_cnt = 1;
	int week_cnt = 0;
	int day_max = month_days(year, month);
	int blank_day = week - 1; //5
	int no_1 = 0;
	int no_2 = 1;
	int wd_1 = 0;
	int wd_2 = 1;

	for (i = 0; i < CAL_ROWS; i++)
	{
		for (j = 0; j < CAL_COLS; j++)
		{
			if (blank_day > 0)							//前面空格
			{
				cale[i][j].date = EMPTY_DAY;
				strcpy(cale[i][j].employee[0], "###");
				strcpy(cale[i][j].employee[1], "###");
				cale[i][j].work_day[0] = 0;
				cale[i][j].work_day[1] = 0;
				blank_day--;
			}
			else if (day_cnt <= day_max)				//中間班表
			{
				if (wd_1 < WORK_DAY_MAX)
				{
					wd_1++;
					cale[i][j].work_day[0] = wd_1;
				}
				else
				{
					wd_1 = 1;
					no_1 = (no_1 + 2) % 4;
					cale[i][j].work_day[0] = wd_1;
				}

				if (wd_2 < WORK_DAY_MAX)
				{
					wd_2++;
					cale[i][j].work_day[1] = wd_2;
				}
				else
				{
					wd_2 = 1;
					no_2 = (no_2 + 2) % 4;
					cale[i][j].work_day[1] = wd_2;
				}

				cale[i][j].date = day_cnt;
				strcpy(cale[i][j].employee[0], employee_all[no_1]);
				strcpy(cale[i][j].employee[1], employee_all[no_2]);

				day_cnt++;
			}
			else										//後面空格
			{
				cale[i][j].date = EMPTY_DAY;
				strcpy(cale[i][j].employee[0], "##");
				strcpy(cale[i][j].employee[1], "##");
				cale[i][j].work_day[0] = 0;
				cale[i][j].work_day[1] = 0;
			}
		}
	}

}

int month_days(int year, int month)
{
	int days = 0;

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

	default:
		return 0;
	}

	return days;
}

void print_calendar_console(node cale[CAL_ROWS][CAL_COLS])
{
	//星期標題建立
	char all_week[7][4] = { "Mon","Tue","Wed" ,"Thu" ,"Fri" ,"Sat" ,"Sun" };
	int i, j;
	for (i = 0; i < 7; i++)
	{
		printf("%15s", all_week[i]);
	}
	printf("\n");
	for (i = 0; i < (15 * 7); i++)
		printf("=");
	printf("\n");

	for (i = 0; i < CAL_ROWS; i++)
	{
		//列印日期
		for (j = 0; j < CAL_COLS; j++)
		{
			if (cale[i][j].date != EMPTY_DAY)
				printf("%15d", cale[i][j].date);
			else
				printf("%15s", " ");
		}
		printf("\n");
		//列印員工1
		for (j = 0; j < CAL_COLS; j++)
		{
			if (cale[i][j].date != EMPTY_DAY)
				printf("%15s", cale[i][j].employee[0]);
			else
				printf("%15s", " ");
		}
		printf("\n");
		//列印員工2
		for (j = 0; j < CAL_COLS; j++)
		{
			if (cale[i][j].date != EMPTY_DAY)
				printf("%15s", cale[i][j].employee[1]);
			else
				printf("%15s", " ");
		}
		printf("\n\n");
		
	}
}

