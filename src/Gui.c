#include "Gui.h"

int renderButton(Button button,TTF_Font *writer,int state)
{
	Vector2 position;
	SDL_Window *ecran = GetWindow();
	SDL_Renderer *renderer = SDL_GetRenderer(ecran);
	int mstate = SDL_GetMouseState(&position.x, &position.y);
	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;
	Vector2 tmp;

	/* state 0 idle      */
	/*       1 on_select */
	/*       2 on_clik   */

	surface = TTF_RenderText_Blended(writer, button.message, button.test);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture, NULL, NULL, &button.cadre.w, &button.cadre.h);

	if (PositionInButtons(button, position))
	{
		if (mstate & SDL_BUTTON(SDL_BUTTON_LEFT))
			state = 2;
		else
			state = 1;
	}

	if (state == 2)
	{
		tmp = button.margin;
		button.margin.x = 0;
		button.margin.y = 0;
		button.padin.x += tmp.x;
		button.padin.y += tmp.y;
		button.couleur = DimColor(button.couleur, 3);
	}
	if (state == 1)
	{
		button.couleur = LightenColor(button.couleur, 2);
	}
	//on veut desner 3 recctangle
	//l'ombre
	button.cadre.x -= button.margin.x;
	button.cadre.y -= button.margin.y;
	button.cadre.w += 2 * (button.padin.x + button.margin.x);
	button.cadre.h += 2 * (button.padin.y + button.margin.y);

	SDL_SetRenderDrawColorWithColor(renderer, button.ombre);
	SDL_RenderFillRect(renderer, &button.cadre);

	//le cadre
	button.cadre.x += button.margin.x;
	button.cadre.y += button.margin.y;
	button.cadre.w -= 2 * (button.margin.x);
	button.cadre.h -= 2 * (button.margin.y);

	SDL_SetRenderDrawColorWithColor(renderer, button.couleur);
	SDL_RenderFillRect(renderer, &button.cadre);

	//le titre
	button.cadre.x += button.padin.x;
	button.cadre.y += button.padin.y;
	button.cadre.w -= 2 * button.padin.x;
	button.cadre.h -= 2 * button.padin.y;
	//la couleur est appliquer en haut
	SDL_RenderCopy(renderer, texture, NULL, &button.cadre);

	button.cadre.x -= button.padin.x;
	button.cadre.y -= button.padin.y;

	SDL_DestroyTexture(texture);
	if (state == 2)
		return button.value;
	if (state == 1)
		return 100;
	else
		return 0;
}

int menuButton(int bn,Button **B)
{
	SDL_Window *ecran = GetWindow();
	SDL_Renderer *renderer = SDL_GetRenderer(ecran);
	int height = 20, state = 0, pstate = 0, i = 0, j, k = 0;
	SDL_Event event;
	TTF_Font *writer;
	if (B == NULL)
		return 0;
	writer = TTF_OpenFont("../Font/Champagne & Limousines Bold.ttf", height);
	if (writer == NULL)
		printf("Font could not be loaded");
	do
	{
		SDL_PollEvent(&event);
		state = 0;
		if (event.type == SDL_KEYDOWN)
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				i--;
				break;

			case SDLK_DOWN:
				i++;
				break;

			case SDLK_RETURN:
				state = 1;
				break;
			}
		for (j = 0; j != bn && k == 0; j++)
		{
			if (i % bn == j)
			{
				if (state == 1)
					k = renderButton(*B[j],  writer, 2);
				else
					k = renderButton(*B[j], writer, 1);
			}
			else
				k = renderButton(*B[j], writer, 0);
			if (k == 100)
			{
				i = j;
				k = 0;
			}
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(FPS);
		SDL_SetRenderDrawColor(renderer, 225, 225, 225, 225);
		SDL_RenderClear(renderer);
			
		}while(event.type!=SDL_QUIT && k==0 && NotQuit(event));
		
		TTF_CloseFont(writer);
		for (i = 0; i < bn;i++)
			free(B[i]);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);
		return k;
}

void renderLevel (Level *niveau,int j,SDL_Texture **textures)

{
	static int isInitialised;
	SDL_Window *ecran = GetWindow();
	SDL_Renderer *renderer = SDL_GetRenderer(ecran);
	static Vector2 Screnres;
	int s1=0,s2=0,b=1,k;
	SDL_Rect cadre={0,0,34,34};
	if(!isInitialised)
	{
		int *i;
		i=getSettings("screenSetting","height");
		Screnres.x=*i;
		i=getSettings("screenSetting","width");
		Screnres.y=*i;
		isInitialised=1;
		free(i);
	}
	cadre.h=Screnres.x/niveau->resolution.x;
	cadre.w=Screnres.y/niveau->resolution.y;
	SDL_SetRenderDrawColor(renderer,0,0,0,225);
	SDL_RenderClear(renderer);
	/*donc maintenant on a represente tout les TAILLE*PIX*TAILLE*PIX pixel en 144 PIX*PIX
	Voyez ça comme un changement de reper 
	donc la position PIX,PIX
	devent 1,1 ce qui revient a notre tableau de TAILLE*TAILLE 
	wow je suis un genie ruch le boss
	*/
  
	
	for(s1=0;s1!=niveau->resolution.x;s1++)
		for(s2=0;s2!=niveau->resolution.y;s2++)
		{
		cadre.y=s1*cadre.h;
		cadre.x=s2*cadre.w;
		
	/*
		petit rapel 
		0=vide;
		1=mur;
		2=perle verte;
		3=boite;
		4=2+3;
		5,6,7,8=mario
		9=2+(5,6,7,8)
	*/

		k=niveau->t[s1][s2];
		if(k<5)
			SDL_RenderCopy(renderer,textures[k],NULL,&cadre);
		else if(k<9)
			SDL_RenderCopy(renderer,textures[k+j],NULL,&cadre);
		else
		{
			SDL_RenderCopy(renderer,textures[2],NULL,&cadre);
			SDL_RenderCopy(renderer,textures[5+j],NULL,&cadre);
		} 
		
	}
}
