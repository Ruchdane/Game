#include "stdio.h"
#include "stdlib.h"
#define PIX 34
#define TEST 0
#include "SDL.h"
#define Failed_case -100
#include"SDL_image.h"
#include "SDL_ttf.h"
#include "fonction.h"
#include "structure.h"
#include "rule.h"
#include "ini.h"
#include "Gui.h"


void jouer( SDL_Window *ecran,SDL_Renderer* renderer ,SDL_Texture **textures ,int k)
{
	SDL_Rect om={0,0,34,34},oom={0,0,34,34};
	SDL_Event event;
	Pile *actions;
	int s,j=0;
	Level *niveau;
	niveau=malloc(sizeof(*niveau));
	
	for(;k!=Failed_case;)
	{
		if(Linitialiser(niveau,k))
		{
		actions=Pinitialiser();
		renderLevel(niveau,3,ecran,renderer,textures);
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

					renderLevel(niveau,j,ecran,renderer,textures);
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
					k=menuButton(ecran,renderer,4,CreateButton(k+1,50,10,2,2,0,0,"suivant"),CreateButton(k-1,50,10,2,2,0,50,"precedent")
						,CreateButton(k,50,10,2,2,0,100,"rejouer"),CreateButton(Failed_case,50,10,2,2,0,150,"exit"));
				else
					k=menuButton(ecran,renderer,3,CreateButton(k+1,50,10,2,2,0,0,"suivant")
						,CreateButton(k,50,10,2,2,0,100,"rejouer"),CreateButton(Failed_case,50,10,2,2,0,150,"exit"));
				
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

void niveau( SDL_Window *ecran,SDL_Renderer* renderer ,SDL_Texture **textures)
{
	SDL_Event event;
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
			SDL_stop("Renderer couleur non change",ecran,renderer,NULL);
		}

	renderLevel(niveau,0,ecran,renderer,textures);
	
		
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
				
				renderLevel(niveau,0,ecran,renderer,textures);
				SDL_WaitEvent(&event);
			}
		}
	}while(event.key.keysym.sym!=SDLK_ESCAPE);
	if(SDL_SetRenderDrawColor(renderer,0,0,0,225)==-1)
		{
			for(int i=0;i!=10;i++)
				SDL_DestroyTexture(textures[i]);
			SDL_stop("Renderer couleur non change",ecran,renderer,NULL);
		}

	translate(niveau);
	
}



int main (int argc, char *argv[])
{
	/*------------------------------------*/
	int j=1,s1,s2;
	SDL_Window *ecran=NULL;
	SDL_Surface *surface=NULL;
	SDL_Renderer* renderer;
	SDL_Event event;
	SDL_Texture *textures[10];
	
	/*------------------------------------*/
	
	/*------------------------------------*/

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
	
	/*------------------------------------*/
	
	/*------------------------------------*/
	int *height=getSettings("screenSetting","height"),*width=getSettings("screenSetting","width");
	ecran = SDL_CreateWindow("Mario Sokoban",
                          SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED,
                          *width,*height,
                           0);
	free(height);
	free(width);
	if(ecran==NULL)
		SDL_stop("ecran non aloue",NULL,NULL,NULL);
	
	surface=IMG_Load("img/mur.png");
	if(surface==NULL)
		SDL_stop("L'image n'as pas pu etre charger",ecran,NULL,NULL);
	

	SDL_SetWindowIcon(ecran,surface);
	SDL_FreeSurface(surface);
	
	renderer=SDL_CreateRenderer(ecran,-1,0);
	
	if(renderer==NULL)
		SDL_stop("desinateur non  aloue",ecran,NULL,NULL);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	textures[0]=TextureFromImage("img/vide.png",ecran,renderer);
	textures[1]=TextureFromImage("img/mur.png",ecran,renderer);
	textures[2]=TextureFromImage("img/objectif.png",ecran,renderer);
	textures[3]=TextureFromImage("img/0.png",ecran,renderer);
	textures[4]=TextureFromImage("img/1.png",ecran,renderer);
	textures[5]=TextureFromImage("img/0.gif",ecran,renderer);
	textures[6]=TextureFromImage("img/1.gif",ecran,renderer);
	textures[7]=TextureFromImage("img/2.gif",ecran,renderer);
	textures[8]=TextureFromImage("img/3.gif",ecran,renderer);
	textures[9]=TextureFromImage("img/images.png",ecran,renderer);
	
	while(j)
	{
		switch(menuButton(ecran,renderer,3,
			CreateButton(1,50,10,2,2,0,0,"start"),
			CreateButton(2,50,10,2,2,0,50,"editeur de niveau"),CreateButton(3,50,10,2,2,0,100,"exit")))
		{
			case 1:
			jouer(ecran,renderer,textures,1);
			break;
	
			case 2 :
			{
				niveau(ecran,renderer,textures);
				jouer(ecran,renderer,textures,-1);
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
