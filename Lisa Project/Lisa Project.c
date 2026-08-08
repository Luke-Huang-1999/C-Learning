#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAL_ROWS 6			//6行
#define CAL_COLS 7			//一週7天
#define EMPLOYEE_NUMS 8		//員工人數
#define DM_NUMS 4			//值班主管人數
#define WORK_DAY_MAX 6		//最多連續做幾天
#define EMPTY_DAY 0			//月曆中空白日的賦值
#define SHIFT_NUMS 3		//班別(早班午班晚班)
#define NAME_LEN 10			//員工名字長度限制20bytes

typedef struct node
{
	int date;
	char employee[SHIFT_NUMS][NAME_LEN];
	int work_day[SHIFT_NUMS];
	//int work_day_2;
}node;

typedef struct data
{
	int month;
	int day;
	char week[5];
	char DS_DM[10];
	char DS_B[10];
	char DS_H[10];
	char ES_DM[10];
	char ES_B[10];
	char ES_H[10];
	char NS_DM[10];
	char NS_B[10];
	char NS_H[10];
	char DO_DM[10];
	char DO_B[10];
	char DO_H[10];
	char LEAVE_DS[10];
	char LEAVE_ES[10];
	char LEAVE_NS[10];
	struct data* next;
}list;

typedef struct employinfo
{
	char employee[10];
	int day;
}epinfo;

char employee_all[EMPLOYEE_NUMS][NAME_LEN] = { "Bruce","Carol" ,"Eason","Frank","Hank","Iris","Ken","Louis" };
char dm_all[DM_NUMS][NAME_LEN] = { "Alice" ,"David","Grog","Jackson" };
char shift[3][15] = { "Day","Evening" ,"Night" };
char parts[3][15] = { "DM","Brine","HCl" };
char all_week[7][5] = { "Mon","Tue","Wed" ,"Thu" ,"Fri" ,"Sat" ,"Sun" };

void receive_data(int* year, int* month, int* ds_dm_index, int* ds_dm_workday);
//(回傳當年當月的1號星期幾)蔡勒公式(年份, 月份)

int Zeller(int year, int month);
//()建立月曆(當年當月的1號星期幾)
void create_calendar_chart(int year, int month, node cale[CAL_ROWS][CAL_COLS]);

//()建立月曆(當年當月的1號星期幾)
list* create_calendar_list_console(int year, int month, node cale[CAL_ROWS][CAL_COLS], int ds_dm_index, int ds_dm_workday);

//()列印月曆(月曆的首指標)
void print_calendar_list_console(list* head);

//(回傳當月天數)計算當月天數(年份, 月份)
int month_days(int year, int month);

//()列印月曆(node型態的二維矩陣)
void print_calendar_chart_console(node cale[CAL_ROWS][CAL_COLS]);

list* create_list(int month, int day, char week[5], char DS_DM[10], char DS_B[10], char DS_H[10], char ES_DM[10], char ES_B[10], char ES_H[10], char NS_DM[10], char NS_B[10], char NS_H[10], char DO_DM[10], char DO_B[10], char DO_H[10], char LEAVE_DS[10], char LEAVE_ES[10], char LEAVE_NS[10]);

int main()
{
	//宣告變數
	int year, month;
	node cale[CAL_ROWS][CAL_COLS] = { 0 };
	year = 2026;
	month = 8;
	int ds_dm_index = 1;
	int ds_dm_workday = 4;
	//1.接收初始資訊
	//receive_data(&year, &month,&ds_dm_index,&ds_dm_workday);

	//生成月曆
	//create_calendar_chart(year, month, cale);
	list* head = create_calendar_list_console(year, month, cale, ds_dm_index, ds_dm_workday);
	//列印月曆
	//print_calendar_chart_console(cale);
	print_calendar_list_console(head);

	//system("pause");

	return 0;
}

void receive_data(int* year, int* month, int* ds_dm_index, int* ds_dm_workday)
{
	printf("請輸入年份與月份：(例如 ==> 2026 8)\n");
	scanf("%d %d", year, month);

	printf("\n");

	printf("[0]Alice [1]David [2]Grog [3]Jackson\n");
	printf("請輸入第一天早班主管編號：(例如==> 1)\n");
	scanf("%d", ds_dm_index);

	printf("\n");

	printf("請輸入第一天早班主管值班第N天：(例如==> 1)\n");
	scanf("%d", ds_dm_workday);

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

	week = (Zeller_week + 5) % 7;

	//printf("%4d/%2d/%2d week = %d\n", input_year, input_month, day, week);

	return week;
}

