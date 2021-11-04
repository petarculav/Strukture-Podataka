#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define Msize (50)
#define MLINE (1024)

struct _osoba;
typedef struct _osoba* Pozicija;
typedef struct _osoba
{
    char ime [Msize];
    char prezime [Msize];
    int godina_rodenja;
    Pozicija next;
}osoba;

int unosNaPocetak(Pozicija p, char* ime, char* prezime, int godina_rodenja);
int ispisListe(Pozicija prvi);
int unosNaKraj(Pozicija p, char* ime, char* prezime, int godina_rodenja);
Pozicija trazi(Pozicija p, char* prezime);
int brisi(Pozicija p, Pozicija q);
int unosIzaOdredenogEl(Pozicija p, char* ime, char* prezime, int godina_rodenja, char* prezimeIza);
int unosIspredOdredenogEl(Pozicija p, char* ime, char* prezime, int godina_rodenja, char* prezimeIspri);
int sortiraj(Pozicija p);
int upisUDatoteku(Pozicija p, char* imeDat);
int citanjeIzDatoteke(Pozicija head, char* imeDat);
int brisiSve(Pozicija p);
Pozicija StvoriOsobu(char* ime, char* prezime, int godina_rodenja);

int main()
{
    int i = 0;
    char prezime[Msize] = {0};
    char imeDatoteke[Msize] = {0};
    osoba zaHead = {.next = NULL, .ime = {0}, .prezime = {0}, .godina_rodenja = 0};
    osoba osoba = {.next = NULL, .ime = {0}, .prezime = {0}, .godina_rodenja = 0};
    Pozicija p = NULL;

    for(i=0;i<3;i++)
    {
        printf("unesite ime osobe \n");
        scanf(" %s" , osoba.ime);
        printf("unesite prezime osobe \n");
        scanf(" %s" , osoba.prezime);
        printf("unesite godinu rodenja osobe \n");
        scanf("%d" , &osoba.godina_rodenja);

        unosNaPocetak(&zaHead, osoba.ime, osoba.prezime, osoba.godina_rodenja);
    }
    printf("\n");

    ispisListe(zaHead.next);

    printf("unesite podatke za osobu koju zelite unijeti NA KRAJ \n");

        printf("unesite ime osobe \n");
        scanf(" %s" , osoba.ime);
        printf("unesite prezime osobe \n");
        scanf(" %s" , osoba.prezime);
        printf("unesite godinu rodenja osobe \n");
        scanf("%d" , &osoba.godina_rodenja);

        unosNaKraj(&zaHead, osoba.ime, osoba.prezime, osoba.godina_rodenja);
        ispisListe(zaHead.next);

        printf("\n");

    printf("unesite prezime osobe koju zelite pronaci \n");
    scanf(" %s" , prezime);

    p = trazi(zaHead.next, prezime);
    printf("%s\t%s\t%d\n", p->ime, p->prezime, p->godina_rodenja);
    printf("\n");
    
    printf("unesite prezime osobe koju zelite IZBRISATI \n\n");
    scanf(" %s" , prezime);

    p = trazi(zaHead.next, prezime);
    brisi(&zaHead, p);

    ispisListe(zaHead.next);

    printf("unesite prezime osobe iza koje zelite unijeti novu osobu\n\n");
    scanf(" %s" , prezime);

    printf("unesite podatke za osobu koju zelite unijeti IZA ODREDENE OSOBE \n\n");
        printf("unesite ime osobe \n");
        scanf(" %s" , osoba.ime);
        printf("unesite prezime osobe \n");
        scanf(" %s" , osoba.prezime);
        printf("unesite godinu rodenja osobe \n");
        scanf("%d" , &osoba.godina_rodenja);
    
    unosIzaOdredenogEl(&zaHead, osoba.ime, osoba.prezime, osoba.godina_rodenja, prezime);
    
    ispisListe(zaHead.next);

    printf("unesite prezime osobe ispred koje zelite unijeti novu osobu \n\n");
    scanf(" %s" , prezime);

    printf("unesite podatke za osobu koju zelite unijeti ISPRED ODREDENE OSOBE \n\n");
        printf("unesite ime osobe \n");
        scanf(" %s" , osoba.ime);
        printf("unesite prezime osobe \n");
        scanf(" %s" , osoba.prezime);
        printf("unesite godinu rodenja osobe \n");
        scanf("%d" , &osoba.godina_rodenja);
    
    unosIspredOdredenogEl(&zaHead, osoba.ime, osoba.prezime, osoba.godina_rodenja, prezime);

    ispisListe(zaHead.next);
    printf("\n\n");

    sortiraj(&zaHead);
    ispisListe(zaHead.next);
    printf("\n\n");

    printf("printanje liste u datoteku \n");
    printf("unesite ime datoteke \n");
    scanf(" %s" , imeDatoteke);
    upisUDatoteku(&zaHead, imeDatoteke);
    puts("");

    brisiSve(&zaHead);
    printf("citanje liste iz datoteke %s\n", imeDatoteke);
    citanjeIzDatoteke(&zaHead, imeDatoteke);
    ispisListe(zaHead.next);

    return 0;
}

int unosNaPocetak(Pozicija p, char* ime, char* prezime, int godina_rodenja)
{
    Pozicija NovaOsoba = NULL;

    NovaOsoba = (Pozicija)malloc(sizeof(osoba));

        strcpy(NovaOsoba->ime, ime);
        strcpy(NovaOsoba->prezime, prezime);
        NovaOsoba->godina_rodenja = godina_rodenja;

    NovaOsoba->next = p->next;
    p->next = NovaOsoba;

    return 0;
}

