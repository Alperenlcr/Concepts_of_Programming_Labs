#include <stdio.h>
#include <stdlib.h>

void main()
{
    enum Palet{Siyah=0, Gri=128, Beyaz=255};
    enum Palet renk;
    int N, M;
    int i, j, tmp;
    int **resim, **histogram;

    printf("Satir ve sutun degerleri girin (bir bosluk ile) : ");
    scanf("%d %d", &N, &M);

    resim = (int**) malloc(N*sizeof(int*));
    if (resim == NULL)
    {
        printf("\nBellek ayrilamadi.");
        return;
    }
    for ( i = 0; i < N; i++)
    {
        resim[i] = (int*) malloc(M*sizeof(int));
        if (resim == NULL)
        {
            printf("\nBellek ayrilamadi.");
            return;
        }
    }
    printf("Resim degerlerini giriniz -- Siyah : %d     Gri : %d     Beyaz : %d\n", renk=Siyah, renk=Gri, renk=Beyaz);
    //matris alma
    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < M; j++)
            scanf("%d", &resim[i][j]);
        printf("\n");
    }
    //matris gosterme
    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < M; j++)
            printf("%d ", resim[i][j]);
        printf("\n");
    }
    histogram = (int**) calloc(3, sizeof(int*));
    for ( i = 0; i < 3; i++)
        histogram[i] = (int*) calloc(2, sizeof(int));

    histogram[0][0] = renk=Siyah;
    histogram[1][0] = renk=Gri;
    histogram[2][0] = renk=Beyaz;

    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < M; j++)
        {
            tmp = resim[i][j];
            histogram[(tmp/127)][1] ++;
        }
    }
    printf("\nHistogram :\n");
    for ( i = 0; i < 3; i++)
    {
        for ( j = 0; j < 2; j++)
            printf("%d ", histogram[i][j]);
        printf("\n");
    }
}