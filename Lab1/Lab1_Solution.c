#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

int main()
{
    int j, i, smallest=100, smallest_in_all=100;
    srand(time(NULL));

    printf("\nPopulation size : %d \nIteration number : %d\n\n", populasyon, iterasyon_sayisi);
    // Initial
    printf("Initial Population :\n");
    for ( i = 0; i < populasyon; i++)
    {
        int r = rand() % 50 + 1;
        if (smallest > r)
            smallest = r;

        printf("%d\t", r);
    }
    printf("\nInitial best cost : %d value\n", maaliyet_fonksiyonu(smallest));
    printf("\n\n");
    if (smallest_in_all > smallest)
        smallest_in_all = smallest;


    printf("\nIteration Start\n\n\n\n");

    // Iterations
    for ( j = 0; j < iterasyon_sayisi; j++)
    {
        smallest=100;
        printf("Iteration-%d new population :\n", j+1);
        for ( i = 0; i < populasyon; i++)
        {
            int r = rand() % 50 + 1;
            if (smallest > r)
                smallest = r;
            
            printf("%d\t", r);
        }
        printf("\nBest cost in iteration-%d : %d value\n", j+1, maaliyet_fonksiyonu(smallest));
        printf("\n\n");
        if (smallest_in_all > smallest)
            smallest_in_all = smallest;
        
    }
    printf("\nBest cost in all iterations: %d\n", maaliyet_fonksiyonu(smallest_in_all));

    return 0;
}
