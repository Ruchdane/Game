#include "fonction.h"
SDL_Texture *TextureFromImage(char *title)
{
	SDL_Window *ecran = GetWindow();
	SDL_Renderer *renderer = SDL_GetRenderer(ecran);
	SDL_Surface *surface = IMG_Load(title);
	SDL_Texture *texture = NULL;
	SDL_Rect rectangle = {0, 0, PIX, PIX};
	if (surface == NULL)
		SDL_stop("surface non aloue", NULL);

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	if (texture == NULL)
		SDL_stop("surface non convertie en texture", NULL);

	SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h);
	return texture;
}
void SDL_stop(const char *message, SDL_Texture *texture)
{
	SDL_Window *ecran = GetWindow();
	SDL_Renderer *renderer = SDL_GetRenderer(ecran);
	printf("EROR :%s --%s\n", message, SDL_GetError());
	if (ecran != NULL)
		SDL_DestroyWindow(ecran);
	if (renderer != NULL)
		SDL_DestroyRenderer(renderer);
	if (texture != NULL)
		SDL_DestroyTexture(texture);

	SDL_Quit();
	exit(EXIT_FAILURE);
}

void translate(Level *nivo)

{
	unsigned int s = 0, mask;
	int brak = 1, s1, s2;
	FILE *niveau;
	int **t = nivo->t;
	if ((niveau = fopen("../niveaux/perso", "w+")) == NULL)
		printf("Eror opening file");
	fprintf(niveau, "(%d,%d),", nivo->resolution.x, nivo->resolution.y);
	for (s1 = 0; s1 != nivo->resolution.x; s1++)
		for (s2 = 0; s2 != nivo->resolution.y; s2++)
			if (t[s1][s2] == 2 || t[s1][s2] == 4)
				s++;
	fprintf(niveau, "%d,", s);
	for (s = 0, s1 = 0; s1 != nivo->resolution.x; s1++)
	{
		for (mask = 1 << nivo->resolution.y - 1, s = 0, s2 = 0; s2 != nivo->resolution.y; mask /= 2, s2++)
			if (t[s1][s2] == 1)
				s |= mask;
		fprintf(niveau, "%d,", s);
	}
	/*   
		remplisage // egasimpmer
			0=vide;
		1=mur;
		2=perle verte;
		3=boite;
		4=2+3;
		5=mario
	*/

	for (s1 = 0; s1 != nivo->resolution.x; s1++)
		for (s2 = 0; s2 != nivo->resolution.y; s2++)
			if (t[s1][s2] == 2 || t[s1][s2] == 4)
				fprintf(niveau, "(%d,%d),", s1, s2);

	for (s1 = 0; s1 != nivo->resolution.x; s1++)
		for (s2 = 0; s2 != nivo->resolution.y; s2++)
			if (t[s1][s2] == 3 || t[s1][s2] == 4)
				fprintf(niveau, "(%d,%d),", s1, s2);

	for (s1 = 0; s1 != nivo->resolution.x; s1++)
		for (s2 = 0; s2 != nivo->resolution.y; s2++)
			if (t[s1][s2] == 5)
			{
				fprintf(niveau, "(%d,%d),", s1, s2);
				brak = 0;
			}

	fclose(niveau);
}

int monitor()
{
	int id;
	#ifdef unix
	char *command = malloc(100 * sizeof(char));
	sprintf(command,"gnome-terminal -- top -p %d",getpid());
	id = system(command);
	free(command);
	#endif 
	return id;
}