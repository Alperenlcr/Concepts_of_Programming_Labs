#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Dersler Dersler;
typedef struct Ogrenciler Ogrenciler;

// dersleri linkli listede ders koduna gore sirali tutuyoruz. dersteki_nums dersi alan ogrencilerin numaralarini sakliyor ve
// ogrenci_cikar, ogrenci_ekle, ders_cikar, ders_ekle, dersler_oku, ogrenci_ders_kayit_tara fonksiyonlari degerlerini degistirebiliyorken
// baska fonksiyonlar icinden veri alabiliyor
struct Dersler {
    char ders_kodu[50];
    char ders_adi[50];
    int kredi;
    int kontenjan;
    int* dersteki_nums;
    Dersler* next;
};

// ogrencileri cift yonlu linkli listede ogrenci numarasina gore sirali tutuyoruz.
// bilgiler ogrenci_ekle, ogrenciler_oku, ogrenci_cikar fonksiyonlarindan etkileniyor
// ayrica kredi bilgisi ve ders sayisi ders_cikar'dan etkileniyor
// baska fonksiyonlar icinden veri alabiliyor
struct Ogrenciler {
    int ogrenci_numarasi;
    char ad[50];
    char soyad[50];
    int ders_sayisi;
    int kredi_bilgisi;
    Ogrenciler* next;
    Ogrenciler* prev;
};

// okuma
void ogrenciler_oku(Ogrenciler* head, char File_Name[50], char delimiter[2]);
Dersler* dersler_oku(Dersler* head, Ogrenciler* head_ogrenciler, char File_Name[50], char delimiter[2], int* log_ID);
void ogrenci_ders_kayit_tara(char ders_kodu[50], int* liste, char delimiter[2], int* log_ID);
// yazma
void ogrenciler_yaz(Ogrenciler* head, char File_Name[50]);
void dersler_yaz(Dersler* head, char File_Name[50]);
// ekle-cikar
Ogrenciler* ogrenci_cikar(Ogrenciler *head_ogrenciler, Dersler *head_dersler, int ogrenci_numarasi, int* log_ID);
Ogrenciler* ogrenci_ekle(Ogrenciler* head_ogrenciler, Dersler* head_dersler, int* log_ID);
Dersler* ders_cikar(Dersler *head_dersler, Ogrenciler *head_ogrenciler, char ders_kodu[50], int* log_ID);
Dersler* ders_ekle(Dersler* head_dersler, int* log_ID);
// ekrana yazdirma
void yazdir_ogrenciler(Ogrenciler* head);
void yazdir_dersler(Dersler* head, char ders_kodu[50]);     // DERSKODU.txt icin de kullaniliyor
// dizi islemleri icin
void remove_first(int* Array, int* size, int value);
int len(int* Array);
int find(int* Array, int value);
int* remove_element(int* array, int sizeOfArray, int indexToRemove);
void selection_sort(int* Array, int size);
// arama
int ogrenci_ara(Ogrenciler* head_ogrenciler, int numara);
int ders_ara(Dersler* head_dersler, char ders_kodu[50]);
// ÖĞRENCİNO_DERSPROGRAMI.txt icin kullaniliyor
void ders_programi_olustur(Dersler* head_dersler, Ogrenciler* head_ogrenciler, int numara);
// spesifik islemler icin
void ogrenciye_ders_ekle_sil(Ogrenciler* head_ogrenciler, Dersler* head_dersler, int numara, int* log_ID);
// function pointer array ile kullanilan iki fonksiyon
void output_yazilari_1();
void output_yazilari_2();

