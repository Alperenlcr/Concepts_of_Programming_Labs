/*
matrix = sayilar yazilislarina karsilik gelecek sekilde 3 boyutlu dynamic matris olustur
0 1 2 3 4 5 6 7 8 9
zero, one, two, three, four, five, six, seven, eight, nine
kullanican 10'dan kucuk olacak bir sayi al
functions and macros kullan
enum kullan
*/


#include "exmp.h"



int main()
{
    int n;
    char*** matrix;
    printf("\n1-10 arasi bir sayi : ");
    scanf("%d", &n);
    matrix = matrix_init(n);
    matrix_print(n, matrix);

    return 0;
}