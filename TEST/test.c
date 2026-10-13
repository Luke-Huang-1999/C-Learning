#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

int main(void)
{
    int choice = 0;
    int key;

    while (1)
    {
        system("cls");

        printf("請選擇你的行動：\n\n");

        if (choice == 0)
            printf(" > [1] 出門\n");
        else
            printf("   [1] 出門\n");

        if (choice == 1)
            printf(" > [2] 不出門\n");
        else
            printf("   [2] 不出門\n");

        printf("\n使用方向鍵移動，按 Enter 確認\n");

        key = _getch();

        if (key == 224)
        {
            key = _getch();

            if (key == 72)
            {
                choice--;
                if (choice < 0)
                    choice = 1;
            }
            else if (key == 80)
            {
                choice++;
                if (choice > 1)
                    choice = 0;
            }
        }
        else if (key == 13)
        {
            break;
        }
    }

    //system("cls");

    if (choice == 0)
        printf("你選擇了：出門\n");
    else
        printf("你選擇了：不出門\n");

    return 0;
}