int main()
{
    void (*function_pointer_array[2]) ();
    function_pointer_array[0] = output_yazilari_1;
    function_pointer_array[1] = output_yazilari_2;

    int log_ID=0;
    Ogrenciler* head_ogrenciler = (Ogrenciler*) malloc(sizeof(Ogrenciler));
    head_ogrenciler->next = NULL;
    head_ogrenciler->prev = NULL;
    ogrenciler_oku(head_ogrenciler , "ogrenciler.txt", ",\0");
    Dersler* head_dersler = (Dersler*) malloc(sizeof(Dersler));
    head_dersler->next = NULL;
    head_dersler = dersler_oku(head_dersler, head_ogrenciler, "dersler.txt", ",\0", &log_ID);

//  *************************************************
//                      MENU
//  *************************************************
    int numara, choice = 0;
    char ders_kodu[50];
    while (choice != 10)
    {
        (*function_pointer_array[0]) ();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            yazdir_dersler(head_dersler, "yok");           
            break;
        case 2:
            yazdir_ogrenciler(head_ogrenciler);
            break;
        case 3:
            // ders ekle
            head_dersler = ders_ekle(head_dersler, &log_ID);
            break;
        case 4:
            // ders sil
            printf("Silinecek dersin kodunu giriniz (listeyi gormek icin 1 giriniz) : ");
            scanf("%s", ders_kodu);
            if (!strcmp(ders_kodu, "1"))
            {
                yazdir_dersler(head_dersler, "yok");
                printf("Silinecek dersin kodunu giriniz : ");
                scanf("%s", ders_kodu);
            }
            head_dersler = ders_cikar(head_dersler, head_ogrenciler, ders_kodu, &log_ID);
            break;
        case 5:
            head_ogrenciler = ogrenci_ekle(head_ogrenciler, head_dersler, &log_ID);
            break;
        case 6:
            printf("Silinecek ogrencinin numarasini giriniz (listeyi gormek icin 1 giriniz) : ");
            scanf("%d", &numara);
            if (numara == 1)
            {
                yazdir_ogrenciler(head_ogrenciler);
                printf("Silinecek ogrencinin numarasini giriniz : ");
                scanf("%d", &numara);
            }
            // ogrenci numarasina gore ogrenciler linkli listinden ve dersler linkli listinden siler.
            head_ogrenciler = ogrenci_cikar(head_ogrenciler, head_dersler, numara, &log_ID);
            break;
        case 7:
            printf("Duzenleme yapilacak ogrencinin numarasini giriniz (listeyi gormek icin 1 giriniz) : ");
            scanf("%d", &numara);
            if (numara == 1)
            {
                yazdir_ogrenciler(head_ogrenciler);
                printf("Duzenleme yapilacak ogrencinin numarasini giriniz : ");
                scanf("%d", &numara);
            }
            ogrenciye_ders_ekle_sil(head_ogrenciler, head_dersler, numara, &log_ID);
            break;
        case 8:
            printf("Dosyasi olusturulacak dersin kodunu giriniz (listeyi gormek icin 1 giriniz) : ");
            scanf("%s", ders_kodu);
            if (!strcmp(ders_kodu, "1"))
            {
                yazdir_dersler(head_dersler, "yok");
                printf("Dosyasi olusturulacak dersin kodunu giriniz : ");
                scanf("%s", ders_kodu);
            }
            yazdir_dersler(head_dersler, ders_kodu);
            break;
        case 9:
            printf("Ders programi dosya olarak olusturulacak ogrencinin numarasini giriniz (listeyi gormek icin 1 giriniz) : ");
            scanf("%d", &numara);
            if (numara == 1)
            {
                yazdir_ogrenciler(head_ogrenciler);
                printf("Ders programi dosya olarak olusturulacak ogrencinin numarasini giriniz : ");
                scanf("%d", &numara);
            }
            ders_programi_olustur(head_dersler, head_ogrenciler, numara);
            break;
        case 10:
            break;
        default:
            (*function_pointer_array[1]) ();
            break;
        }
        ogrenciler_yaz(head_ogrenciler, "ogrenciler.txt");
        dersler_yaz(head_dersler, "dersler.txt");
    }
    free(head_dersler);
    free(head_ogrenciler);
    return 0;
}

Dersler* ders_cikar(Dersler *head_dersler, Ogrenciler *head_ogrenciler, char ders_kodu[50], int* log_ID)
{
    Dersler *iter_ders = (Dersler*) malloc(sizeof(Dersler));
    iter_ders = head_dersler;
    Ogrenciler *iter_ogrenci = (Ogrenciler*) malloc(sizeof(Ogrenciler));
    iter_ogrenci = head_ogrenciler;
    FILE* log_fp = fopen("OgrenciDersKayit.txt", "a");
// ders var mi
    if (!ders_ara(iter_ders, ders_kodu))
    {
        printf("%s kodlu ders acik degildir.\n", ders_kodu);
    }
    else
    {
    // listede ara bul
        while (strcmp(iter_ders->ders_kodu, ders_kodu))
            iter_ders = iter_ders->next;
        int i, size = len(iter_ders->dersteki_nums)-1;
    // ogrencilerinin kredi ve ders sayilarini dusur
        for ( i = 0; i < size; i++)
        {
            while (iter_ogrenci->ogrenci_numarasi != iter_ders->dersteki_nums[i])
                iter_ogrenci = iter_ogrenci->next;
    // log mesaji yaz her ogrenci icin
            (*log_ID) ++;
            fprintf(log_fp, "%d,%s,%d,01.01.2023,ders kapandi\n", *log_ID, iter_ders->ders_kodu, iter_ogrenci->ogrenci_numarasi);
            iter_ogrenci->ders_sayisi -= 1;
            iter_ogrenci->kredi_bilgisi -= iter_ders->kredi;
        }
    // ve dersi listeden cikar
        iter_ders = head_dersler;
        if (!strcmp(iter_ders->ders_kodu, ders_kodu))
            head_dersler = iter_ders->next;
        else
        {
            while (strcmp(iter_ders->next->ders_kodu, ders_kodu))
                iter_ders = iter_ders->next;
            iter_ders->next = iter_ders->next->next;
        }
    }
    fclose(log_fp);
    return head_dersler;
}