int brisiSve(Pozicija p)
{
    Pozicija temp = NULL;
    
    while(p->next != NULL)
    {
        temp = p->next;
        p->next = temp->next;
        free(temp);
    }
    return 0;
}

int ispisListe(Pozicija prvi)
{
    Pozicija p = prvi;
    while(p != NULL)
    {
        printf("%s\t%s\t%d\n" , p->ime, p->prezime, p->godina_rodenja);
        p = p->next;
    }
    return 0;
}

int unosNaKraj(Pozicija p, char* ime, char* prezime, int godina_rodenja)
{
    Pozicija NovaOsoba = NULL;

    NovaOsoba = (Pozicija)malloc(sizeof(osoba));

    strcpy(NovaOsoba->ime, ime);
    strcpy(NovaOsoba->prezime, prezime);
    NovaOsoba->godina_rodenja = godina_rodenja;

    while(p->next != NULL)
        p = p->next;
    
    NovaOsoba->next = p-> next;
    p->next = NovaOsoba;

    return 0;
}

Pozicija trazi(Pozicija p, char* prezime)
{
    Pozicija osoba = p;

    while(osoba != NULL && strcmp(osoba->prezime, prezime) != 0)
    {
        osoba = osoba->next;
    }
    return osoba;
}

int brisi(Pozicija p, Pozicija q)
{
    while(p->next != q)
        p = p->next;

    p->next = q->next;
    free(q);

    return 0;
}

int unosIzaOdredenogEl(Pozicija p, char* ime, char* prezime, int godina_rodenja, char* prezimeIza)
{

    Pozicija NovaOsoba = NULL;
    p = p->next;
    while(p != NULL && strcmp(p->prezime, prezimeIza) != 0)
    {
        p = p->next;
    }

    if(p != NULL)
    {
        NovaOsoba = (Pozicija)malloc(sizeof(osoba));
        strcpy(NovaOsoba->ime, ime);
        strcpy(NovaOsoba->prezime, prezime);
        NovaOsoba->godina_rodenja = godina_rodenja;

        NovaOsoba->next = p->next;
        p->next = NovaOsoba;
    }
    else
        printf("Greška! Element ne postoji! \n");

    return 0;
}

int unosIspredOdredenogEl(Pozicija p, char* ime, char* prezime, int godina_rodenja, char* prezimeIspri)
{
    Pozicija NovaOsoba = NULL;

    while(p->next != NULL && strcmp(p->next->prezime, prezimeIspri) != 0)
    {
        p = p->next;
    }

    if(p->next != NULL)
    {
        NovaOsoba = (Pozicija)malloc(sizeof(osoba));
        strcpy(NovaOsoba->ime, ime);
        strcpy(NovaOsoba->prezime, prezime);
        NovaOsoba->godina_rodenja = godina_rodenja;

        NovaOsoba->next = p->next;
        p->next = NovaOsoba;
    }
    else
        printf("Greška! Element ne postoji! \n");
    
    return 0;
}

int sortiraj(Pozicija p)
{
    Pozicija temp = NULL, q = NULL, pretq = NULL, kraj = NULL;

    while(p->next != kraj)
    {
        pretq = p;
        q = p->next;

        while(q->next != kraj)
        {
            if(strcmp(q->prezime, q->next->prezime) > 0)
            {
                temp = q->next;
                pretq->next = temp;
                q->next = temp->next;
                temp->next = q;

                q = temp;
            }
            pretq = q;
            q = q->next;
        }
        kraj = q;
    }

    return 0;
}

int upisUDatoteku(Pozicija p, char* imeDat)
{
    FILE* fp;

    fp = fopen(imeDat , "w");

    p = p->next;

    while(p != NULL)
    {
        fprintf(fp, " \n%s\t%s\t%d" , p->ime, p->prezime, p->godina_rodenja);
        p = p->next;
    }

    fclose(fp);

    return 0;
}

Pozicija StvoriOsobu(char* ime, char* prezime, int godina_rodenja)
{
    Pozicija NovaOsoba = NULL;

    NovaOsoba = (Pozicija)malloc(sizeof(osoba));

    if(NovaOsoba == NULL)
    {
        perror("nije uspilo alocirat \n");

        return NULL;
    }

        strcpy(NovaOsoba->ime, ime);
        strcpy(NovaOsoba->prezime, prezime);
        NovaOsoba->godina_rodenja = godina_rodenja;

        return NovaOsoba;
}

int citanjeIzDatoteke(Pozicija p, char* imeDatoteke)
{
    FILE* fp = NULL;
    Pozicija head = p;
    char buffer[MLINE] = {0};
    char name[MLINE] = {0};
    char surname[MLINE] = {0};
    int birthyear = 0;

    fp = fopen(imeDatoteke, "r");

    if(fp == NULL)
    {
        printf("datoteka se nije otvorila \n");

        return -1;
    }

    while(!feof(fp))
    {
        fgets(buffer,MLINE,fp);
        if(sscanf(buffer," %s %s %d", name, surname, &birthyear) == 3)
        {
            Pozicija NewEl = StvoriOsobu(name, surname, birthyear);

            if(NewEl == NULL)
            {
                return -2;
            }
    
            NewEl->next = p-> next;
            p->next = NewEl;
            p = p->next;
        }
    }
    fclose(fp);

    return 0;
}