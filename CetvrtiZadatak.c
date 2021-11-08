#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MLINE 1024

struct polinom;
typedef struct polinom* Pozicija;
typedef struct polinom {
    int k;
    int ex;
    Pozicija next;
}polinom;

int citanjeIzDatoteke(Pozicija head1,Pozicija head2, char* imeDat);
Pozicija stvoriPolinom(int k, int exp);
int sortiraniUnos(Pozicija head, int koef, int exp);
int ispisListe(Pozicija head);
int brisiEl(Pozicija p);
int brisiSve(Pozicija p);
int zbroj(Pozicija head1, Pozicija head2, Pozicija suma);
int produkt(Pozicija head1, Pozicija head2, Pozicija produkt);

int main()
{
    polinom Head1 = {.next = NULL, .k = 0, .ex = 0};
    polinom Head2 = {.next = NULL, .k = 0, .ex = 0};
    polinom suma = {.next = NULL, .k = 0, .ex = 0};
    polinom produkt1 = {.next = NULL, .k = 0, .ex = 0};
    char imeDat[MLINE] = { 0 };

    printf("unesite ime datoteke iz koje cemo citati polinome \n");
    scanf(" %s", imeDat);
    citanjeIzDatoteke(&Head1, &Head2, imeDat);
    printf("ovo je prvi polinom \n");
    ispisListe(&Head1);
    printf("\novo je drugi polinom \n");
    ispisListe(&Head2);
    printf("\n");
    zbroj(Head1.next, Head2.next, &suma);
    printf("suma dvaju polinoma \n");
    ispisListe(&suma);
    printf("\n");
    produkt(Head1.next, Head2.next, &produkt1);
    printf("produkt dvaju polinoma \n");
    ispisListe(&produkt1);
    printf("\n");

    brisiSve(&Head1);
    brisiSve(&Head2);
    brisiSve(&suma);
    brisiSve(&produkt1);

    return 0;
}

int citanjeIzDatoteke(Pozicija head1,Pozicija head2 ,char* imeDat)
{
    FILE* fp;
    int koef = 0;
    int pot = 0;
    int n = 0;
    char* pok = NULL;
    char buffer[MLINE] = { 0 };

    fp = fopen(imeDat, "r");

    if(!fp)
    {
        perror("greska pri otvaranju datoteke \n");

        return -1;
    }

        fgets(buffer, MLINE, fp);
        pok = buffer;
        while (strlen(pok) > 0)
        {
            sscanf(pok, " %d %d %n", &koef, &pot, &n);
            sortiraniUnos(head1, koef, pot);
            pok += n;
        }

        fgets(buffer, MLINE, fp);
        pok = buffer;
        while (strlen(pok) > 0)
        {
            sscanf(pok, " %d %d %n", &koef, &pot, &n);
            sortiraniUnos(head2, koef, pot);
            pok += n;
        }

    return 0;
}

Pozicija stvoriPolinom(int koef, int exp)
{
    Pozicija q = NULL;
    
    q = (Pozicija)malloc(sizeof(polinom));

    if (!q)
    {
        perror("Nemoze alocirati memoriju");
    }

    q->k = koef;
    q->ex = exp;
    q->next = NULL;

    return q;
}

int sortiraniUnos(Pozicija head, int koef, int exp)
{
    Pozicija q = NULL;
    Pozicija h = head;
    Pozicija prev = head;
    
    q = stvoriPolinom(koef, exp);

    if (h->next == NULL)
    {
        q->next = h->next;
        h ->next = q;
    }

    else
    {
        h = h->next;

        while (h->next != NULL && h->ex > exp)
        {
            prev = h;
            h = h->next;
        }

        if (h->ex < q->ex)
        {
            q->next = h;
            prev->next = q;
        }

        else if(h->ex == q->ex)
        { 
            h->k = h->k + q->k;
            if(h->k == 0)
            {
                brisiEl(prev);
            }
        }

        else 
        {
            q->next = h->next;
            h->next = q;
        }
    }

    return 0;
}

int ispisListe(Pozicija head)
{
    Pozicija prvi = head;
    prvi = prvi->next;

    while(prvi != NULL)
    {
        printf("%dx^%d\t", prvi->k, prvi->ex);
        prvi = prvi->next;
    }
    return 0;
}

int brisiEl(Pozicija p)

{
    Pozicija temp = NULL;

    temp = p->next;

    p->next = temp->next;
    free(temp);

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

int zbroj(Pozicija head1, Pozicija head2, Pozicija suma)
{
    Pozicija temp = NULL;

    while(head1 != NULL && head2 != NULL)
    {
        if(head1->ex == head2->ex)
        {
            sortiraniUnos(suma, head1->k + head2->k, head1->ex);
            head1 = head1->next;
            head2 = head2->next;
        }
        else if(head1->ex > head2 ->ex)
        {
            sortiraniUnos(suma, head1->k, head1->ex);
            head1 = head1->next;
        }
        else
        {
            sortiraniUnos(suma, head2->k, head2->ex);
            head2 = head2 -> next;
        }
    }
    if(head1 != NULL)
    {
        temp = head1;
    }
    else
    {
        temp = head2;
    }
    while(temp != NULL)
    {
        sortiraniUnos(suma, temp->k, temp->ex);
        temp = temp->next;
    }
    return 0;
}

int produkt(Pozicija head1, Pozicija head2, Pozicija produkt)
{
    Pozicija poc = head2;

    while(head1 != NULL)
    {
        head2 = poc;
        while(head2 != NULL)
        {
            sortiraniUnos(produkt, head1->k * head2->k, head1->ex + head2->ex);
            head2 = head2->next;
        }
        head1 = head1->next;
    }
    return 0;
}