Dersler* ders_ekle(Dersler* head_dersler, int* log_ID)
{
    Dersler* new = (Dersler*) malloc(sizeof(Dersler));
    Dersler* iter_ders = (Dersler*) malloc(sizeof(Dersler));
    iter_ders = head_dersler;
// ders kodu iste
    printf("Eklemek istediginiz dersin kodunu giriniz : ");
    scanf("%s", new->ders_kodu);
// ders zaten ekli mi
    if (ders_ara(head_dersler, new->ders_kodu))
        printf("%s kodlu ders zaten bulunmaktadir.\n", new->ders_kodu);
    // bilgileri al
    else
    {
        getchar();
        printf("Dersin adi : ");
        scanf("%[^\n]", new->ders_adi);
        printf("Dersin kontenjani : ");
        scanf("%d", &new->kontenjan);        
        printf("Dersin kredisi : ");
        scanf("%d", &new->kredi);        
        new->dersteki_nums = (int*) calloc(sizeof(int), 0);
    // koduna gore siraya ekle
        if (strcmp(iter_ders->ders_kodu, new->ders_kodu) > 0)
        {
            new->next = iter_ders;
            head_dersler = new;
        }
        else
        {
            while (iter_ders->next != NULL && strcmp(iter_ders->next->ders_kodu, new->ders_kodu) < 0)
                iter_ders = iter_ders->next;
            new->next = iter_ders->next;
            iter_ders->next = new;
        }
        printf("%s Kodlu ders dersler listesine eklenmistir. Menude \"Kayitli ogrenciye ders ekle veya sil\"den derse ogrenci ekleyebilirsiniz.\n", new->ders_kodu);
    }
    return head_dersler;
}

Ogrenciler* ogrenci_cikar(Ogrenciler *head_ogrenciler, Dersler *head_dersler, int ogrenci_numarasi, int* log_ID)
{
    Ogrenciler *iter_ogrenci = (Ogrenciler*) malloc(sizeof(Ogrenciler));
    iter_ogrenci = head_ogrenciler;

// ogrencinin aldigi dersleri tek yonlu linkli listenin dynamic dizilerinde bulup silme
    Dersler *iter_ders = (Dersler*) malloc(sizeof(Dersler));
    iter_ders = head_dersler;
    FILE* log_fp = fopen("OgrenciDersKayit.txt", "a");

    while(iter_ders != NULL)
    {
        int* bir_eleman_azalmis_liste_dondur(int* liste, int eleman)
        {
            int i, j, length = len(liste);
            length --;
            int* yeni_liste = (int*) calloc(sizeof(int), length);
            for ( i = 0, j = 0; i < length; i++, j++)
            {
                if (liste[j] != eleman)
                    yeni_liste[i] = liste[j];

                else
                    i --;
            }
            return yeni_liste;
        }
// Dersi alan numaralar
        int i = 0;
        int size = len(iter_ders->dersteki_nums);
        for ( i = 0; i < size-1; i++)
            if (iter_ders->dersteki_nums[i] == ogrenci_numarasi)
            {
                iter_ders->dersteki_nums = bir_eleman_azalmis_liste_dondur(iter_ders->dersteki_nums, ogrenci_numarasi);
// log dosyasina silindi mesaji yaz
                (*log_ID) ++;
                fprintf(log_fp, "%d,%s,%d,01.01.2023,sildi\n", *log_ID, iter_ders->ders_kodu, ogrenci_numarasi);
            }
        iter_ders=iter_ders->next;
    }
    fclose(log_fp);

// ogrenciyi cift yonlu linkli listeden cikarma
// ilk eleman ise
    if (iter_ogrenci->ogrenci_numarasi == ogrenci_numarasi)
    {
        iter_ogrenci->next->prev = NULL;
        return iter_ogrenci->next;
    }

    while (iter_ogrenci->next != NULL && iter_ogrenci->next->ogrenci_numarasi != ogrenci_numarasi)
        iter_ogrenci = iter_ogrenci->next;

    if (iter_ogrenci->next == NULL)
        printf("\n%d Numarali Ogrenci Listede Bulunamadi\n", ogrenci_numarasi);
    else if (iter_ogrenci->next->next == NULL)
        iter_ogrenci->next = NULL;
    else
    {
        iter_ogrenci->next->next->prev = iter_ogrenci;
        iter_ogrenci->next = iter_ogrenci->next->next;
    }
    return head_ogrenciler;
}

