#include "structure.h"

Button *CreateButton(int value, int padinx, int padiny, int marginx, int marginy, int cadrex, int cadrey, char *message)
{
	Button *button = malloc(sizeof(Button));

	if (button == NULL)
	{
		printf("Button non alloue");
		return NULL;
	}
	button->value = value;

	button->padin.x = padinx;
	button->padin.y = padiny;

	button->margin.x = marginx;
	button->margin.y = marginy;

	button->cadre.x = cadrex;
	button->cadre.y = cadrey;
	button->cadre.w = 0;
	button->cadre.h = 0;

	button->message = message;

	button->test = RGBToColor(50, 0, 225, 225);
	button->ombre = RGBToColor(0, 225, 50, 225);
	button->couleur = RGBToColor(225, 50, 0, 225);
	return button;
}

SDL_Color RGBToColor(int r, int g, int b, int a)
{
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return color;
}

void Pafficher(Pile *pile)
{
	Element *actuel;
	char c[][6] = {"right", "left", "down", "up"};
	if (pile == NULL)
		exit(EXIT_FAILURE);
	actuel = pile->premier;
	while (actuel != NULL)
		actuel = actuel->suivant;
}
Pile *Pinverse(Pile *pile)
{
	Pile *tmp = Pinitialiser();
	while (pile->premier != NULL)
		empiler(tmp, depiler(pile));
	return tmp;
}

int Linitialiser(Level *niveau, int j)
{
	char c;
	int s = 0, s1, s2, s3, *nivo = NULL;
	FILE *niveaux = NULL;

	niveau->id = j;
	/*Bon les commentaire c'est pas mon fort
	donc je charge les nombre ecrit sur TAILLE bit 
	je les charges dans TAILLE tableau chaque nombre
	representes TAILLE cases sur la s1-iéme ligne
	le remplisage bon 
	0=vide;
	1=mur;
	2=perle verte;
	3=boite;
	4=2+3;
	5=mario
	*/

	if (j > 0) /*j represente le niveau*/
	{
		niveaux = fopen("./niveaux/niveau", "r");

		for (j--; j; j--)
		{
			c = fgetc(niveaux);
			while (c != '\n' && feof(niveaux) == 0)
				c = fgetc(niveaux);
		} /*positioner le curseur au niveau de la line j*/
	}

	else
	{
		niveaux = fopen("./niveaux/perso", "r");
	}

	fscanf(niveaux, "(%d,%d),", &niveau->resolution.x, &niveau->resolution.y);
	niveau->t = Minitialiser(niveau->resolution.x, niveau->resolution.y);
	fscanf(niveaux, "%d,", &niveau->np); /*Le nombre de perle qu'il y a*/
	while (nivo == NULL)
		nivo = malloc(niveau->resolution.x * sizeof(int));

	for (s1 = 0; s1 != niveau->resolution.x; s1++)
		fscanf(niveaux, "%d,", &nivo[s1]);

	for (int i = 0; i != niveau->np; i++)
	{
		fscanf(niveaux, "(%d,%d),", &s1, &s2); /*les positions des perles vertes*/
		niveau->t[s1][s2] = 2;
	}

	for (int i = 0; i != niveau->np; i++)
	{
		fscanf(niveaux, "(%d,%d),", &s1, &s2); /*les positions des boites*/
		if (niveau->t[s1][s2] == 2)
		{
			niveau->t[s1][s2] = 4;
			niveau->np--; /*pour n'avoir que les perles visibles*/
			i--;
		}
		else
			niveau->t[s1][s2] = 3;
	}

	fscanf(niveaux, "(%d,%d),", &s1, &s2);
	niveau->t[s1][s2] = 5;

	for (s1 = 0; s1 != niveau->resolution.x; s1++)
		for (s = 1 << niveau->resolution.y - 1, s2 = 0; s2 != niveau->resolution.y; s /= 2, s2++)
			if (s & nivo[s1])
				niveau->t[s1][s2] = 1; //je de dechifre les valeur ecrites sur talle bit

	fclose(niveaux);
	return 1;
}
Pile *Pinitialiser()
{
	Pile *pile = malloc(sizeof(*pile));
	if (pile != NULL)
	{
		pile->premier = NULL;
		return pile;
	}
	else
		exit(EXIT_FAILURE);
}
void empiler(Pile *pile, int Nombre)
{
	Element *nouveau = malloc(sizeof(*nouveau));
	if (pile == NULL || nouveau == NULL)
		exit(EXIT_FAILURE);

	nouveau->nombre = Nombre;
	nouveau->suivant = pile->premier;
	pile->premier = nouveau; // le sommet de la pile
}
int depiler(Pile *pile) //retourne l’élément dépilé
{
	int nombreDepile = 0;
	Element *elementDepile;
	if (pile == NULL)
		exit(EXIT_FAILURE);

	elementDepile = pile->premier;
	if (pile->premier != NULL) //si la pile n’est pas vide
	{
		nombreDepile = elementDepile->nombre; //contient la valeur du nombre à dépiler
		pile->premier = elementDepile->suivant;
		free(elementDepile);
	}
	return nombreDepile;
}

int Ptaille(Pile *pile)
{
	int len;
	Element *elt;
	if (pile == NULL)
		exit(EXIT_FAILURE);
	for (elt = pile->premier, len = 0; elt != NULL; elt = elt->suivant, len++)
		;
	return len;
}

void Pfree(Pile *pile)
{
	Element *elt;
	if (pile == NULL)
		return;

	for (; pile->premier != NULL;)
		depiler(pile);
	free(pile);
}

int **Minitialiser(int size, int seze)
{
	int i;
	int **matrice;
	matrice = calloc(size, sizeof(int *));
	if (matrice == NULL)
	{
		//("matrice non alloue");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i != size; i++)
	{
		matrice[i] = calloc(seze, sizeof(int));
		if (matrice[i] == NULL)
		{
			//("matrice non alloue");
			exit(EXIT_FAILURE);
		}
	}
	return matrice;
}
void Mfree(int **matrice, int seze)
{
	int i;
	if (matrice != NULL)
	{
		for (i = 0; i != seze; i++)
			free(matrice[i]);
		free(matrice);
	}
}

void Lwrite(Level *niveau)
{
	FILE *file;
	if ((file = fopen("niveaux\\level.bin", "ab")) == NULL)
	{
		//("Eror opening file");
		exit(EXIT_FAILURE);
	}
	fwrite(&niveau->id, sizeof(int), 1, file);
	fwrite(&niveau->np, sizeof(int), 1, file);
	fwrite(&niveau->resolution, sizeof(Vector2), 1, file);
	for (int i = 0; i != niveau->resolution.y; i++)
		fwrite(niveau->t[i], sizeof(int), niveau->resolution.x, file);
	fclose(file);
}

void Lread(Level *niveau, int j)
{
	FILE *file;
	if ((file = fopen("niveaux\\level.bin", "rb")) == NULL)
	{
		//("Eror opening file");
		exit(EXIT_FAILURE);
	}
	niveau->t = NULL;
	do
	{
		fread(&niveau->id, sizeof(int), 1, file);
		fread(&niveau->np, sizeof(int), 1, file);
		fread(&niveau->resolution, sizeof(Vector2), 1, file);
		Mfree(niveau->t, niveau->resolution.x);
		niveau->t = Minitialiser(niveau->resolution.y, niveau->resolution.x);
		for (int i = 0; i != niveau->resolution.y; i++)
			fwrite(niveau->t[i], sizeof(int), niveau->resolution.x, file);
	} while (niveau->id != j);

	fclose(file);
}
