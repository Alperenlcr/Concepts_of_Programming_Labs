#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20
enum nevermind {zero, one};


char*** fill_matrix(int n, char*** matrix)
{
    char numbers[2][10][MAX] = {{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"},
                                {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"}};

    int i;
    for ( i = zero; i < n; i++)
    {
        strcpy(matrix[zero][i], numbers[one][i]);
        strcpy(matrix[one][i], numbers[zero][i]);
    }
    
    return matrix;
}

char*** matrix_init(int n)
{
    int i, j, k;
    char ***matrix = (char***)malloc(2*sizeof(char**));
    if (matrix == NULL)
        printf("ERROR.");
    
    for ( k = 0; k < 2; k++)
    {
        matrix[k] = (char**)malloc(n*sizeof(char*));
        if (matrix[k] == NULL)
            printf("ERROR.");
    }

    for ( k = 0; k < 2; k++)
    {
        for ( i = 0; i < n; i++)
        {
            matrix[k][i] = (char*)malloc(MAX*sizeof(char));
            if (matrix[k] == NULL)
                printf("ERROR.");
        }
    }
    matrix = fill_matrix(n, matrix);
    return matrix;
}

void matrix_print(int n, char*** matrix)
{
    int i, k;
    for ( k = 0; k < 2; k++)
    {
        for ( i = 0; i < n; i++)
        {
           printf("%s ", matrix[k][i]); 
        }
        printf("\n");
        
    }
    
}