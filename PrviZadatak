#include <stdio.h>
#include <stdlib.h>
#define MSIZE (128)
#define MLINE (1024)

typedef struct _student{
    char ime [MSIZE];
    char prezime [MSIZE];
    double bodovi;
}student;

int citanjeDatoteke(char*);
student* dinamickaAlokacija(int, char*);
void bodovi(int, student*);

int main()
{
    int i;
    int brst = 0;
    char nazivDat[MSIZE];
    student* students;

    printf("unesite ime datoteke \n");
    scanf(" %s" , nazivDat);

    brst = citanjeDatoteke(nazivDat);
    printf("broj studenata u datoteci je %d \n" ,brst);

    students = dinamickaAlokacija(brst, nazivDat);

    printf("Svi studenti su: \n");
    for(i=0;i<brst;i++)
    {
        printf("%s\t%s\t%lf\n" , students[i].ime, students[i].prezime,students[i].bodovi);
    }

    bodovi(brst, students);


    return 0;
}

int citanjeDatoteke (char* nazivDat)
{
    FILE* dat = NULL;
    int n = 0;
    char buffer [MLINE] = {0};

    dat = fopen(nazivDat , "r");
    
    if(!dat)
    {
        printf("greska \n");
        return -1;
    }

    while(!feof(dat))
    {
        fgets(buffer, MLINE, dat);
        n++;
    }

    fclose(dat);

    return n;
}

student* dinamickaAlokacija(int brst, char* nazDat)
{
    int br = 0;
    FILE* dat = NULL;
    student* studenti = NULL;

    studenti = (student*)malloc(brst * sizeof(student));
    dat = fopen(nazDat, "r");

    while(!feof(dat))
    {
        fscanf(dat, " %s %s %lf" , studenti[br].ime, studenti[br].prezime, &studenti[br].bodovi);
        br++;
    }

    fclose(dat);

    return studenti;

}

void bodovi(int brst, student* studenti)
{
    int i = 0;
    double apsBod = 0;
    double relBod[MSIZE] = {0};
    double max_br_bod = 50;

    for(i=0;i<brst;i++)
    {
        printf("Apsolutni broj bodova studenta %s\t%s je: %lf\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi);
    }

    for(i=0;i<brst;i++)
    {
        relBod[i] = studenti[i].bodovi/max_br_bod*100;
    }

    printf("\n\n");

    for(i=0;i<brst;i++)
    {
        printf("relativni broj bodova studenta %s\t%s je %lf\n" ,studenti[i].ime, studenti[i].prezime, relBod[i]);
    }

}
