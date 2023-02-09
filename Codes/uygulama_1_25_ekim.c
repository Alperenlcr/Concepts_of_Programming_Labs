#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "menu.h"

#define SUM(num1, num2) (num1)+(num2)   //num1 + num2 yapsaydik ve SUM(5+1,6+1) gonderseydik 5+1*6+1 isleminden 12 olurdu cevap
#define DIFF(num1, num2) (num1)-(num2)
#define PRODUCT(num1, num2) (num1)*(num2)
#define DIV(num1, num2) (num1)/(num2)


int main()
{
    int choice, num1, num2;
    do
    {
        m;  //menu.h dan
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Toplama islemi icin birinci sayi : ");
            scanf("%d", &num1);
            printf("Toplama islemi icin ikinci sayi : ");
            scanf("%d", &num2);
            printf("%d + %d = %d\n", num1, num2, SUM(num1, num2));
            break;
        
        case 2:
            printf("Cikarma islemi icin birinci sayi : ");
            scanf("%d", &num1);
            printf("Cikarma islemi icin ikinci sayi : ");
            scanf("%d", &num2);
            printf("%d - %d = %d\n", num1, num2, DIFF(num1, num2));
            break;

        case 3:
            printf("Carpma islemi icin birinci sayi : ");
            scanf("%d", &num1);
            printf("Carpma islemi icin ikinci sayi : ");
            scanf("%d", &num2);
            printf("%d * %d = %d\n", num1, num2, PRODUCT(num1, num2));
            break;

        case 4:
            printf("Bolme islemi icin birinci sayi : ");
            scanf("%d", &num1);
            printf("Bolme islemi icin ikinci sayi : ");
            scanf("%d", &num2);
            printf("%d / %d = %d\n", num1, num2, DIV(num1, num2));
            break;
        
        case 5:
            printf("Faktoriyeli alinacak sayi : ");
            scanf("%d", &num1);
            num2 = num1;
            printf("%d! =",num2);
            while (num2>1)
                num1 *= --num2;

            printf(" %d\n", num1);
            break;
        default:
            break;
        }
    } while (choice != 0);
    



    return 0;
}