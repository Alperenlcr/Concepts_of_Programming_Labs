#include<stdio.h>
#include<stdlib.h>
#define P (float)1 / (6*6*6)

int main(){
    float **mat;
    int i, j, k, top, nrow=16;
    
    mat= (float**)malloc(nrow*sizeof(float*)); /* toplam deðerleri 3 ile 18 arasi degisir, 16 satir acilmali */
    if(mat == NULL)  {
		printf("Bellek ayrýlamadý...\n");
		return -1;
	}
    for(i=0; i<nrow; i++)
		mat[i] = (float*)calloc(2, sizeof(float)); /*2 kolon actik, elemanlarin ilk degeri: 0 */
	
    for(i=1; i<=6; i++){    /*her bir zarin olasi degeri: 1-6 arasi */
        for(j=1; j<=6; j++) {  /*her bir zarin olasi degeri: 1-6 arasi */
			for(k=1; k<=6; k++) {  /*her bir zarin olasi degeri: 1-6 arasi */
	    		top = i+j+k;
	   			mat[top-3][0] = top;
	    		mat[top-3][1] += P;

/* mesela zarin 4 toplamini vermesi 3kez gozlenir: i=1,j=1,k=2; ve i=1,j=2,k=1; ve i=2,j=1,k=1 durumlari... 4'u her gozledigimizde 1/216 kadar artiririz. Dolayisiyla, 3kez 1/216 ekledik; direkt 3/216 yazmadik. 
mat[0][0]=3; mat[1][0]=4; mat[2][0]=5; => dolayisiyla "top" degeri, "top-3"ncu satira islenir */
			}
        }
    }
   /* matrisin görüntülenmesi */
   printf("Toplam\tOlasilik\n\n");
   for(i=0;i<16;i++){
   		printf("%.f\t%.8f\n",mat[i][0],mat[i][1]);
   	}
   		
   			
    for(i=0;i<16;i++)
    	free(mat[i]);
    free(mat);
    return 0;
}