Ogrenciler* ogrenci_ekle(Ogrenciler* head_ogrenciler, Dersler* head_dersler, int* log_ID)
{
    Ogrenciler *iter_ogrenci = (Ogrenciler*) malloc(sizeof(Ogrenciler));
    Ogrenciler* new = (Ogrenciler*) malloc(sizeof(Ogrenciler));
    iter_ogrenci = head_ogrenciler;
    FILE* log_fp = fopen("OgrenciDersKayit.txt", "a");

    printf("Ogrencinin numarasini giriniz : ");
    scanf("%d", &new->ogrenci_numarasi);
    getchar();
    if (ogrenci_ara(head_ogrenciler, new->ogrenci_numarasi))
    {
        printf("%d numarali ogrenci zaten bulunmaktadir. Bu ogrenciye ders eklemek veya silmek istiyorsaniz menuden seciniz.\n", new->ogrenci_numarasi);
        return head_ogrenciler;
    }
    printf("Ogrencinin adini giriniz : ");
    scanf("%[^\n]", new->ad);
    getchar();
    printf("Ogrencinin soyadini giriniz : ");
    scanf("%[^\n]", new->soyad);
    getchar();
    new->ders_sayisi = 0;
    new->kredi_bilgisi = 0;
// -1 girene kadar ders iste
    printf("\nOgrencinin derslerinin ders kodlarini giriniz. '-1' girene kadar ders kodlari girebilirsiniz.\n");
    char ders_kodu[50];
    printf("Ders kodu giriniz : ");
    scanf("%s", ders_kodu);
    while (strcmp(ders_kodu, "-1"))
    {
    // ders var mi
        if (!ders_ara(head_dersler, ders_kodu))
            printf("%s kodlu ders bulunmamaktadir.\n", ders_kodu);
        else
        {
            Dersler* iter_dersler = (Dersler*) malloc(sizeof(Dersler));
            iter_dersler = head_dersler;
            while (strcmp(iter_dersler->ders_kodu, ders_kodu))
                iter_dersler = iter_dersler->next;
    // zaten aliyor mu diye kontrol
            if (find(iter_dersler->dersteki_nums, new->ogrenci_numarasi))
                printf("Ogrenci zaten dersi almaktadir.\n");
    // dersin kontenjani yeterli mi diye bak
            else if (iter_dersler->kontenjan < len(iter_dersler->dersteki_nums))
                printf("%s kodlu derste kontenjan doludur. Lutfen bolume dilekce verin arttirilmasin :)\n", ders_kodu);
    // varsa o dersin ogrenci numaralarina sirayi bozmayacak sekilde ekle
            else
            {
                int i = 0, size = len(iter_dersler->dersteki_nums)-1;
                new->kredi_bilgisi += iter_dersler->kredi;
                new->ders_sayisi += 1;
                iter_dersler->dersteki_nums = realloc(iter_dersler->dersteki_nums, (size+1)*sizeof(int));

                for (i = size - 1; (i >= 0 && iter_dersler->dersteki_nums[i] > new->ogrenci_numarasi); i--)
                    iter_dersler->dersteki_nums[i + 1] = iter_dersler->dersteki_nums[i];
            
                iter_dersler->dersteki_nums[i + 1] = new->ogrenci_numarasi;

                (*log_ID) += 1;
                fprintf(log_fp, "%d,%s,%d,01.01.2023,kayitli\n", *log_ID, ders_kodu, new->ogrenci_numarasi);
            }
        }
        printf("Ders kodu giriniz : ");
        scanf("%s", ders_kodu);
    }
    fclose(log_fp);

// return updated linked list
    // head
    if (new->ogrenci_numarasi < iter_ogrenci->ogrenci_numarasi)
    {
        iter_ogrenci->prev = new;
        new->next = iter_ogrenci;
        new->prev = NULL;
        return new;
    }
    else
    {
        while (iter_ogrenci->next != NULL && new->ogrenci_numarasi > iter_ogrenci->next->ogrenci_numarasi)
            iter_ogrenci = iter_ogrenci->next;
        new->next = iter_ogrenci->next;
        new->prev = iter_ogrenci;
        iter_ogrenci->next = new;
    }
    return head_ogrenciler;
}