void create_calendar_chart(int year, int month, node cale[CAL_ROWS][CAL_COLS])
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

list* create_calendar_list_console(int year, int month, node cale[CAL_ROWS][CAL_COLS], int ds_dm_index, int ds_dm_workday)
{
	int i;
	//建立標題
	printf("%5s%5s%30s%30s%30s%30s%30s\n", "date", "week", shift[0], shift[1], shift[2], "Day-off", "Leave");
	for (i = 0; i < 160; i++)
		printf("-");
	printf("\n");
	printf("%10s", " ");
	for (i = 0; i < 4; i++)
	{
		printf("%10s%10s%10s", parts[0], parts[1], parts[2]);
	}
	printf("%10s%10s%10s\n", parts[0], parts[1], parts[2]);
	for (i = 0; i < 160; i++)
		printf("-");
	printf("\n");

	int week = Zeller(year, month); //第一天星期幾 6[5]
	int day_max = month_days(year, month);//總天數
	int day_cnt = 1;//天數紀錄
	//int ds_dm_workday = 1;//早班主管連續天數
	int es_dm_workday = (ds_dm_workday + 1) % 6 + 1;//午班主管連續天數3
	int ns_dm_workday = (ds_dm_workday + 3) % 6 + 1;//晚班主管連續天數5
	int do_dm_workday = (ds_dm_workday % 2 != 0) ? 5 : 6;//輪休主管連續天數5
	//int ds_dm_index = 0;//早班主管係數
	int es_dm_index = (ds_dm_index + ((ds_dm_workday <= 4) ? 1 : 2)) % 4;//午班主管係數1
	int ns_dm_index = (ds_dm_index + ((ds_dm_workday <= 2) ? 2 : 3)) % 4;//晚班主管係數2
	int do_dm_index = (ds_dm_index + ((ds_dm_workday <= 2) ? 2 : (ds_dm_workday <= 4) ? 2 : 1)) % 4;//輪休主管係數3

	int ds_employee_workday = ds_dm_workday;//早班員工連續天數
	int es_employee_workday = (ds_dm_workday + 1) % 6 + 1;//午班員工連續天數
	int ns_employee_workday = (ds_dm_workday + 3) % 6 + 1;//晚班員工連續天數
	int do_employee_workday = (ds_dm_workday % 2 != 0) ? 5 : 6;//輪休員工連續天數
	int ds_employee_index = ds_dm_index * 2;//早班員工係數0
	int es_employee_index = es_dm_index * 2;//午班員工係數2
	int ns_employee_index = ns_dm_index * 2;//晚班員工係數4
	int do_employee_index = do_dm_index * 2;//輪休員工係數6

	list* head = NULL;//開頭指標指向1號
	list* current = NULL;
	list* newnode = NULL;

	while (day_cnt <= day_max)
	{
		newnode = create_list(month,
			day_cnt,
			all_week[(week++) % CAL_COLS],
			dm_all[(ds_dm_index) % DM_NUMS],						//早班
			employee_all[(ds_employee_index) % EMPLOYEE_NUMS],
			employee_all[(ds_employee_index + 1) % EMPLOYEE_NUMS],
			dm_all[(es_dm_index) % DM_NUMS],						//午班
			employee_all[(es_employee_index) % EMPLOYEE_NUMS],
			employee_all[(es_employee_index + 1) % EMPLOYEE_NUMS],
			dm_all[(ns_dm_index) % DM_NUMS],						//晚班
			employee_all[(ns_employee_index) % EMPLOYEE_NUMS],
			employee_all[(ns_employee_index + 1) % EMPLOYEE_NUMS],
			dm_all[(do_dm_index) % DM_NUMS],						//輪休
			employee_all[(do_employee_index) % EMPLOYEE_NUMS],
			employee_all[(do_employee_index + 1) % EMPLOYEE_NUMS],
			" ",
			" ",
			" "
		);
		ds_dm_workday++;
		es_dm_workday++;
		ns_dm_workday++;
		do_dm_workday++;
		ds_employee_workday++;
		es_employee_workday++;
		ns_employee_workday++;
		do_employee_workday++;


		if (do_dm_workday > WORK_DAY_MAX)
		{
			do_dm_workday = 5;
			do_dm_index--;
		}

		if (ds_dm_workday > WORK_DAY_MAX)
		{
			ds_dm_workday = 1;
			do_dm_index = ds_dm_index;
			ds_dm_index++;
		}

		if (es_dm_workday > WORK_DAY_MAX)
		{
			es_dm_workday = 1;
			do_dm_index = es_dm_index;
			es_dm_index++;
		}

		if (ns_dm_workday > WORK_DAY_MAX)
		{
			ns_dm_workday = 1;
			do_dm_index = ns_dm_index;
			ns_dm_index++;
		}
		//+++++++++++++++++++++++++++++++++++++++++++++
		if (do_employee_workday > WORK_DAY_MAX)
		{
			do_employee_workday = 5;
			do_employee_index -= 2;
		}
		if (ds_employee_workday > WORK_DAY_MAX)
		{
			ds_employee_workday = 1;
			do_employee_index = ds_employee_index;
			ds_employee_index += 2;
		}

		if (es_employee_workday > WORK_DAY_MAX)
		{
			es_employee_workday = 1;
			do_employee_index = es_employee_index;
			es_employee_index += 2;
		}

		if (ns_employee_workday > WORK_DAY_MAX)
		{
			ns_employee_workday = 1;
			do_employee_index = ns_employee_index;
			ns_employee_index += 2;
		}

		if (head == NULL)
			head = newnode;
		else
			current->next = newnode;

		current = newnode;
		day_cnt++;
	}
	return head;
}

