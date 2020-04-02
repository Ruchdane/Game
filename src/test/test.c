#include "stdio.h"
#include "stdlib.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"


/*gcc src\*c -o bin\mario.c -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf*/
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

int renderButton(Button button,SDL_Window* window,SDL_Renderer* renderer,TTF_Font *writer)
{
		int state=0;
		Descartes position;
		int mstate=SDL_GetMouseState(&position.x,&position.y);
		SDL_Surface* surface=NULL;
		SDL_Texture* texture=NULL;
	
		SDL_Color test={225,192,0},ombre={164,181,198};
		int box[3][3]={{0,0,225},{89,89,225},{0,0,95}};
		/* state 0 idle   */
		/*       1 select */
		/*       2 clik   */

			surface=TTF_RenderText_Blended(writer,button.message, test);

			if(button.cadre.x < position.x && position.x < button.cadre.x + button.cadre.w+3*(button.padin.x+button.margin.x) &&
				button.cadre.y < position.y  && position.y< button.cadre.y + button.cadre.h+4*(button.padin.y+button.margin.y))
					{
						if(mstate & SDL_BUTTON(SDL_BUTTON_LEFT))
							state=2;
						else
							state=1;
					}
			else
				state=0;
	
			
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			Descartes tmp;
			if(state==2)
			{
				tmp=button.margin;
				button.margin.x=0;
				button.margin.y=0;
				button.padin.x +=tmp.x;
				button.padin.y +=tmp.y;
			}
			SDL_QueryTexture(texture,NULL,NULL,&button.cadre.w,&button.cadre.h);
			//on veut desner 3 recctangle
			//l'ombre
			button.cadre.w+=2*(button.padin.x+button.margin.x);
			button.cadre.h+=2*(button.padin.y+button.margin.y);
			
			SDL_SetRenderDrawColor(renderer,164,181,198,225);
			SDL_RenderFillRect(renderer,&button.cadre);
			
			/*//le cadre
			button.cadre.x+=button.margin.x;
			button.cadre.y+=button.margin.y;*/
			button.cadre.w-=2*(button.margin.x);
			button.cadre.h-=2*(button.margin.y);
			
			SDL_SetRenderDrawColor(renderer,box[state][0],box[state][1],box[state][2],225);
			SDL_RenderFillRect(renderer,&button.cadre);

			//le titre
			button.cadre.x+=button.padin.x;
			button.cadre.y+=button.padin.y;
			button.cadre.w-=2*button.padin.x;
			button.cadre.h-=2*button.padin.y;
			SDL_RenderCopy(renderer,texture,NULL,&button.cadre);
			
			
			
			button.cadre.x-=button.padin.x;
			button.cadre.y-=button.padin.y;
			
			
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surface);
		if(state==2)
			return button.value;
		else 
			return 0;
}


int menu(SDL_Window* window,SDL_Renderer* renderer)
{
		int height=20,x=0,y=0;
		SDL_Event event;
		TTF_Font *writer;
		int j;
		Button buttons[]={{1,{50,10},{2,2},{x,y,0,0},"start"},{2,{50,10},{2,2},{x,y+50,0,0},"select"},{3,{50,10},{2,2},{x ,y+100,0,0}," exit "}};
		writer=TTF_OpenFont("Font/Champagne & Limousines Bold.ttf",height);
		
		do
		{
			SDL_PollEvent(&event);
			for(int i=0;i!=3;i++)
			{
				j=renderButton(buttons[i],window,renderer,writer);
				
				if(j)
					return j;
			}
			SDL_RenderPresent(renderer);
			SDL_SetRenderDrawColor(renderer,225,225,225,225);
			SDL_RenderClear(renderer);
			
		}while(event.type!=SDL_QUIT);
		TTF_CloseFont(writer);
		TTF_Quit();
		return 0;
}

/*int main(int argc, char* argv[])
{
	/*Declaration*/
		SDL_Window* window=NULL;
		SDL_Renderer* renderer=NULL;
		
	
	/*Chargement des systemes*/
		SDL_Init(SDL_INIT_VIDEO); 
		IMG_Init(IMG_INIT_PNG);
		TTF_Init();
	/*initialisation des vaiables*/

		window=SDL_CreateWindow("TEST",25,25,800,600,0);
		
		renderer=SDL_CreateRenderer(window,-1,0);

	/*----------------------------------*/
	SDL_SetRenderDrawColor(renderer,225,225,225,225);
	SDL_RenderClear(renderer);
	menu(window,renderer);
	/*----------------------------------*/
		
		SDL_DestroyRenderer(renderer);

		SDL_DestroyWindow(window);
		
		SDL_Quit();
		return 0;
}*/