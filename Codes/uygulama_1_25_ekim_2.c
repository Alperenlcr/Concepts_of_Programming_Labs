#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define MAX 500
int main()
{
    char main_text[MAX] = "asd ASD asd asd keysad keyasddsakekekekekekeke";
    char key[MAX] = "key";
    int i=0, j;

    while (main_text[i] != '\0')
    {
        j = 0;
        while (main_text[i+j] == key[j] && key[j+1] !='\0')
        {
            j++;
        }
        if (j != 0 && key[j+1] == '\0')
        {
            printf("Found at %d\n", i);
        }
        i++;
    }

    return 0;
}