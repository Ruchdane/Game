#include "stdio.h"
#include "stdlib.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "structure.h"

Button *CreateButton(int value,int  padinx,int  padiny,int marginx,int marginy,int cadrex,int cadrey,char *message)
{
	Button *button=NULL;
	button=malloc(sizeof(Button));
	
	if(button==NULL)
		{
			printf("zqskfjbgdxk,sdl");
			return NULL;
		}
	button->value=value;
	button->padin.x=padinx;
	button->padin.y=padiny;
	button->margin.x=marginx;
	button->margin.y=marginy;
	button->cadre.x=cadrex;
	button->cadre.y=cadrey;
	button->cadre.w=0;
	button->cadre.h=0;
	button->cadre.x=cadrex;
	button->message=message;
}


void Pafficher(Pile*pile)
{
	Element* actuel;
	char c[][6]={"right","left","down","up"};
	if(pile==NULL)
		exit(EXIT_FAILURE);
	actuel=pile->premier;
	while(actuel!=NULL)
	{
		printf(" _____________\n");
		
		printf("|     %s      |\n",c[actuel->nombre-1073741903]);
		printf(" _____________\n");
		actuel=actuel->suivant;
	}
	printf("\n et voici l inverse");
	
	
}
Pile* Pinverse(Pile* pile)
{
	Pile *tmp=Pinitialiser();
	while(pile->premier!=NULL)
		empiler(tmp,depiler(pile));
	return tmp;
	
	
}

Pile* Pinitialiser()
{
	Pile *pile = malloc(sizeof(*pile));
	if (pile!=NULL)
	{
		pile->premier = NULL;
		return pile; 
	}
	else
	exit(EXIT_FAILURE);
}
void empiler(Pile*pile,int Nombre)
{
	Element* nouveau=malloc(sizeof(*nouveau));
	if(pile==NULL||nouveau==NULL)
		exit(EXIT_FAILURE);
	
	nouveau->nombre=Nombre;
	nouveau->suivant=pile->premier;
	pile->premier=nouveau;// le sommet de la pile
}
int depiler(Pile* pile) //retourne l’élément dépilé
{
	int nombreDepile=0;
	Element* elementDepile;
	if(pile==NULL)
		exit(EXIT_FAILURE);

	elementDepile=pile->premier;
	if(pile->premier!=NULL) //si la pile n’est pas vide
	{
		nombreDepile=elementDepile->nombre; //contient la valeur du nombre à dépiler
		pile->premier=elementDepile->suivant;
		free(elementDepile);
	}
	return nombreDepile;
}

int Ptaille(Pile* pile)
{
	int len;
	Element *elt;
	if(pile==NULL)
		exit(EXIT_FAILURE);
	for(elt=pile->premier,len=0;elt!=NULL;elt=elt->suivant,len++);
	return len;
}

void Pfree(Pile *pile)
{
	Element *elt;
	if(pile==NULL)
		return;
	
	for(elt=pile->premier;elt!=NULL;depiler(pile),elt=elt->suivant);
}

int **Minitialiser(int size,int seze)
{
    int i;
    int **matrice;
    matrice=calloc(size,sizeof(int*));
    if(matrice==NULL)
    {
        printf("matrice non alloue");
        exit(EXIT_FAILURE);
    }

    for(i=0;i!=size;i++)
    {
        matrice[i]=calloc(seze,sizeof(int));
        if(matrice[i]==NULL)
        {
            printf("matrice non alloue");
            exit(EXIT_FAILURE);
        }
    }
	return matrice;

}
void Mfree(int **matrice,int seze)
{
	int i;
	for(i=0;i!=seze;i++)
		free(matrice[i]);
	free(matrice);
}