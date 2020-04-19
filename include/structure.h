#ifndef RUCHDANESTRUCT
#define RUCHDANESTRUCT

typedef struct{
	int x;
	int y;
}Descartes;

typedef struct{
	int value;
	Descartes padin;
	Descartes margin;
	SDL_Rect cadre;
	char *message;
}Button;

typedef struct 
{
	int id;
	int np;//nombre de perle visible dans le niveau
	Descartes resolution;
	int **t;
}Level;

typedef struct Element
{
	int nombre;
	struct Element* suivant;
}Element;

typedef struct 
{
	Element* premier;
}Pile;

Button *CreateButton(int value,int  padinx,int  padiny,int marginx,int marginy,int cadrex,int cadrey,char *message);

int Linitialiser (Level *niveau,int j);
void Lwrite(Level *niveau);
void Lread(Level *niveau,int j);
Pile* Pinitialiser();
void empiler(Pile*pile,int Nombre);
int depiler(Pile* pile);
int Ptaille(Pile* pile);
void Pfree(Pile *pile);
void Pafficher(Pile* pile);
Pile* Pinverse(Pile* pile);

int **Minitialiser(int size,int seze);
void Mfree(int ** ,int seze);
#endif