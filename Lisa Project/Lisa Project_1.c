#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
工作天數 加班天數 休息天數 請假天數
*/

#define CAL_ROWS 6						//6行
#define CAL_COLS 7						//一週7天
#define EMPLOYEE_NUMS 8					//員工人數
#define DM_NUMS 4						//值班主管人數
#define WORK_DAY_MAX 6					//最多連續做幾天
#define EMPTY_DAY 0						//月曆中空白日的賦值
#define SHIFT_NUMS 3					//班別(早班午班晚班)
#define NAME_LEN 15						//員工名字長度限制
#define working_hours_per_day 8.0		//一日工時

#define LIST_DATE_LEN 5
#define LIST_NAME_LEN 10

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
	char DS_DM[NAME_LEN];
	float DS_DM_WORKING_HOURS;
	char DS_B[NAME_LEN];
	float DS_B_WORKING_HOURS;
	char DS_H[NAME_LEN];
	float DS_H_WORKING_HOURS;
	char ES_DM[NAME_LEN];
	float ES_DM_WORKING_HOURS;
	char ES_B[NAME_LEN];
	float ES_B_WORKING_HOURS;
	char ES_H[NAME_LEN];
	float ES_H_WORKING_HOURS;
	char NS_DM[NAME_LEN];
	float NS_DM_WORKING_HOURS;
	char NS_B[NAME_LEN];
	float NS_B_WORKING_HOURS;
	char NS_H[NAME_LEN];
	float NS_H_WORKING_HOURS;
	char DO_DM[NAME_LEN];
	float DO_DM_WORKING_HOURS;
	char DO_B[NAME_LEN];
	float DO_B_WORKING_HOURS;
	char DO_H[NAME_LEN];
	float DO_H_WORKING_HOURS;
	char LEAVE_DM[NAME_LEN];
	float LEAVE_DM_WORKING_HOURS;
	char LEAVE_B[NAME_LEN];
	float LEAVE_B_WORKING_HOURS;
	char LEAVE_H[NAME_LEN];
	float LEAVE_H_WORKING_HOURS;
	char NAME_LIST[15][NAME_LEN];
	struct data* next;
}list;

//char employee_all[EMPLOYEE_NUMS][NAME_LEN] = { "Bruce","Carol" ,"Eason","Frank","Hank","Iris","Ken","Louis" };
//char dm_all[DM_NUMS][NAME_LEN] = { "Alice" ,"David","Grog","Jackson" };
char employee_all[EMPLOYEE_NUMS][NAME_LEN] = { "小新","廣志" ,"小葵","小白","風間","阿呆","妮妮","正男" };
char dm_all[DM_NUMS][NAME_LEN] = { "維尼" ,"小豬","屹耳","羅賓" };
char shift[3][15] = { "Day","Evening" ,"Night" };
char parts[3][15] = { "DM","Brine","HCl" };
char all_week[7][5] = { "Mon","Tue","Wed" ,"Thu" ,"Fri" ,"Sat" ,"Sun" };
float dm_working_hours[DM_NUMS] = { 0.0 };
float employee_working_hours[EMPLOYEE_NUMS] = { 0.0 };

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

//()生成月曆清單節點(相關資料)
list* create_list(int month, int day, char week[5], char DS_DM[10], char DS_B[10], char DS_H[10], char ES_DM[10], char ES_B[10], char ES_H[10], char NS_DM[10], char NS_B[10], char NS_H[10], char DO_DM[10], char DO_B[10], char DO_H[10], char LEAVE_DS[10], char LEAVE_ES[10], char LEAVE_NS[10]);

//每日工時計算(list型態的首區塊指標)
void working_hours_daily(list* head);

//()操作系統(list型態的首區塊指標, 年, 月)
void operation_system(list* head, int year, int month);

//()該月工時總計(list型態的首區塊指標)
void total_working_hours_print(list* head);

//請假系統()
void leave_system(list* head);

