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