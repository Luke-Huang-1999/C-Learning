#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
//#include <windows.h>

void test(char* NAME);
int main(void)
{
    char employee_list[4][3][10] = { {"群諭","尚鴻","朝鑫"},{"杰宏","訓嘉","總為"},{"紋性","宏龍","健忠"},{"鵬銘","孟昌","傑哥"} };

    //printf("%s\n", employee_list[0][1]);

    test("Hi welcome!\n\n");
    return 0;
}

void test(char* NAME)
{

    printf("%s", NAME);
}