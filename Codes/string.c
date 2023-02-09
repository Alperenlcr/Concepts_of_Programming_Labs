#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void f(char* x1, char* x2, char* x3, char* x4)
{
    printf("s1 : %s     s2 : %s     s3 : %s     s4 : %s\n\n", x1, x2, x3, x4);
}

void main()
{
    printf("\n");
//strcpy, strncpy, strcat, strncat, strcmp, strncmp
    char *s1 = (char*)calloc(100,sizeof(char));
    char *s2 = (char*)malloc(100*sizeof(char));
    char *s3 = (char*)malloc(100*sizeof(char));
    char *s4 = (char*)malloc(100*sizeof(char));

    strcpy(s1, "asdfghjkl\0");
    strcpy(s2, "asdrtyuio\0");
    strcpy(s3, "asdvbnm,.\0");
    strcpy(s4, "de\0");
    f(s1, s2, s3, s4);

    printf("strcpy(s1, s2);\n");
    strcpy(s1, s2);

    f(s1, s2, s3, s4);

    printf("strncpy(s1, s3, 3);\n");
    strncpy(s1, s3, 3);

    f(s1, s2, s3, s4);

    printf("strcat(s1, s3);\n");
    strcat(s1, s3);

    f(s1, s2, s3, s4);

    printf("strncat(s1, s2, 3);\n");
    strncat(s1, s2, 3);

    f(s1, s2, s3, s4);

    printf("strcmp(s1, s2);\n");
    printf("%d ",strcmp(s1, s2));

    f(s1, s2, s3, s4);

    printf("strncmp(s1, s2, 3);\n");
    printf("%d ",strncmp(s1, s2, 3));

    f(s1, s2, s3, s4);

}