int ogrenci_ara(Ogrenciler* head_ogrenciler, int numara)
{
    Ogrenciler* iter = (Ogrenciler*) malloc(sizeof(Ogrenciler));
    iter = head_ogrenciler;
    while (iter->next != NULL && iter->ogrenci_numarasi != numara)
        iter = iter->next;
    if (iter->ogrenci_numarasi == numara)
        return 1;
    return 0;
}

void ogrenciye_ders_ekle_sil(Ogrenciler* head_ogrenciler, Dersler* head_dersler, int numara, int* log_ID)
{
// ogrenci var mi diye kontrol
    if (!ogrenci_ara(head_ogrenciler, numara))
    {
        printf("%d numarali ogrenci bulunmamaktadir.\n", numara);
        return ;
    }
    FILE* log_fp = fopen("OgrenciDersKayit.txt", "a");

    Ogrenciler *iter_ogrenci = (Ogrenciler*) malloc(sizeof(Ogrenciler));
    iter_ogrenci = head_ogrenciler;
    Dersler* iter_dersler = (Dersler*) malloc(sizeof(Dersler));
    iter_dersler = head_dersler;
    int choice;
    char ders_kodu[50];
    printf("%d numarali ogrenciye ders eklemek icin 1 , derslerinden silmek icin 2 , menuye donmek icin 3 giriniz: ", numara);
    scanf("%d", &choice);
    if (choice == 1)
    {
    // ders ekleme
        // ogrenci bulunmali
        while (iter_ogrenci->ogrenci_numarasi != numara)
            iter_ogrenci = iter_ogrenci->next;

        // ders var mi diye bakilmali
        printf("Dersin kodunu giriniz : ");
        scanf("%s", ders_kodu);
        if (!ders_ara(head_dersler, ders_kodu))
            printf("Ders bulunamadi.");
        else
        {
        // dersin kontenjani var mi diye bakilmali
            while (strcmp(iter_dersler->ders_kodu, ders_kodu))
                iter_dersler = iter_dersler->next;
            if (iter_dersler->kontenjan == len(iter_dersler->dersteki_nums)-1)
            {
                printf("Derste kontenjan dolmustur.\n");
            }
        // zaten aliyor mu diye kontrol
            else if (find(iter_dersler->dersteki_nums, numara))
            {
                printf("Ogrenci zaten dersi almaktadir.\n");
            }
        // dersin listesine numara eklenmeli
        // kredisi ve dersi etkilenmeli
        // log a etkilemeli
            else
            {
                int i = 0, size = len(iter_dersler->dersteki_nums)-1;
                iter_ogrenci->kredi_bilgisi += iter_dersler->kredi;
                iter_ogrenci->ders_sayisi += 1;
                iter_dersler->dersteki_nums = realloc(iter_dersler->dersteki_nums, (size+1)*sizeof(int));

                for (i = size - 1; (i >= 0 && iter_dersler->dersteki_nums[i] > numara); i--)
                    iter_dersler->dersteki_nums[i + 1] = iter_dersler->dersteki_nums[i];

                iter_dersler->dersteki_nums[i + 1] = numara;

                (*log_ID) += 1;
                fprintf(log_fp, "%d,%s,%d,01.01.2023,kayitli\n", *log_ID, ders_kodu, numara);
            }
        }
    }
    else if (choice == 2)
    {
    // ders silme
        // ogrenci bulunmali
        while (iter_ogrenci->ogrenci_numarasi != numara)
            iter_ogrenci = iter_ogrenci->next;
        // ders var mi diye bakilmali
        printf("Dersin kodunu giriniz : ");
        scanf("%s", ders_kodu);
        // ders bulunmali
        while (strcmp(iter_dersler->ders_kodu, ders_kodu))
            iter_dersler = iter_dersler->next;
        if (!ders_ara(head_dersler, ders_kodu))
            printf("Ders bulunamadi.");
        // acaba aliyor mu diye kontrol
        else
        {
        // zaten aliyor mu diye kontrol
            if (!find(iter_dersler->dersteki_nums, numara))
            {
                printf("Ogrenci zaten dersi almamaktadir.\n");
            }
        // dersin listesinden numara silinmeli
        // kredisi ve dersi etkilenmeli
        // log a etkilemeli
            else
            {
                int i = 0, size = len(iter_dersler->dersteki_nums)-1;
                iter_ogrenci->kredi_bilgisi -= iter_dersler->kredi;
                iter_ogrenci->ders_sayisi -= 1;
            // index bul ve fonksiyona gonder
                while (iter_dersler->dersteki_nums[i] != numara)
                    i ++;

                iter_dersler->dersteki_nums = remove_element(iter_dersler->dersteki_nums, size, i);
                iter_dersler->dersteki_nums[size-1] = 0;
                iter_dersler->dersteki_nums = (int*) realloc(iter_dersler->dersteki_nums, (size-1)*sizeof(int));

                (*log_ID) += 1;
                fprintf(log_fp, "%d,%s,%d,01.01.2023,silindi\n", *log_ID, ders_kodu, numara);
            }
        }
    }
    else if (choice == 3)
        return ;
    else
    {
        printf("Yanlis girdi !!\n");
        ogrenciye_ders_ekle_sil(head_ogrenciler, head_dersler, numara, log_ID);
    }
    fclose(log_fp);
}

