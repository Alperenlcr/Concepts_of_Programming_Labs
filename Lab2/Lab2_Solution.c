#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    // NxN dynamic matrix create and fill
    int **matrix;
    int N, sum=0;
    int i, j;
    printf("N : ");
    scanf("%d", &N);

    matrix = (int**) malloc(N*sizeof(int*));
    if (matrix == NULL)
    {
        printf("\nBellek ayrilamadi.");
        return 0;
    }

    for ( i = 0; i < N; i++)
    {
        matrix[i] = (int*) malloc(N*sizeof(int));
        if (matrix[i] == NULL)
        {
            printf("\nBellek ayrilamadi.");
            return 0;
        }
        for ( j = 0; j < N; j++)
            matrix[i][j] = rand() % 100 + 1;
    }

    // increase size to N+1xN+1
    matrix = realloc(matrix, (N+1)*sizeof(int*));
    for ( i = 0; i < N+1; i++)
        matrix[i] = realloc(matrix[i], (N+1)*sizeof(int));

    // collection as asked
    // collect rows
    for ( i = 0; i < N; i++)
    {
        sum = 0;
        for ( j = 0; j < N; j++)
            sum += matrix[i][j];
        matrix[i][N] = sum;
    }

    // collect columns
    for ( j = 0; j < N; j++)
    {
        sum = 0;
        for ( i = 0; i < N; i++)
            sum += matrix[i][j];
        matrix[N][j] = sum;
    }

    // collect the collections
    sum = 0;
    for ( i = 0; i < N; i++)
        sum += matrix[N][i] + matrix[i][N];
    matrix[N][N] = sum;

    // print matrix
    for ( i = 0; i < N+1; i++)
    {
        for ( j = 0; j < N+1; j++)
            printf("%3d ", matrix[i][j]);
        printf("\n");
    }

    // free memory
    free(matrix);

    return 0;
}