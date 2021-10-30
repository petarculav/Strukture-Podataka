#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define Msize (50)

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

int main()
{
    int i = 0;
    char prezime[Msize] = {0};
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

    printf("unesite prezime osobe koju zelite pronaci \n");
    scanf(" %s" , prezime);

    p = trazi(zaHead.next, prezime);
    printf("%s\t%s\t%d\n", p->ime, p->prezime, p->godina_rodenja);
    
    printf("unesite prezime osobe koju zelite IZBRISATI \n");
    scanf(" %s" , prezime);

    p = trazi(zaHead.next, prezime);
    brisi(&zaHead, p);

    ispisListe(zaHead.next);

    return 0;
}


int unosNaPocetak(Pozicija p, char* ime, char* prezime, int godina_rodenja)
{
    Pozicija NovaOsoba = NULL;

    NovaOsoba = (Pozicija)malloc(sizeof(NovaOsoba));

        strcpy(NovaOsoba->ime, ime);
        strcpy(NovaOsoba->prezime, prezime);
        NovaOsoba->godina_rodenja = godina_rodenja;

    NovaOsoba->next = p->next;
    p->next = NovaOsoba;

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

    NovaOsoba = (Pozicija)malloc(sizeof(Pozicija));

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