//(索引值)名字搜尋索引值(一維陣列, 一維陣列)
int search(char name[NAME_LEN]);

void time_calculate(list* head);

void test_hours(list* head);

int main()
{
	//宣告變數
	int year, month;
	node cale[CAL_ROWS][CAL_COLS] = { 0 };
	year = 2026;
	month = 8;
	int ds_dm_index = 2;
	int ds_dm_workday = 4;
	int personal_leave = 0;
	//1.接收初始資訊
	//receive_data(&year, &month, &ds_dm_index, &ds_dm_workday);

	//生成月曆
	list* head = create_calendar_list_console(year, month, cale, ds_dm_index, ds_dm_workday);

	//列印月曆
	print_calendar_list_console(head);
	printf("\n");

	//操作系統
	operation_system(head, year, month);


	//釋放記憶體
	free(head);
	head = NULL;

	//total_working_hours_print(head);

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
	int do_dm_index = (ds_dm_index + ((ds_dm_workday <= 2) ? 3 : (ds_dm_workday <= 4) ? 2 : 1)) % 4;//輪休主管係數3

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


	working_hours_daily(head);


	return head;
}

void print_calendar_list_console(list* head)
{
	if (head == NULL)
	{
		printf("calendar list is not exit.\n");
		exit(1);
	}

	//建立標題
	int i;
	printf("%*s%*s%*s%*s%*s%*s%*s\n"
		, LIST_DATE_LEN, "Date"
		, LIST_DATE_LEN, "Week"
		, LIST_NAME_LEN * 3, shift[0]
		, LIST_NAME_LEN * 3, shift[1]
		, LIST_NAME_LEN * 3, shift[2]
		, LIST_NAME_LEN * 3, "Day-off"
		, LIST_NAME_LEN * 3, "Leave");
	for (i = 0; i < 160; i++)
		printf("=");
	printf("\n");
	printf("%10s", " ");
	for (i = 0; i < 5; i++)
	{
		printf("%*s%*s%*s"
			, LIST_NAME_LEN, parts[0]
			, LIST_NAME_LEN, parts[1]
			, LIST_NAME_LEN, parts[2]);
	}
	printf("\n");
	for (i = 0; i < 160; i++)
		printf("=");
	printf("\n");

	list* current = head;
	while (current != NULL)
	{
		printf("%*d/%*d%5s", LIST_DATE_LEN % 3, current->month, LIST_DATE_LEN % 3, current->day, current->week);
		printf("%*s%*s%*s", LIST_NAME_LEN, current->DS_DM, LIST_NAME_LEN, current->DS_B, LIST_NAME_LEN, current->DS_H);
		printf("%*s%*s%*s", LIST_NAME_LEN, current->ES_DM, LIST_NAME_LEN, current->ES_B, LIST_NAME_LEN, current->ES_H);
		printf("%*s%*s%*s", LIST_NAME_LEN, current->NS_DM, LIST_NAME_LEN, current->NS_B, LIST_NAME_LEN, current->NS_H);
		printf("%*s%*s%*s", LIST_NAME_LEN, current->DO_DM, LIST_NAME_LEN, current->DO_B, LIST_NAME_LEN, current->DO_H);
		printf("%*s%*s%*s", LIST_NAME_LEN, current->LEAVE_DM, LIST_NAME_LEN, current->LEAVE_B, LIST_NAME_LEN, current->LEAVE_H);
		printf("\n");
		//for (i = 0; i < 166; i++)
		//	printf("-");
		//printf("\n");
		current = current->next;
	}
	printf("\n");
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

list* create_list(int month, int day, char week[5], char DS_DM[10], char DS_B[10], char DS_H[10], char ES_DM[10], char ES_B[10], char ES_H[10], char NS_DM[10], char NS_B[10], char NS_H[10], char DO_DM[10], char DO_B[10], char DO_H[10], char LEAVE_DM[10], char LEAVE_B[10], char LEAVE_H[10])
{
	int i = 0;
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
	strcpy(newnode->NAME_LIST[i++], DS_DM);
	strcpy(newnode->DS_B, DS_B);
	strcpy(newnode->NAME_LIST[i++], DS_B);
	strcpy(newnode->DS_H, DS_H);
	strcpy(newnode->NAME_LIST[i++], DS_H);
	strcpy(newnode->ES_DM, ES_DM);
	strcpy(newnode->NAME_LIST[i++], ES_DM);
	strcpy(newnode->ES_B, ES_B);
	strcpy(newnode->NAME_LIST[i++], ES_B);
	strcpy(newnode->ES_H, ES_H);
	strcpy(newnode->NAME_LIST[i++], ES_H);
	strcpy(newnode->NS_DM, NS_DM);
	strcpy(newnode->NAME_LIST[i++], NS_DM);
	strcpy(newnode->NS_B, NS_B);
	strcpy(newnode->NAME_LIST[i++], NS_B);
	strcpy(newnode->NS_H, NS_H);
	strcpy(newnode->NAME_LIST[i++], NS_H);
	strcpy(newnode->DO_DM, DO_DM);
	strcpy(newnode->NAME_LIST[i++], DO_DM);
	strcpy(newnode->DO_B, DO_B);
	strcpy(newnode->NAME_LIST[i++], DO_B);
	strcpy(newnode->DO_H, DO_H);
	strcpy(newnode->NAME_LIST[i++], DO_H);
	strcpy(newnode->LEAVE_DM, LEAVE_DM);
	strcpy(newnode->NAME_LIST[i++], LEAVE_DM);
	strcpy(newnode->LEAVE_B, LEAVE_B);
	strcpy(newnode->NAME_LIST[i++], LEAVE_B);
	strcpy(newnode->LEAVE_H, LEAVE_H);
	strcpy(newnode->NAME_LIST[i++], LEAVE_H);
	newnode->next = NULL;

	return newnode;
}

void working_hours_daily(list* head)
{
	int i;
	list* current = head;
	while (current != NULL)
	{
		current->LEAVE_DM_WORKING_HOURS = 0.0;
		current->LEAVE_B_WORKING_HOURS = 0.0;
		current->LEAVE_H_WORKING_HOURS = 0.0;
		for (i = 0; i < DM_NUMS; i++)
		{
			if (strcmp(current->DS_DM, dm_all[i]) == 0)
				current->DS_DM_WORKING_HOURS = working_hours_per_day;

			else if (strcmp(current->ES_DM, dm_all[i]) == 0)
				current->ES_DM_WORKING_HOURS = working_hours_per_day;

			else if (strcmp(current->NS_DM, dm_all[i]) == 0)
				current->NS_DM_WORKING_HOURS = working_hours_per_day;

			else if (strcmp(current->DO_DM, dm_all[i]) == 0)
				current->DO_DM_WORKING_HOURS = 0.0;

			//else if (strcmp(current->LEAVE_DM, dm_all[i]) == 0)
			//{//錯誤需修復，原先的已經被蓋掉了
			//	if (strcmp(current->LEAVE_DM, current->DS_DM) == 0)					//早班主管請假
			//	{
			//		current->ES_DM_WORKING_HOURS += working_hours_per_day / 2.0;
			//		current->NS_DM_WORKING_HOURS += working_hours_per_day / 2.0;
			//	}
			//	else if (strcmp(current->LEAVE_DM, current->ES_DM) == 0)			//午班主管請假
			//	{
			//		current->DS_DM_WORKING_HOURS += working_hours_per_day / 2.0;
			//		current->NS_DM_WORKING_HOURS += working_hours_per_day / 2.0;
			//	}
			//	else if (strcmp(current->LEAVE_DM, current->NS_DM) == 0)			//晚班主管請假
			//	{
			//		current->DS_DM_WORKING_HOURS += working_hours_per_day / 2.0;
			//		current->ES_DM_WORKING_HOURS += working_hours_per_day / 2.0;
			//	}
			//}
		}

		for (i = 0; i < EMPLOYEE_NUMS; i++)
		{
			if (strcmp(current->DS_B, employee_all[i]) == 0)
				current->DS_B_WORKING_HOURS = working_hours_per_day;
			else if (strcmp(current->DS_H, employee_all[i]) == 0)
				current->DS_H_WORKING_HOURS = working_hours_per_day;

			else if (strcmp(current->ES_B, employee_all[i]) == 0)
				current->ES_B_WORKING_HOURS = working_hours_per_day;
			else if (strcmp(current->ES_H, employee_all[i]) == 0)
				current->ES_H_WORKING_HOURS = working_hours_per_day;

			else if (strcmp(current->NS_B, employee_all[i]) == 0)
				current->NS_B_WORKING_HOURS = working_hours_per_day;
			else if (strcmp(current->NS_H, employee_all[i]) == 0)
				current->NS_H_WORKING_HOURS = working_hours_per_day;

			else if (strcmp(current->DO_B, employee_all[i]) == 0)
				current->DO_B_WORKING_HOURS = 0.0;
			else if (strcmp(current->DO_H, employee_all[i]) == 0)
				current->DO_H_WORKING_HOURS = 0.0;

			else if (strcmp(current->LEAVE_B, employee_all[i]) == 0)
				current->LEAVE_B_WORKING_HOURS = -working_hours_per_day;
			else if (strcmp(current->LEAVE_H, employee_all[i]) == 0)
				current->LEAVE_H_WORKING_HOURS = -working_hours_per_day;
		}

		current = current->next;
	}

}

void operation_system(list* head, int year, int month)
{
	int mode;
	while (1)
	{
		printf("操作系統選擇：[0]=>結束   [1]請假系統   [2]列印班表   [3]列印工時表\n");
		printf("==> ");
		scanf("%d", &mode);

		switch (mode)
		{
		case(0):
		{
			printf("結束\n");
			break;
		}
		case(1):
		{
			printf("請假系統\n");
			leave_system(head);
			continue;
		}
		case(2):
		{
			printf("列印班表\n");
			print_calendar_list_console(head);
			continue;
		}
		case(3):
		{
			printf("列印工時表\n");
			total_working_hours_print(head);
			continue;
		}
		default:
		{
			printf("輸入錯誤，請再輸入乙次。\n");
			continue;
		}
		}

		if (mode == 0)
			break;
	}

}

void total_working_hours_print(list* head)
{
	list* current = head;
	int i;
	while (current != NULL)
	{
		//DM工時
		for (i = 0; i < DM_NUMS; i++)
		{
			if (strcmp(current->DS_DM, dm_all[i]) == 0)
				dm_working_hours[i] += current->DS_DM_WORKING_HOURS;

			else if (strcmp(current->ES_DM, dm_all[i]) == 0)
				dm_working_hours[i] += current->ES_DM_WORKING_HOURS;

			else if (strcmp(current->NS_DM, dm_all[i]) == 0)
				dm_working_hours[i] += current->NS_DM_WORKING_HOURS;
		}

		//EMPLOYEE工時
		for (i = 0; i < EMPLOYEE_NUMS; i++)
		{
			if (strcmp(current->DS_B, employee_all[i]) == 0)
				employee_working_hours[i] += current->DS_B_WORKING_HOURS;

			else if (strcmp(current->DS_H, employee_all[i]) == 0)
				employee_working_hours[i] += current->DS_H_WORKING_HOURS;

			else if (strcmp(current->ES_B, employee_all[i]) == 0)
				employee_working_hours[i] += current->ES_B_WORKING_HOURS;

			else if (strcmp(current->ES_H, employee_all[i]) == 0)
				employee_working_hours[i] += current->ES_H_WORKING_HOURS;

			else if (strcmp(current->NS_B, employee_all[i]) == 0)
				employee_working_hours[i] += current->NS_B_WORKING_HOURS;

			else if (strcmp(current->NS_H, employee_all[i]) == 0)
				employee_working_hours[i] += current->NS_H_WORKING_HOURS;

			//else if (strcmp(current->LEAVE_DM, dm_all[i]) == 0)
			//{
			//	if (i % 2 == 0)													//BRINE
			//	{
			//		int leave_index = i;
			//		int do_index = search(current->DO_B);
			//		int j;
			//		for (j = 0; j < EMPLOYEE_NUMS; j += 2)
			//		{
			//			if (j != leave_index && j != do_index)
			//				dm_working_hours[j] += 4.0;
			//		}
			//	}

			//	if (i % 2 != 0)													//HCl
			//	{
			//		int leave_index = i;
			//		int do_index = search(current->DO_H);
			//		int j;
			//		for (j = 1; j < EMPLOYEE_NUMS; j += 2)
			//		{
			//			if (j != leave_index && j != do_index)
			//				dm_working_hours[j] += 4.0;
			//		}
			//	}
			//}
		}
		current = current->next;
	}

	time_calculate(head);

	//列印
	for (i = 0; i < DM_NUMS; i++)
	{
		printf("DM ==>%7s  %.1f hours = %.1f days\n"
			, dm_all[i]
			, dm_working_hours[i]
			, dm_working_hours[i] / working_hours_per_day);
		printf("B  ==>%7s  %.1f hours = %.1f days\n"
			, employee_all[2 * i]
			, employee_working_hours[2 * i]
			, employee_working_hours[2 * i] / working_hours_per_day);
		printf("H  ==>%7s  %.1f hours = %.1f days\n"
			, employee_all[2 * i + 1]
			, employee_working_hours[2 * i + 1]
			, employee_working_hours[2 * +1] / working_hours_per_day);

		printf("\n");
	}

	//test_hours(head);

	//工時歸零
	for (i = 0; i < DM_NUMS; i++)
	{
		dm_working_hours[i] = 0.0;
		employee_working_hours[2 * i] = 0.0;
		employee_working_hours[2 * i + 1] = 0.0;
	}

}

void leave_system(list* head)
{
	int leave_day = 1;
	list* current = head;
	int mode_index;
	int leave_index;
	while (leave_day != 0)
	{
		printf("請輸入請假日期(5號，則輸入 5；結束請假系統請輸入 0 )：\n");
		printf("==> ");
		scanf("%d", &leave_day);
		if (leave_day == 0)
		{
			printf("結束請假系統。\n");
			break;
		}
		while (current->day != leave_day)
			current = current->next;


		//建立標題
		int i;
		printf("%5s%5s%30s%30s%30s%30s%30s\n", "date", "week", shift[0], shift[1], shift[2], "Day-off", "Leave");
		for (i = 0; i < 160; i++)
			printf("=");

		printf("\n");
		printf("%10s", " ");
		for (i = 0; i < 5; i++)
			printf("%10s%10s%10s", parts[0], parts[1], parts[2]);

		printf("\n");
		for (i = 0; i < 160; i++)
			printf("=");
		printf("\n");

		printf("%2d/%2d%5s", current->month, current->day, current->week);
		printf("%10s%10s%10s", current->DS_DM, current->DS_B, current->DS_H);
		printf("%10s%10s%10s", current->ES_DM, current->ES_B, current->ES_H);
		printf("%10s%10s%10s", current->NS_DM, current->NS_B, current->NS_H);
		printf("%10s%10s%10s", current->DO_DM, current->DO_B, current->DO_H);
		printf("%10s%10s%10s", current->LEAVE_DM, current->LEAVE_B, current->LEAVE_H);
		printf("\n");

		printf("[0]DM or [1]Employee ==>");
		scanf("%d", &mode_index);

		printf("請輸入請假人員姓名：");
		if (mode_index == 0)											//DM請假
		{
			for (i = 0; i < DM_NUMS; i++)
				printf("[%d]%s ", i, dm_all[i]);
			printf("\n");

			scanf("%d", &leave_index);

			strcpy(current->LEAVE_DM, dm_all[leave_index]);				//新增資料至LEAVE欄位

			//更改原資料
			if (strcmp(current->DS_DM, current->LEAVE_DM) == 0)			//早班主管更換
			{
				strcpy(current->DS_DM, current->ES_DM);
				//午班主管更換
				strcat(current->ES_DM, "/");
				strcat(current->ES_DM, current->NS_DM);
			}
			if (strcmp(current->ES_DM, current->LEAVE_DM) == 0)			//午班主管更換
			{
				strcpy(current->ES_DM, current->DS_DM);
				//午班主管更換
				strcat(current->ES_DM, "/");
				strcat(current->ES_DM, current->NS_DM);
			}
			if (strcmp(current->NS_DM, current->LEAVE_DM) == 0)			//晚班主管更換
			{
				strcpy(current->NS_DM, current->ES_DM);
				//午班主管更換
				strcpy(current->ES_DM, current->DS_DM);
				strcat(current->ES_DM, "/");
				strcat(current->ES_DM, current->NS_DM);
			}
		}
		else if (mode_index == 1)
		{
			for (i = 0; i < EMPLOYEE_NUMS; i++)
				printf("[%d]%s ", i, employee_all[i]);
			printf("\n");

			scanf("%d", &leave_index);
			if ((leave_index % 2) == 0)									//B位置的工作人員
			{
				strcpy(current->LEAVE_B, employee_all[leave_index]);	//新增資料至LEAVE欄位
				if (strcmp(current->DS_B, current->LEAVE_B) == 0)		//早班B位置員工更換
				{
					strcpy(current->DS_B, current->ES_B);

					strcat(current->ES_B, "/");
					strcat(current->ES_B, current->NS_B);
				}
				if (strcmp(current->ES_B, current->LEAVE_B) == 0)		//午班B位置員工更換
				{
					strcpy(current->ES_B, current->DS_B);

					strcat(current->ES_B, "/");
					strcat(current->ES_B, current->NS_B);
				}
				if (strcmp(current->NS_B, current->LEAVE_B) == 0)		//午班B位置員工更換
				{
					strcpy(current->NS_B, current->ES_B);

					strcpy(current->ES_B, current->DS_B);
					strcat(current->ES_B, "/");
					strcat(current->ES_B, current->NS_B);
				}

			}
			else														//H位置的工作人員
			{
				strcpy(current->LEAVE_H, employee_all[leave_index]);	//新增資料至LEAVE欄位
				if (strcmp(current->DS_H, current->LEAVE_H) == 0)		//早班H位置員工更換
				{
					strcpy(current->DS_H, current->ES_H);

					strcat(current->ES_H, "/");
					strcat(current->ES_H, current->NS_H);
				}
				if (strcmp(current->ES_H, current->LEAVE_H) == 0)		//午班H位置員工更換
				{
					strcpy(current->ES_H, current->DS_H);

					strcat(current->ES_H, "/");
					strcat(current->ES_H, current->NS_H);
				}
				if (strcmp(current->NS_H, current->LEAVE_H) == 0)		//午班H位置員工更換
				{
					strcpy(current->NS_H, current->ES_H);

					strcpy(current->ES_H, current->DS_H);
					strcat(current->ES_H, "/");
					strcat(current->ES_H, current->NS_H);
				}
			}
		}
		else
		{
			printf("輸入錯誤。\n");
			continue;
		}
	}
}

int search(char name[NAME_LEN])
{
	int i;
	int index = 99;
	for (i = 0; i < DM_NUMS; i++)
	{
		if (strcmp(dm_all[i], name) == 0)
			index = i;
	}
	for (i = 0; i < EMPLOYEE_NUMS; i++)
	{
		if (strcmp(employee_all[i], name) == 0)
			index = i;
	}
	if (index == 99)
	{
		printf("search is failed.\n");
		return 0;
	}
	return index;
}

void time_calculate(list* head)
{
	list* current = head;
	int i;
	while (current != NULL)
	{
		//尋找兩人共同分擔的班別-主管
		if (strstr(current->DS_DM, "/"))
		{
			for (i = 0; i < DM_NUMS; i++)
			{
				if (strstr(current->DS_DM, dm_all[i]))
					dm_working_hours[i] += working_hours_per_day / 2.0;
			}
		}
		else if (strstr(current->ES_DM, "/"))
		{
			for (i = 0; i < DM_NUMS; i++)
			{
				if (strstr(current->ES_DM, dm_all[i]))
					dm_working_hours[i] += working_hours_per_day / 2.0;
			}
		}
		else if (strstr(current->NS_DM, "/"))
		{
			for (i = 0; i < DM_NUMS; i++)
			{
				if (strstr(current->NS_DM, dm_all[i]))
					dm_working_hours[i] += working_hours_per_day / 2.0;
			}
		}
		//尋找兩人共同分擔的班別-Brine
		if (strstr(current->DS_B, "/"))
		{
			for (i = 0; i < EMPLOYEE_NUMS; i++)
			{
				if (strstr(current->DS_B, employee_all[i]))
					employee_working_hours[i] += working_hours_per_day / 2.0;
			}
		}
		else if (strstr(current->ES_B, "/"))
		{
			for (i = 0; i < EMPLOYEE_NUMS; i++)
			{
				if (strstr(current->ES_B, employee_all[i]))
					employee_working_hours[i] += working_hours_per_day / 2.0;
			}
		}
		else if (strstr(current->NS_B, "/"))
		{
			for (i = 0; i < EMPLOYEE_NUMS; i++)
			{
				if (strstr(current->NS_B, employee_all[i]))
					employee_working_hours[i] += working_hours_per_day / 2.0;
			}
		}

		//尋找兩人共同分擔的班別-HCl
		if (strstr(current->DS_H, "/"))
		{
			for (i = 0; i < EMPLOYEE_NUMS; i++)
			{
				if (strstr(current->DS_H, employee_all[i]))
					employee_working_hours[i] += working_hours_per_day / 2.0;
			}
		}
		else if (strstr(current->ES_H, "/"))
		{
			for (i = 0; i < EMPLOYEE_NUMS; i++)
			{
				if (strstr(current->ES_H, employee_all[i]))
					employee_working_hours[i] += working_hours_per_day / 2.0;
			}
		}
		else if (strstr(current->NS_H, "/"))
		{
			for (i = 0; i < EMPLOYEE_NUMS; i++)
			{
				if (strstr(current->NS_H, employee_all[i]))
					employee_working_hours[i] += working_hours_per_day / 2.0;
			}
		}

		//指標移動
		current = current->next;
	}
}

void test_hours(list* head)
{
	printf("\n\n");
	list* current = head;
	while (current != NULL)
	{
		printf("%.1f %.1f %.1f |%.1f %.1f %.1f |%.1f %.1f %.1f |%.1f %.1f %.1f |%.1f %.1f %.1f\n"
			, current->DS_DM_WORKING_HOURS
			, current->DS_B_WORKING_HOURS
			, current->DS_H_WORKING_HOURS
			, current->ES_DM_WORKING_HOURS
			, current->ES_B_WORKING_HOURS
			, current->ES_H_WORKING_HOURS
			, current->NS_DM_WORKING_HOURS
			, current->NS_B_WORKING_HOURS
			, current->NS_H_WORKING_HOURS
			, current->DO_DM_WORKING_HOURS
			, current->DO_B_WORKING_HOURS
			, current->DO_H_WORKING_HOURS
			, current->LEAVE_DM_WORKING_HOURS
			, current->LEAVE_B_WORKING_HOURS
			, current->LEAVE_H_WORKING_HOURS
		);
		current = current->next;
	}
}