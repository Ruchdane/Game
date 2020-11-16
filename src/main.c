#include "main.h"
SDL_Window *ecran;
Vector2 Screnres;

SDL_Window *GetWindow() { return ecran; }

void jouer(SDL_Texture **textures ,int k)
{
	SDL_Rect om={0,0,34,34},oom={0,0,34,34};
	SDL_Renderer *renderer = SDL_GetRenderer(GetWindow());
	SDL_Event event;
	Pile *actions;
	int s,j=0;
	Level *niveau;
	Button *Buttons[4] = {
		CreateButton(k + 1, 50, 10, 2, 2, 0, 0, "suivant"),
		CreateButton(Failed_case, 50, 10, 2, 2, 0, 150, "exit"),
		CreateButton(k, 50, 10, 2, 2, 0, 100, "rejouer"),
		CreateButton(k - 1, 50, 10, 2, 2, 0, 50, "precedent")};
	niveau = malloc(sizeof(*niveau));

	for(;k!=Failed_case;)
	{
		if(Linitialiser(niveau,k))
		{
		actions=Pinitialiser();
		renderLevel(niveau,3,textures);
		SDL_RenderPresent(renderer);
		do
			{
				SDL_WaitEvent(&event);
				
				if(estAnnulation(event) && actions->premier !=NULL)
					annuler(&j,niveau,k,actions);
				
				else if(estMouvement(event))
					judge(&j,niveau,event.key.keysym.sym,actions);

				else if(estQuiter(event))
				{
					k=Failed_case;
					break;
				}
				else if(estRecommencer(event))
					break;
				else
					continue;

					renderLevel(niveau,j,textures);
					SDL_RenderPresent(renderer);
					SDL_RenderClear(renderer);

			}while( niveau->np);
		if(!niveau->np)
			{

				SDL_RenderClear(renderer);
				om.y=0;
				om.x=0;
				om.w=PIX;
				om.h=PIX;
				SDL_RenderCopy(renderer,textures[9],NULL,&om);
				SDL_RenderPresent(renderer);
				do
				{
					SDL_WaitEvent(&event);
				}
				while (event.type!=SDL_KEYDOWN);
					
				SDL_RenderClear(renderer);
				if(k!=1)
					k=menuButton(4,Buttons);
				else
					k=menuButton(3,Buttons);
				
			}
			
		}
		else
		{
			k=-1;
		}
		Pfree(actions);
		Mfree(niveau->t,niveau->resolution.y);
	}
	free(niveau);
}

