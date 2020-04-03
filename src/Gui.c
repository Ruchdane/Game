#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "structure.h"
#include "Gui.h"
#include "rule.h"
#define FPS 1000/20

int renderButton(Button button,SDL_Window* window,SDL_Renderer* renderer,TTF_Font *writer,int state)
{
		Descartes position;
		int mstate=SDL_GetMouseState(&position.x,&position.y);
		SDL_Surface* surface=NULL;
		SDL_Texture* texture=NULL;
	
		SDL_Color test={225,192,0},ombre={164,181,198};
		int box[3][3]={{0,0,225},{89,89,225},{0,0,95}};
		/* state 0 idle   */
		/*       1 on_select */
		/*       2 on_clik   */
		surface=TTF_RenderText_Blended(writer,button.message, test);
		texture=SDL_CreateTextureFromSurface(renderer,surface);
		SDL_FreeSurface(surface);
		SDL_QueryTexture(texture,NULL,NULL,&button.cadre.w,&button.cadre.h);
		
			if(button.cadre.x < position.x && position.x < button.cadre.x + button.cadre.w+2*(button.padin.x+button.margin.x) &&
				button.cadre.y < position.y  && position.y< button.cadre.y + button.cadre.h+2*(button.padin.y+button.margin.y))
					{
						if(mstate & SDL_BUTTON(SDL_BUTTON_LEFT))
							state=2;
						else
							state=1;
					}
			
	
			
			Descartes tmp;
			if(state==2)
			{
				tmp=button.margin;
				button.margin.x=0;
				button.margin.y=0;
				button.padin.x +=tmp.x;
				button.padin.y +=tmp.y;
			}
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
		if(state==2)
			return button.value;
		if(state==1)
			return 100;
		else 
			return 0;
}

int menuButton(SDL_Window* window,SDL_Renderer* renderer,int bn,Button *b1, ...)
{
		va_list bp;/*buton pointer*/
		Button **b;
		int height=20,state=0,pstate=0,i=0,j,k=0;
		SDL_Event event;
		TTF_Font *writer;
		writer=TTF_OpenFont("Font/Champagne & Limousines Bold.ttf",height);
		b=malloc(bn*sizeof(*b));
		if(b==NULL)
			exit(EXIT_FAILURE);
		va_start(bp,b1);
		
		b[0]=b1;

		for(j=1;j!=bn;b[j]=va_arg(bp,Button*),j++);
		
		va_end(bp);
		
		do
		{
			SDL_PollEvent(&event);
			state=0;
			if(event.type==SDL_KEYDOWN)
				switch(event.key.keysym.sym)
				{
					case SDLK_UP:
					i--;
					break;
					
					case SDLK_DOWN:
					i++;
					break;

					case SDLK_RETURN:
					state=1;
					printf("It was I Dio\n");
					break ;
				}
			for(j=0;j!=bn && k==0;j++)
				{
					if(i%bn==j)
						{
							if(state==1)
								k=renderButton(*b[j],window,renderer,writer,2);
							else
								k=renderButton(*b[j],window,renderer,writer,1);
						}
					else
						k=renderButton(*b[j],window,renderer,writer,0);
					if(k==100)
						{
							i=j;
							k=0;
						}
					
				}
			SDL_RenderPresent(renderer);
			SDL_Delay(FPS);
			SDL_SetRenderDrawColor(renderer,225,225,225,225);
			SDL_RenderClear(renderer);
			
		}while(event.type!=SDL_QUIT && k==0);
		
		TTF_CloseFont(writer);
		for(j=0;j!=bn;free(b[j]),j++);
		free(b);
		SDL_SetRenderDrawColor(renderer,0,0,0,225);
		printf("tsugi  ni omae wa \"%d nani\"to you\n",k);
		return k;
}
