#include <stdio.h>
#include <stdlib.h>


void main()
{
    int *p = (int*)malloc(3*sizeof(int));
    *p = 1;
    *(p+1) = 2;
    *(p+2) = 3;
    printf("\n%p : %d     %p : %d     %p : %d\n", p, *p, (p+1), *(p+1), (p+2), *(p+2));

    char *p1 = (char*)malloc(3*sizeof(char));
    *p1 = 'a';
    *(p1+1) = 'b';
    *(p1+2) = 'c';
    printf("\n%p : %c     %p : %c     %p : %c\n", p1, *p1, (p1+1), *(p1+1), (p1+2), *(p1+2));

    int *p2 = (int*)calloc(3, sizeof(int)); //calloc ayirdigi yerdeki degerleri 0 yapar
    *p2 = 1;
    //*(p2+1) = 2;
    *(p2+2) = 3;
    printf("\n%p : %d     %p : %d     %p : %d\n", p2, *p2, (p2+1), *(p2+1), (p2+2), *(p2+2));

    int *p3 = realloc(p, 4*sizeof(int));        // daha onceden dynamic olarak ayirilmis yerin boyutu arttirilmak istenirse realloc ile arttirilabilir
    // ek istenilen yeri var olan memorye ekleyebilir veya yetersiz gelir ise eski yer, yeni bir yer ayarlayip eskileri oraya kopyalayabilir.
    // azaltmak icin de kullanilabilir
    *(p3+3) = 4;
    printf("\n%p : %d     %p : %d     %p : %d       %p : %d\n", p3, *p3, (p3+1), *(p3+1), (p3+2), *(p3+2), (p3+3), *(p3+3));

    //free(p);  realloc kullandik uzerinde
    free(p1);
    free(p2);
    free(p3);



    //matrix
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
        mat[i][1] = i;
    }
    

}
