#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define baslangic_size 4
struct arac{
	char model[MAX];
	int yil;
	int satis_fiyati;
	int adet;
};
int descending(char model1[MAX], char model2[MAX]);
int ascending(char model1[MAX], char model2[MAX]);
void swap(struct arac *a, struct arac *b);
void selectionSort(struct arac array[], const int size, int (*compare)(char model1[MAX], char model2[MAX]));
int main() 
{
	char baslangic_modeller[baslangic_size][MAX] = {"FiatB", "RenaultB", "MercedesB", "ToyotaB"};
	int baslangic_yillar[baslangic_size] = {2010, 2012, 2011, 2013};
	unsigned int baslangic_satis_fiyatlar[baslangic_size] = {101000, 103000, 102000, 104000};
	int baslangic_adetler[baslangic_size] = {1, 3, 2, 4};
	int order; // 1 = ascending, 2 = descending
	int counter, counter2, choice=1;

	struct arac *araclar;
	araclar = (struct arac*)malloc(baslangic_size*sizeof(struct arac));

	for(counter = 0; counter < baslangic_size; counter++)
	{
        strcpy(araclar[counter].model, baslangic_modeller[counter]);
		araclar[counter].yil = baslangic_yillar[counter];
		araclar[counter].satis_fiyati = baslangic_satis_fiyatlar[counter];
		araclar[counter].adet = baslangic_adetler[counter];
	}

	while (choice == 1)
    {
        printf("\nAraç eklemek için 1, var olan listeyle devam etmek için 2 giriniz : ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            char temp[MAX];
            araclar = realloc(araclar, (counter)*sizeof(struct arac));
            printf("\nEklenecek arac tipinin ozelliklerini giriniz.");
            printf("\nModel : ");
            scanf("%s", temp);
            *temp = toupper(*temp);
            strcpy(araclar[counter].model, temp);
            printf("Yil : ");
            scanf("%d", &araclar[counter].yil);
            printf("Satis fiyati : ");
            scanf("%d", &araclar[counter].satis_fiyati);
            printf("Adet : ");
            scanf("%d", &araclar[counter].adet);
            counter ++;
        }
    }
    
	printf("\nArtan siralama için 1, azalan için 2 giriniz :");
	scanf("%d", &order);
	
	if(order == 1)
	{
		selectionSort(araclar, counter, ascending);
	}
	else{
		selectionSort(araclar, counter, descending);
	}
	for(counter2 = 0; counter2 < counter; counter2++)
	{
		printf("(%s, %d, %d, %d) \n", araclar[counter2].model, araclar[counter2].yil, araclar[counter2].satis_fiyati, araclar[counter2].adet);
	}
	
	return 0; 
}

int ascending(char model1[MAX], char model2[MAX])
{
    if (strcmp(model1, model2)<0)
    	return 1;
    return 0;
}

int descending(char model1[MAX], char model2[MAX])
{
    if (strcmp(model1, model2)>0)
    	return 1;
    return 0;
}

void swap(struct arac *a, struct arac *b)
{
	struct arac tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
void selectionSort(struct arac array[], const int size, int (*compare)(char model1[MAX], char model2[MAX]))
{
	int i, j, smallestOrLargest;
	for(i=0; i < size-1; i++)
	{
		smallestOrLargest = i;
		for(j=i+1; j < size; j++)
		{
			if(!compare(array[smallestOrLargest].model, array[j].model))
				smallestOrLargest = j;
		}
		swap(&array[smallestOrLargest], &array[i]);
	}
}