int ders_ara(Dersler* head_dersler, char ders_kodu[50])
{
    Dersler* iter = (Dersler*) malloc(sizeof(Dersler));
    iter = head_dersler;
    while (iter->next != NULL && strcmp(iter->ders_kodu, ders_kodu))
        iter = iter->next;
    if (!strcmp(iter->ders_kodu, ders_kodu))
        return 1;
    return 0;
}

// Öğrenci numarası verilen bir öğrencinin aldığı tüm dersleri listeleyen ve ÖĞRENCİNO_DERSPROGRAMI.txt isminde dosyaya yazan fonksiyonu yazınız.
void ders_programi_olustur(Dersler* head_dersler, Ogrenciler* head_ogrenciler, int numara)
{
    // ogrenci var mi diye bak
    if (!ogrenci_ara(head_ogrenciler, numara))
    {
        printf("%d numarali ogrenci bulunmadigi icin dosya olusturulmadi.\n", numara);
        return ;
    }
    char File_Name[50];
    sprintf(File_Name, "%d", numara);
    strcat(File_Name, "_DERSPROGRAMI.txt");
    FILE *fp = fopen(File_Name, "w");
    Dersler *iter = (Dersler*) malloc(sizeof(Dersler));
    iter = head_dersler;
    while(iter != NULL)
    {
        int i = 0;
        int size = len(iter->dersteki_nums);
        for ( i = 0; i < size-1; i++)
            if (iter->dersteki_nums[i] == numara)
                fprintf(fp, "%s\t\t%40s\t\tkredi_bilgisi : %d  kontenjan siniri : %d  dersi alan kisi sayisi : %d\n", iter->ders_kodu, iter->ders_adi, iter->kredi, iter->kontenjan, size-1);
        iter = iter->next;
    }
    fclose(fp);
}

//    Ders kodu verilen bir derse kayıtlı olan tüm öğrencileri listeleyen fonksiyonu yazınız. Bu fonksiyon yardımı ile tüm derslere
//     ait sınıf listesini DERSKODU.txt isim formatında dosyaya yazdırınız.

// Dersler linkli listemizi ekrana yazdiriyor.
void yazdir_dersler(Dersler* head, char ders_kodu[50])
{
    FILE *fp;
    int first=1, amac = 1;   // 1 : DERSKODU.txt olustur     0 : olusturma, sadece ekrana dersleri yazdir.
    if (!strcmp(ders_kodu, "yok"))
    {
        printf("\n\t\t*********\n\t\t*Dersler*\n\t\t*********\n");
        amac = 0;
    }
    Dersler *iter = (Dersler*) malloc(sizeof(Dersler));
    iter = head;
    while(iter != NULL)
    {
        int i = 0;
        int size = len(iter->dersteki_nums);
        if (!amac)
        {
            printf("\n");
            printf("%s %s kredi_bilgisi : %d kontenjan siniri : %d dersi alan kisi sayisi : ", iter->ders_kodu, iter->ders_adi, iter->kredi, iter->kontenjan);
            printf("%d\n", size-1);
            printf("Dersi alan numaralar : ");
            for ( i = 0; i < size-1; i++)
                printf("%d ", iter->dersteki_nums[i]);
        }
        for ( i = 0; i < size-1; i++)
        {
            if (amac && !strcmp(ders_kodu, iter->ders_kodu))
            {
                if (first)
                {
                    first = 0;
                    char File_Name[50];
                    strcpy(File_Name, ders_kodu);
                    strcat(File_Name, ".txt");
                    fp = fopen(File_Name, "w");
                }
                fprintf(fp, "%d\n", iter->dersteki_nums[i]);
            }
        }

        iter=iter->next;
    }
    if (amac && !first)
        fclose(fp);
    else if(amac)
        printf("%s kodlu ders bulunmamaktadir.\n", ders_kodu);
    printf("\n");
}
// ders koduna gore OgrenciDersKayit.txt i okuyor ve dersler.txt den
// dersler linkli listemize eklenmis dersleri alan ogrenci log larina bakarak dinamik diziyi dolduruyor 
void ogrenci_ders_kayit_tara(char ders_kodu[50], int* liste, char delimiter[2], int* log_ID)
{
    char buf[255];
    FILE *fpr = fopen("OgrenciDersKayit.txt", "r");
    int i=0;
    int flag = 0, count = 0;

    while (fgets(buf, 255, fpr) != NULL)
    {
        char *token;
        char ders_kodu_okunan[50], durum[50];
        int ogrenci_num;
    // ID
        token = strtok(buf, delimiter);
        *log_ID = atoi(token);
    // ders_kodu
        token = strtok(NULL, delimiter);
        strcpy(ders_kodu_okunan, token);
    // ogrenci_num
        token=strtok(NULL,delimiter);
        ogrenci_num = atoi(token);
    // tarih
        token = strtok(NULL, delimiter);
    // durum
        token = strtok(NULL, delimiter);
        token[strlen(token)-1] = '\0';
        strcpy(durum, token);

        if (!strcmp(ders_kodu_okunan, ders_kodu))
        {
            if (!strcmp(durum, "kayitli"))
            {
                if (flag == 0)
                    liste = realloc(liste, (count+1)*sizeof(int));
                else
                    flag --;
                liste[count] = ogrenci_num;
                count ++;
            }
            else if (!strcmp(durum, "silindi"))
            {
                remove_first(liste, &count, ogrenci_num);
                flag ++;
            }
        }
        i++;
    }
    int size = len(liste)-1;
    if (liste[0] != '\0' && size > 0)
        selection_sort(liste, size);
 	fclose(fpr);
}

