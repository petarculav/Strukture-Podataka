#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MLINE 1024

struct stog;
typedef struct stog* Pozicija;
typedef struct stog
{
    double broj;
    Pozicija next;
}stog;

Pozicija stvoriEl(double br);
int unos(Pozicija head, Pozicija noviEl);
int Push(Pozicija head, double br);
int brisiPosli(Pozicija poz);
int Pop(double* rezultat, Pozicija head);
int operacija(Pozicija head, char oper);
int postfix(double *rezultat, char* imeDat); //za citanje postfix izraza iz datoteke
int brisanjeSvega(Pozicija head);

int main(int argc, char* argv[])
{

    double rezultat = 0;

    if(argc == 1)
    {
        if(postfix(&rezultat, "postfix.txt") == EXIT_SUCCESS)
        {
            printf("rezultat operacija je: %lf \n", rezultat);
        }
    }
    else if (postfix(&rezultat, argv[1]) == EXIT_SUCCESS)
    {
        printf("rezultat operacija je: %lf \n" , rezultat);
    }
    
    return EXIT_SUCCESS;
}

Pozicija stvoriEl(double br)
{
    Pozicija q = NULL;

    q = (Pozicija)malloc(sizeof(stog));

    if(!q)
    {
        perror("greška u inicijalizaciji \n");

        return NULL;
    }
    
    q->broj = br;
    q->next = NULL;

    return q;
}

int unos(Pozicija head, Pozicija noviEl)
{
    noviEl->next = head->next;
    head->next = noviEl;

    return EXIT_SUCCESS;
}

int Push(Pozicija head, double br)
{
    Pozicija noviEl = NULL;

    noviEl = stvoriEl(br);

    if (!noviEl)
	{
		return -1;
	}

    unos(head, noviEl);

    return EXIT_SUCCESS;
}

int brisiPosli(Pozicija poz)
{
    Pozicija temp = NULL;

    temp = poz->next;

    if(!temp)
    {
        return EXIT_SUCCESS;
    }

    poz->next = temp->next;
    free(temp);

    return EXIT_SUCCESS;
}

int Pop(double* rezultat, Pozicija head)
{
    Pozicija prvi = NULL;

    prvi = head->next;

    if(!prvi)
    {
        perror("nevalja postfix \n");
        return -1;
    }
    
    *rezultat = prvi->broj;
    brisiPosli(head);

    return EXIT_SUCCESS;
}

int operacija(Pozicija head, char oper)
{
    double operand1 = 0;
    double operand2 = 0;
    double rezultat = 0;
    int stanje1 = EXIT_SUCCESS;
    int stanje2 = EXIT_SUCCESS;

    stanje2 = Pop(&operand2, head);
    if (stanje2 != EXIT_SUCCESS)
	{
		return -1;
	}

    stanje1 = Pop(&operand1, head);
    if (stanje1 != EXIT_SUCCESS)
	{
		return -2;
	}

    switch (oper)
	{
	case '+':
		rezultat = operand1 + operand2;
		break;
	case '-':
		rezultat = operand1 - operand2;
		break;
	case '*':
		rezultat = operand1 * operand2;
		break;
	case '/':
		if (operand2 == 0)
		{
			perror("nemoze se dijeliti sa 0\n");
			return -3;
		}
		rezultat = operand1 / operand2;
		break;
	default:
		return -4;
	}

    return Push(head, rezultat);
}

int postfix(double *rezultat, char* imeDat)
{
    stog head = {.next = NULL, .broj = 0};
    FILE* fp = NULL;
    int duzinaDat = 0;
    char* buffer = NULL;
    char* noviBuffer = NULL;
    int broj_bajtova = 0;
    double br = 0;
    int status = 0;
    char oper = 0;

    fp = fopen(imeDat, "rb");

    if(!fp)
    {
        perror("datoteka se nije otvorila \n");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    duzinaDat = ftell(fp);

    buffer = (char*)calloc(duzinaDat +1, sizeof(char));
    if(!buffer)
    {
        perror("greska u alociranju \n");

        return -2;
    }

    rewind(fp);
    fread(buffer, sizeof(char),duzinaDat, fp);
    printf("|%s|\n", buffer);
    fclose(fp);

    noviBuffer = buffer;

    while(strlen(noviBuffer) > 0)
    {
        status = sscanf(noviBuffer, " %lf, %n", &br, &broj_bajtova);
        if(status == 1)
        {
            status = Push(&head, br);
            if(status != EXIT_SUCCESS)
            {
                free(buffer);
                brisanjeSvega(&head);
                return -3;
            }
            noviBuffer += broj_bajtova;
        }
        else
        {
            sscanf(noviBuffer, " %c, %n" , &oper, &broj_bajtova);
            status = operacija(&head, oper);
            if(status != EXIT_SUCCESS)
            {
                free(buffer);
                brisanjeSvega(&head);
                return -4;
            }
            noviBuffer += broj_bajtova;
        }
    }
    free(buffer);

    status = Pop(rezultat, &head);
    if(status != EXIT_SUCCESS)
    {
        brisanjeSvega(&head);
        return -5;
    }

    if(head.next)
    {
        printf("nevalja postfix izraz \n");
        brisanjeSvega(&head);
        return -6;
    }
    return EXIT_SUCCESS;
}

int brisanjeSvega(Pozicija Head)
{
    while(Head->next)
    {
        brisiPosli(Head);
    }
    return 0;
}

int ispisStoga(Pozicija head)
{
    while(head != NULL)
    {
        printf("%lf \n" , head->broj);
        head = head->next;
    }
    return EXIT_SUCCESS;
}
