#include <stdio.h>
#define MIN(a, b) ( (a) < (b) ? (a) : (b))

void main()
{
    printf("\n%d", MIN(3,2));
    printf("\nKaynak kodun o anda kac numarali satirindayiz (__LINE__) : %d", __LINE__);
    printf("\nKaynak kodun hangi dosya icinden cagirildigi (__FILE__) : %s", __FILE__);
    printf("\nDerlendigi zaman (__TIME__) : %s", __TIME__);
    printf("\nDerlendigi tarih (__DATE__) : %s", __DATE__);
    printf("\nANSI standartina uyuyor mu (__STDC__) : %d", __STDC__);
    printf("\n");
    access_function();
}