Dersler* dersler_oku(Dersler* head_dersler, Ogrenciler* head_ogrenciler, char File_Name[50], char delimiter[2], int* log_ID)
{
    /*
    dersler dosyasi olacak:
    ders kodu, adı, toplam kredisi, kontenjanı bilgisi
    TEK YÖNLÜ LİNKLİ LİSTE ile ders koduna göre sıralı
        derse kayıtlı öğrencilerin numarası dinamik bir dizi ile öğrenci numarasına göre artan sırada saklanmalıdır
    */
    FILE *fp=fopen(File_Name,"r");
    Dersler* iter = (Dersler*) malloc(sizeof(Dersler));
    Dersler* prev = (Dersler*) malloc(sizeof(Dersler));
    iter = head_dersler;
    char buf[255];
    while (fgets(buf,255,fp) != NULL)
    {
        char *token;
    //ders_kodu
        token = strtok(buf, delimiter);
        strcpy(iter->ders_kodu, token);
    //ders_adi
        token = strtok(NULL, delimiter);
        strcpy(iter->ders_adi, token);
    //kredi
        token=strtok(NULL,delimiter);
        iter->kredi = atoi(token);
    //kontenjan
        token = strtok(NULL, delimiter);
        token[strlen(token)-1] = '\0';
        iter->kontenjan = atoi(token);

        iter->dersteki_nums = (int*) calloc(sizeof(int), 0);
        ogrenci_ders_kayit_tara(iter->ders_kodu, iter->dersteki_nums, ",\0", log_ID);
        prev = iter;
        iter->next = (Dersler*)malloc(sizeof(Dersler));
        iter = iter->next;
        //printf("%s,%s,%d,%d\n", new->ders_kodu, new->ders_adi, new->kredi, new->kontenjan);
    }
    prev->next = NULL;
 	fclose(fp);
    return head_dersler;
}

int len(int* Array)
{
    int count = 0;
    while (Array[count] != '\0')
    {
        count++;
    }
    return count+1;
}

void remove_first(int* Array, int* size, int value)
{
    int i = 0, item_index = 999999;
    while (Array[i] != '\0')
    {
        if (Array[i] == value)
        {
            item_index = i;
            break;
        }
        i++;
    }
    for ( i = item_index; i < *size-1; i++)
        Array[i] = Array[i+1];

    if (item_index != 999999)
    {
        Array[*size-1] = 0;
        *size -= 1;
    }
}

void dersler_yaz(Dersler* head, char File_Name[50])
{
    FILE *fp = fopen(File_Name, "w");
    Dersler* iter = (Dersler*) malloc(sizeof(Dersler));
    iter = head;
    while(iter != NULL)
    {
        fprintf(fp, "%s,%s,%d,%d\n", iter->ders_kodu, iter->ders_adi, iter->kredi, iter->kontenjan);
        iter = iter->next;
    }
    fclose(fp);
}

