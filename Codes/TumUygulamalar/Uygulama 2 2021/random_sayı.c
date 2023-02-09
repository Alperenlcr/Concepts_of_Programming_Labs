#include<stdio.h>
#include<stdlib.h>

#define randnum(min, max) (min + (rand() % (int) (max-min+1)))

int main(){
	int Deneme_Sayisi;
	int x,y,z, i;
	//srand(time(NULL));
	printf("Toplam Zar Atis Sayisini Giriniz: ");
	scanf("%d",&Deneme_Sayisi);
	for(i=0;i<Deneme_Sayisi;i++){
		printf("x: %d, y: %d, z: %d \n", randnum(2,5),  randnum(6,8),  randnum(9,11));
	}	

    return 0;
}

// 25 --> 24%4=0  0+2 = 2, 25%4=1  1+2 = 3, 26%4=2  2+2 = 4, 27%4=3  3+2 = 5, 28%4=0  0+2 = 2
