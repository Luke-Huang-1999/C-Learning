#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int search(char name[10]);

char dm_all[4][10] = { "Alice" ,"David","Grog","Jackson" };

int main()
{
	char name[10] = "Alice";
	int index = search(name);
	printf("%d", index);

	return 0;
}

int search(char name[10])
{
	int i;
	int index = 99;
	for (i = 0; i < 4; i++)
	{
		if (strcmp(dm_all[i], name) == 0)
			index = i;
	}

	if (index == 99)
	{
		printf("search is failed.\n");
		return 0;
	}
	return index;
}