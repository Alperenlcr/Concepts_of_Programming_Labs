#include<stdio.h>
#include<stdlib.h>

int main(){
	
	enum Palet{Siyah=0,Gri=128,Beyaz=255};
	enum Palet renk;
	
	int N,M; //sat�r ve sutun
	int i,j, tmp; 
	int **resim, **histogram;

	
	printf("Lutfen resim boyutlarini satir ve sutun olarak sirasiyla giriniz:");
	scanf("%d %d",&N,&M);
	
	//Resim matrisinin dinamik olarak olu�turulmas�
	resim=(int**)malloc(N*sizeof(int*));
	if(resim == NULL)  {
		printf("Bellek ayr�lamad�...\n");
		return -1;
	}
	
	for(i=0;i<N;i++){
		resim[i]=(int*)malloc(M*sizeof(int));
		if(resim[i] == NULL)  {
			printf("Bellek ayr�lamad�...\n");
			return -1;
		}
	}
	
	//Kullan�c�n�n matris i�eri�ini girmesi. Enum'u burada kulland�m. Enum'u tan�mlaman�z ve kodun herhangi bir yerinde kullanman�z yeterliydi.
	printf("\nLutfen renk paletindeki degerlere uygun bir resim olusturunuz :\nRenk Paleti :Siyah:%d, Gri:%d, Beyaz:%d\n",Siyah,Gri,Beyaz);
	
	for(i=0;i<N;i++){
	printf("%d. satir elemanlarini giriniz :\n", i+1);
		for(j=0;j<M;j++){
			scanf("%d",&resim[i][j]);	
		}
	}
			
	//Resim matrisini g�r�nt�leme
	printf("\nResim :\n");
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
			printf("%3d  ",resim[i][j]);
		printf("\n");
	}
	
	//Histogram matrisinin olu�turulmas�, ilk de�erlerin s�f�r olmas�n� sa�lamak i�in calloc kullan�yoruz, ayr� d�ng� olu�turup s�f�ra e�itlememize gerek kalm�yor.
	histogram=(int**)calloc(3,sizeof(int*)); /* Renk paletinde 3 farkl� renk var*/
		if(histogram == NULL)  {
		printf("Bellek ayr�lamad�...\n");
		return -1;
	}
	
	for(i=0;i<3;i++)
		histogram[i]=(int*)calloc(2,sizeof(int)); /* 2 kolon a�t�k, ilk de�erler: 0 */
	
	
	//Histogram matrisinin frekanslar�n�n bulunmas�
	//Kullan�c�n�n de�erleri do�ru girdi�ini varsayabiliriz demi�tik. Dilerseniz kullan�c� 0,128,255 d���nda de�er girerse uyar�p tekrar girdi almay� sa�layabilirsiniz.
	//Enum'u burada da kullanabilirsiniz. 
	for(i=0;i<N;i++)	{
		for(j=0;j<M;j++){	
			tmp=resim[i][j];
			histogram[(tmp/127)][0]=tmp; //Piksel de�eri
			histogram[(tmp/127)][1]++;// Frekans de�eri Siyah i�in: 0/127=0 histogram[0][1], Gri: 128/127=1 histogram[1][1], Beyaz: 255/127=2 histogram[2][1]	
		}
	}
	
	//Histogram g�r�nt�lenmesi
	printf("\nHistogram :\n");
	for(i=0;i<3;i++)
	{
		for(j=0;j<2;j++)
			printf("%4d  ",histogram[i][j]);
		printf("\n");
	}
	

	for(i=0;i<N;i++)
		free(resim[i]);
	free(resim);
	
	for(i=0;i<3;i++)
		free(histogram[i]);
	free(histogram);
	return 0;
}