void print_calendar_list_console(list* head)
{
	if (head == NULL)
	{
		printf("calendar list is not exit.\n");
		exit(1);
	}
	list* current = head;
	while (current != NULL)
	{
		printf("%2d/%2d%5s", current->month, current->day, current->week);
		printf("%10s%10s%10s", current->DS_DM, current->DS_B, current->DS_H);
		printf("%10s%10s%10s", current->ES_DM, current->ES_B, current->ES_H);
		printf("%10s%10s%10s", current->NS_DM, current->NS_B, current->NS_H);
		printf("%10s%10s%10s", current->DO_DM, current->DO_B, current->DO_H);
		printf("%10s%10s%10s", current->LEAVE_DS, current->LEAVE_ES, current->LEAVE_NS);
		printf("\n");
		current = current->next;
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

void print_calendar_chart_console(node cale[CAL_ROWS][CAL_COLS])
{
	//星期標題建立
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

list* create_list(int month, int day, char week[5], char DS_DM[10], char DS_B[10], char DS_H[10], char ES_DM[10], char ES_B[10], char ES_H[10], char NS_DM[10], char NS_B[10], char NS_H[10], char DO_DM[10], char DO_B[10], char DO_H[10], char LEAVE_DS[10], char LEAVE_ES[10], char LEAVE_NS[10])
{
	list* newnode = (list*)malloc(sizeof(list));
	if (newnode == NULL)
	{
		printf("Failed to created list.\n");
		exit(1);
	}

	//初始化
	newnode->month = month;
	newnode->day = day;
	strcpy(newnode->week, week);
	strcpy(newnode->DS_DM, DS_DM);
	strcpy(newnode->DS_B, DS_B);
	strcpy(newnode->DS_H, DS_H);
	strcpy(newnode->ES_DM, ES_DM);
	strcpy(newnode->ES_B, ES_B);
	strcpy(newnode->ES_H, ES_H);
	strcpy(newnode->NS_DM, NS_DM);
	strcpy(newnode->NS_B, NS_B);
	strcpy(newnode->NS_H, NS_H);
	strcpy(newnode->DO_DM, DO_DM);
	strcpy(newnode->DO_B, DO_B);
	strcpy(newnode->DO_H, DO_H);
	strcpy(newnode->LEAVE_DS, LEAVE_DS);
	strcpy(newnode->LEAVE_ES, LEAVE_ES);
	strcpy(newnode->LEAVE_NS, LEAVE_NS);
	newnode->next = NULL;
	return newnode;
}