void niveau(SDL_Texture **textures)
{
	SDL_Event event;
	SDL_Renderer *renderer = SDL_GetRenderer(GetWindow());
	FILE *file;
	int s,s1,s2;
	int *height=getSettings("screenSetting","height"),*width=getSettings("screenSetting","width");
	SDL_Rect om;
	Level *niveau=malloc(sizeof(*niveau));
	printf("resolution de votre niveau ");
	printf("\nLa profondeur :");
	scanf("%d",&niveau->resolution.x);
	printf("\nLa largeur :");
	scanf("%d",&niveau->resolution.y);

	niveau->t=Minitialiser(niveau->resolution.x,niveau->resolution.y);
	om.h=*height/niveau->resolution.x;
	om.w=*width/niveau->resolution.y;
	free(height);
	free(width);
	niveau->np=0;
	if(SDL_SetRenderDrawColor(renderer,0,0,225,1)==-1)
		{
			for(int i=0;i!=10;i++)
				SDL_DestroyTexture(textures[i]);
			SDL_stop("Renderer couleur non change",NULL);
		}

	renderLevel(niveau,0,textures);
	
		
	do
	{
		SDL_WaitEvent(&event);
	
		while(event.type==SDL_KEYDOWN)
		{
				switch(event.key.keysym.sym)
			{
				case SDLK_UP:
					s1--;
				break;
				
				case SDLK_DOWN:
					s1++;
				break;
				
				case SDLK_RIGHT:
					s2++;
				break;
				
				case SDLK_LEFT:
					s2--;
				break;
				
				default:
				break;
			}

			s1=nohomo(s1,niveau->resolution.x);
			s2=nohomo(s2,niveau->resolution.y);
			om.x=s2*om.w;
			om.y=s1*om.h;

			SDL_SetRenderDrawColor(renderer,0,0,225,0);
			SDL_RenderFillRect(renderer,&om);
			SDL_RenderPresent(renderer);
	
			while(event.type!=SDL_KEYDOWN)
				SDL_WaitEvent(&event);	     
	
			while(event.type==SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_KP_0:
						niveau->t[s1][s2]=0;
					break;
					
					case SDLK_KP_1:
						niveau->t[s1][s2]=1;
					break;
					
					case SDLK_KP_2:
					niveau->np++;
						niveau->t[s1][s2]=2;
					break;
					
					case SDLK_KP_3:
						niveau->t[s1][s2]=3;
					break;
					
					case SDLK_KP_4:
						niveau->t[s1][s2]=4;
					break;
					
					case SDLK_KP_5:
						niveau->t[s1][s2]=5;
					break;
					
					default:
					break;
				}
				
				renderLevel(niveau,0,textures);
				SDL_WaitEvent(&event);
			}
		}
	}while(event.key.keysym.sym!=SDLK_ESCAPE);
	if(SDL_SetRenderDrawColor(renderer,0,0,0,225)==-1)
		{
			for(int i=0;i!=10;i++)
				SDL_DestroyTexture(textures[i]);
			SDL_stop("Renderer couleur non change",NULL);
		}

	translate(niveau);
	
}

int main (int argc, char *argv[])
{
	/*------------------------------------*/
	int j=1,s1,s2;
	SDL_Surface *surface=NULL;
	SDL_Event event;
	SDL_Texture *textures[10];
	SDL_Renderer *renderer;
	Button *MainMenu[3] = {
		CreateButton(1, 50, 10, 2, 2, 0, 0, "start"),
		CreateButton(2, 50, 10, 2, 2, 0, 50, "editeur de niveau"),
		CreateButton(3, 50, 10, 2, 2, 0, 100, "exit")};
	/*------------------------------------*/

	/*------------------------------------*/

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
	
	/*------------------------------------*/
	
	/*------------------------------------*/
	int *height=getSettings("screenSetting","height"),*width=getSettings("screenSetting","width");
	ecran = SDL_CreateWindow(
		"Mario Sokoban",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		*width, *height,
		0);
	free(height);
	free(width);
	if(ecran==NULL)
		SDL_stop("ecran non aloue",NULL);
	
	surface=IMG_Load("../img/mur.png");
	if(surface==NULL)
		SDL_stop("L'image n'as pas pu etre charger",NULL);
	

	SDL_SetWindowIcon(ecran,surface);
	SDL_FreeSurface(surface);
	
	renderer=SDL_CreateRenderer(ecran,-1,0);
	
	if(renderer==NULL)
		SDL_stop("desinateur non  aloue",NULL);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	textures[0]=TextureFromImage("../img/vide.png");
	textures[1]=TextureFromImage("../img/mur.png");
	textures[2]=TextureFromImage("../img/objectif.png");
	textures[3]=TextureFromImage("../img/0.png");
	textures[4]=TextureFromImage("../img/1.png");
	textures[5]=TextureFromImage("../img/0.gif");
	textures[6]=TextureFromImage("../img/1.gif");
	textures[7]=TextureFromImage("../img/2.gif");
	textures[8]=TextureFromImage("../img/3.gif");
	textures[9]=TextureFromImage("../img/images.png");
	
	while(j)
	{
		switch(menuButton(3,MainMenu))
		{
			case 1:
			jouer(textures,1);
			break;
	
			case 2 :
			{
				niveau(textures);
				jouer(textures,-1);
			}
			break;
	
			default:
			j=0;
			break;
		}
	}
	for(int s=0;s!=10;s++)
		SDL_DestroyTexture(textures[s]);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(ecran);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
