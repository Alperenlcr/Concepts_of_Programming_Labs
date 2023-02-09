#include <stdio.h>
#include <stdlib.h>

void main()
{
    float **mat;
    int i, j, k, tmp;
    int top=0, nrow=16;
    printf("d");

    mat = (float**) malloc(nrow*sizeof(float*));
    if(mat == NULL)
    {
        printf("Bellek ayrilamadi.");
        return;
    }
    printf("d");
    for ( i = 0; i < nrow; i++)
    {
        mat[i]=(float*) calloc(2, sizeof(float));
        mat[i][0] = i+3;
    }
    
    for ( i = 1; i <= 6; i++)
        for ( j = 1; j <= 6; j++)
            for ( k = 1; k <= 6; k++)
            {
                top = i+j+k;
                mat[top-3][1] += (float) 1/(6*6*6);
            }
    printf("\nToplam Olasilik : \n\n");
    float saglama = 0.0;
    for ( i = 0; i < nrow; i++)
    {
        printf("%f  %f\n", mat[i][0], mat[i][1]);
        saglama += mat[i][1];
    }
    printf("\nOlasiliklar toplami : %f\n", saglama);
}