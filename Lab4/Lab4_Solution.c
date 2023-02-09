#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// ucuslarin bilgilerini saklayacak yapimiz
typedef struct DATA
{
    int ID;
    char from[50];
    char to[50];
    char saat[20];
    char hat[1];
    int pist;
    struct DATA *next;
}data;

// dosyanan okunan satir bu fonksiyona gelir ve holder node'u doldurulur.
void Split_Data(data* holder,char buff[255],char delimiter[2])
{
    char *token;
//ID
    token=strtok(buff,delimiter);
    holder->ID=atoi(token);
//from
    token=strtok(NULL,delimiter);
    strcpy(holder->from,token);
//to
    token=strtok(NULL,delimiter);
    strcpy(holder->to,token);
//saat
    token=strtok(NULL,delimiter);
    strcpy(holder->saat,token);
//hat
    token=strtok(NULL,delimiter);
    strcpy(holder->hat,token);
//pist
    token=strtok(NULL,delimiter);
    token[strlen(token)-1]='\0';
    holder->pist=atoi(token);
}

// linkli listemizdeki pist numaralarini kume yapmamiz gerekiyor.
// bu fonksiyon yardimiyla yapiyoruz.
void yoksa_ekle(int* pistler, int pist)
{
    int i = 0;
    while (pistler[i] != 0 && pistler[i] != pist)
        i ++;

    if (pistler[i] == 0)
        pistler[i] = pist;
}

// satir satir dosyayi okuyup linkli liste olusturuyoruz.
// dosyada buyukten kucuge sirali oldugu ve linkli listemizi kucukten buyuge istedigimiz icin
// linkli listemize yeni nodelari bastan ekliyoruz.
data* File_Read(char File_Name[50],char delimiter[2], int* pistler)
{
    FILE *fp=fopen(File_Name,"r");
    char buf[255];
    
    data* head=(data*)malloc(sizeof(data));
    data* new;
    if(fgets(buf,255,fp)!=NULL)
    {
        printf("%s",buf);
        Split_Data(head,buf,delimiter);
        yoksa_ekle(pistler, head->pist);    
    }
    head->next = NULL;
    while(fgets(buf,255,fp)!=NULL)
    {
        printf("%s",buf);
        new=(data*)malloc(sizeof(data));
        Split_Data(new,buf,delimiter);
        yoksa_ekle(pistler, new->pist);
        new->next=head;
        head=new;
    }
    fclose(fp);
    return head;
}

// cagirildigi dosya adiyla dosya acip parametre olarak gonderilen pist degerine sahipse yaziyor.
// bastan sona ilerledigi icin dosyaya sirali yazilmis oluyor.
void File_Write_wfprintf(data* head, char File_Name[30], int pist)
{
    FILE *fp=fopen(File_Name,"w");
    char tmp[20];
    while(head!=NULL)
    {
        if (head->pist == pist)
            fprintf(fp, "%d %s %s %s %s %d\n", head->ID, head->from, head->to, head->saat, head->hat, head->pist);
        head=head->next;    
    }
    fclose(fp);
    return ;
}

// linkli listemizi ekrana yazdiriyor.
void Print_List(data* head)
{
    while(head!=NULL)
    {
        printf("%d %s %s %s %s %d\n", head->ID, head->from, head->to, head->saat, head->hat, head->pist);
        head=head->next;
    }
}

// driver
int main(){
    int pistler[100] = {0};              // pistlerin pozitif tam sayi olacagi bilgisi soruda verilmis
    char file_write[30], temp[10];
    data* head;

    printf("Dosyadaki hali\n-----------------\n");
    head=File_Read("ucusBilgi.txt", " \0",  pistler);       // linkli liste dosyadan okunarak olusmus olarak geri donuyor
    printf("\nLinkli listemiz\n-----------------\n");

// linkli listemizi ekrana yazdiriyoruz.
    Print_List(head);
    printf("\n");

// dosya yazma islemleri icin
    int i=0;
    while (pistler[i] != 0)
    {
// dosya adi olusturuyoruz.
        strcpy(file_write, "pist");
        sprintf(temp, "%d", pistler[i]);
        strcat(file_write, temp);
        strcat(file_write, ".txt");
// olusturdugumuz dosya adiyla fonksiyona gonderiyoruz.
        File_Write_wfprintf(head, file_write, pistler[i]);

        printf("%s ", file_write);
        i++;
    }
    printf("dosyalarina ucus bilgileri yazilmistir.\n");

    return 0;
}
