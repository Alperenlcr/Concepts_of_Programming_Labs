#include<stdio.h>
#include<stdlib.h>

int main(){
	
	enum Palet{Siyah=0,Gri=128,Beyaz=255};
	enum Palet renk;
	
	int N,M; //satýr ve sutun
	int i,j, tmp; 
	int **resim, **histogram;

	
	printf("Lutfen resim boyutlarini satir ve sutun olarak sirasiyla giriniz:");
	scanf("%d %d",&N,&M);
	
	//Resim matrisinin dinamik olarak oluþturulmasý
	resim=(int**)malloc(N*sizeof(int*));
	if(resim == NULL)  {
		printf("Bellek ayrýlamadý...\n");
		return -1;
	}
	
	for(i=0;i<N;i++){
		resim[i]=(int*)malloc(M*sizeof(int));
		if(resim[i] == NULL)  {
			printf("Bellek ayrýlamadý...\n");
			return -1;
		}
	}
	
	//Kullanýcýnýn matris içeriðini girmesi. Enum'u burada kullandým. Enum'u tanýmlamanýz ve kodun herhangi bir yerinde kullanmanýz yeterliydi.
	printf("\nLutfen renk paletindeki degerlere uygun bir resim olusturunuz :\nRenk Paleti :Siyah:%d, Gri:%d, Beyaz:%d\n",Siyah,Gri,Beyaz);
	
	for(i=0;i<N;i++){
	printf("%d. satir elemanlarini giriniz :\n", i+1);
		for(j=0;j<M;j++){
			scanf("%d",&resim[i][j]);	
		}
	}
			
	//Resim matrisini görüntüleme
	printf("\nResim :\n");
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
			printf("%3d  ",resim[i][j]);
		printf("\n");
	}
	
	//Histogram matrisinin oluþturulmasý, ilk deðerlerin sýfýr olmasýný saðlamak için calloc kullanýyoruz, ayrý döngü oluþturup sýfýra eþitlememize gerek kalmýyor.
	histogram=(int**)calloc(3,sizeof(int*)); /* Renk paletinde 3 farklý renk var*/
		if(histogram == NULL)  {
		printf("Bellek ayrýlamadý...\n");
		return -1;
	}
	
	for(i=0;i<3;i++)
		histogram[i]=(int*)calloc(2,sizeof(int)); /* 2 kolon açtýk, ilk deðerler: 0 */
	
	
	//Histogram matrisinin frekanslarýnýn bulunmasý
	//Kullanýcýnýn deðerleri doðru girdiðini varsayabiliriz demiþtik. Dilerseniz kullanýcý 0,128,255 dýþýnda deðer girerse uyarýp tekrar girdi almayý saðlayabilirsiniz.
	//Enum'u burada da kullanabilirsiniz. 
	for(i=0;i<N;i++)	{
		for(j=0;j<M;j++){	
			tmp=resim[i][j];
			histogram[(tmp/127)][0]=tmp; //Piksel deðeri
			histogram[(tmp/127)][1]++;// Frekans deðeri Siyah için: 0/127=0 histogram[0][1], Gri: 128/127=1 histogram[1][1], Beyaz: 255/127=2 histogram[2][1]	
		}
	}
	
	//Histogram görüntülenmesi
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