void ogrenciler_yaz(Ogrenciler* head, char File_Name[50])
{
    FILE *fp = fopen(File_Name, "w");
    Ogrenciler* iter = (Ogrenciler*) malloc(sizeof(Ogrenciler));
    iter = head;
    while(iter != NULL)
    {
        fprintf(fp, "%d,%s,%s,%d,%d\n", iter->ogrenci_numarasi, iter->ad, iter->soyad, iter->kredi_bilgisi, iter->ders_sayisi);
        iter = iter->next;
    }
    fclose(fp);
}

void ogrenciler_oku(Ogrenciler* head, char File_Name[50], char delimiter[2])
{
    /*
    Öğrenciler dosyasi olacak:
        öğrenci numarası, adı, soyadı, kaydolduğu toplam ders sayısı ve kaydolduğu toplam kredi bilgisi
        ÖğrenciListesi isimli ÇİFT YÖNLÜ LİNKLİ LİSTEDE öğrenci bilgilerini numaralarına göre artan düzende saklayınız.
    */
    FILE *fp=fopen(File_Name,"r");
    Ogrenciler* iter = (Ogrenciler*) malloc(sizeof(Ogrenciler));
    Ogrenciler* prev = (Ogrenciler*) malloc(sizeof(Ogrenciler));
    iter = head;
    char buf[255];

    while (fgets(buf,255,fp) != NULL)
    {
        char *token;
    // ogrenci_numarasi
        token = strtok(buf, delimiter);
        iter->ogrenci_numarasi = atoi(token);
    // ad
        token = strtok(NULL, delimiter);
        strcpy(iter->ad, token);
    // soyad
        token = strtok(NULL, delimiter);
        strcpy(iter->soyad, token);
    // kredi_bilgisi
        token = strtok(NULL, delimiter);
        iter->kredi_bilgisi = atoi(token);
    // ders_sayisi
        token=strtok(NULL,delimiter);
        token[strlen(token)-1] = '\0';
        iter->ders_sayisi = atoi(token);

        prev = iter;
        iter->next = (Ogrenciler*)malloc(sizeof(Ogrenciler));
        iter = iter->next;
        iter->prev = prev;
        //printf("%s,%s,%d,%d\n", new->ders_kodu, new->ders_adi, new->kredi, new->kontenjan);
    }
    prev->next = NULL;
 	fclose(fp);
}

// Ogrenciler linkli listemizi ekrana yazdiriyor.
void yazdir_ogrenciler(Ogrenciler* head)
{
    printf("\n\t\t************\n\t\t*Ogrenciler*\n\t\t************\n");
    while(head!=NULL)
    {
        printf("%d %s %s ders_sayisi : %d kredi_bilgisi : %d\n", head->ogrenci_numarasi, head->ad, head->soyad, head->ders_sayisi, head->kredi_bilgisi);
        head=head->next;
    }
    printf("\n");
}

int find(int* Array, int value)
{
    int i = 0, counter = 0;
    while (Array[i] != '\0' && counter == 0)
    {
        if (Array[i] == value)
            counter++;
        i++;
    }
    return counter;
}

int* remove_element(int* array, int sizeOfArray, int indexToRemove)
{
    int* temp = malloc((sizeOfArray - 1) * sizeof(int)); // allocate an array with a size 1 less than the current one

    if (indexToRemove != 0)
        memcpy(temp, array, indexToRemove * sizeof(int)); // copy everything BEFORE the index

    if (indexToRemove != (sizeOfArray - 1))
        memcpy(temp+indexToRemove, array+indexToRemove+1, (sizeOfArray - indexToRemove - 1) * sizeof(int)); // copy everything AFTER the index

    free (array);
    return temp;
}

void selection_sort(int* Array, int size)
{
    int i, j, min_id, temp;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < size-1; i++)
    {
        // Find the minimum element in unsorted array
        min_id = i;
        for (j = i+1; j < size; j++)
          if (Array[j] < Array[min_id])
            min_id = j;

        // Swap the found minimum element with the first elemen
        temp = Array[min_id];
        Array[min_id] = Array[i];
        Array[i] = temp;
    }
}

void output_yazilari_1()
{
    printf("\nMENU\n----------\n");
    printf("1-Dersleri ekranda goster\n");
    printf("2-Ogrencileri ekranda goster\n");
    printf("3-Ders ekle\n");
    printf("4-Ders sil\n");
    printf("5-Ogrenci ekle\n");
    printf("6-Ogrenci sil\n");
    printf("7-Kayitli ogrenciye ders ekle veya sil\n");
    printf("8-DERSKODU.txt olustur\n");
    printf("9-ÖĞRENCİNO_DERSPROGRAMI.txt olustur\n");
    printf("10-Cikis\n");
    printf("Isleminizi seciniz : ");
}

void output_yazilari_2()
{
    printf("\nYanlis giris yaptiniz !!\nTekrar deneyiniz.\n");
}
