#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int main()
{
	char employee_all[4][15] = { "AAAAA","BBBBB","CCCCC" ,"DDDDD" };
	int day = 1;
	int day_max = 10;
	int employee_source_1 = 0;
	int employee_source_2 = 0;
	while (day <= day_max)
	{
		printf("第%d天\n", day);


		employee_source_1 = (day / 4) / 4;
		employee_source_2 = (2 + day / 4) / 4;

		printf("%s ", employee_all[employee_source_1]);
		printf("%s ", employee_all[employee_source_2]);
		day++;
		printf("\n");
	}

	return 0;
}