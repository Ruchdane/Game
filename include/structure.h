#ifndef RUCHDANESTRUCT
#define RUCHDANESTRUCT
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

typedef struct
{
	int x;
	int y;
} Vector2;

typedef struct
{
	int value;
	Vector2 padin;
	Vector2 margin;
	SDL_Rect cadre;
	char *message;
	SDL_Color test;
	SDL_Color couleur;
	SDL_Color ombre;
} Button;

typedef struct
{
	int id;
	int np; //nombre de perle visible dans le niveau
	Vector2 resolution;
	int **t;
} Level;

typedef struct Element
{
	int nombre;
	struct Element *suivant;
} Element;

typedef struct
{
	Element *premier;
} Pile;

Button *CreateButton(int value, int padinx, int padiny, int marginx, int marginy, int cadrex, int cadrey, char *message);

int Linitialiser(Level *niveau, int j);
void Lwrite(Level *niveau);
void Lread(Level *niveau, int j);
Pile *Pinitialiser();
void empiler(Pile *pile, int Nombre);
int depiler(Pile *pile);
int Ptaille(Pile *pile);
void Pfree(Pile *pile);
void Pafficher(Pile *pile);
Pile *Pinverse(Pile *pile);

int **Minitialiser(int size, int seze);
void Mfree(int **, int seze);
SDL_Color RGBToColor(int r, int g, int b, int a);
#endif