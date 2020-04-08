#define PIX 34
#define TAILLE 18
#define TEST 0
#include "stdio.h"
#include "SDL.h"
#include"SDL_image.h"
#include "SDL_ttf.h"
#include "structure.h"
#include "rule.h"
#include "fonction.h"

#include "Gui.h"

int nohomo(int z)/*eviter des ereiur de segmentation*/

{
	int n;
	if (z<0)
		n=0;
	else if(z>(TAILLE-1))
		n=TAILLE-1;
	else
		n=z;
	return n;
}

int win (int **t)
{
	int s1,s2;
	for(s1=0;s1!=TAILLE;s1++)
		for(s2=0;s2!=TAILLE;s2++)
			if(t[s1][s2]==2 || t[s1][s2]==9 )
				return 1;
  return 0;
}

void verdict(int *pos,int* pas1,int* pas2,int *result)
{
	switch(*pas1)
	{
		case 0:
		{
			*pos=(*pos-5)/2;
			*pas1=5;
		}
		break;
		
		
		case 2:
		{
			*pos=(*pos-5)/2;
			*pas1=9;
		}
		break;

		break;
		case 3:
		switch(*pas2)
		{
			case 0:
			{
				*pos=(*pos-5)/2;
				*pas1=5;
				*pas2=3;
			}
			break;
			
			case 2:
			{
				*pos=(*pos-5)/2;
				*pas1=5;
				*pas2=4;
			}
			
			break;
			
			default:
			*result=0;
			break;
		}
		break;

		case 4:
		switch(*pas2)
		{
			case 0:
			{
				*pos=(*pos-5)/2;
				*pas1=9;
				*pas2=3;
			}
			break;
			
			case 2:
				{
					*pos=(*pos-5)/2;
					*pas1=9;
					*pas2=4;
				}   
				
				break;
			default:
			*result=0;
			break;
		}
		break;

		default:
		*result=0;
		break;
	} 

}
int estMouvement(SDL_Event event)
{
	int key=event.key.keysym.sym;
	return event.type==SDL_KEYDOWN && key-SDLK_RIGHT<=3 && key-SDLK_RIGHT>=0;
}

int estAnnulation(SDL_Event event)
{
	return event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_BACKSPACE;
}

int estQuiter(SDL_Event event)
{
	return event.type==SDL_QUIT;
}
int estRecommencer(SDL_Event event)
{
	return event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE;
}
void annuler(int *j,int ***t,int k,Pile *actions)
{
	Pile *tmp;
	tmp=Pinverse(actions);
	Mfree(*t,TAILLE);
	
	*t=Minitialiser(TAILLE,TAILLE);
	init0(*t,k);
	for(;tmp->premier->suivant!=NULL;depiler(tmp))
		judge(j,*t,tmp->premier->nombre,actions);
	Pfree(tmp);
}
int judge(int *k,int **t,int key,Pile *actions)
{
	int s1=0,s2=0,j,result=1,stop=1;
	for(;s1!=TAILLE && stop ;s1++)
		for(s2=0;s2!=TAILLE && stop;s2++)
			if(t[s1][s2]==5 || t[s1][s2]==9 )
				stop=0;
	s1--;
	s2--;

	switch(key)
	{
		case SDLK_RIGHT:
		{
			j=3;
			verdict(&t[s1][s2],&t[s1][nohomo(s2+1)],&t[s1][nohomo(s2+2)],&result);
		}
		break;
		case SDLK_LEFT:
		{
			j=0;
			verdict(&t[s1][s2],&t[s1][nohomo(s2-1)],&t[s1][nohomo(s2-2)],&result);
			
		}
		break;
		case SDLK_DOWN:
		{
			j=2;
			verdict(&t[s1][s2],&t[nohomo(s1+1)][s2],&t[nohomo(s1+2)][s2],&result);
		}
		break;
		
		case SDLK_UP:
		{
			j=1;
			verdict(&t[s1][s2],&t[nohomo(s1-1)][s2],&t[nohomo(s1-2)][s2],&result);
		}
		break;
		default:
		result=0;
		break;
	}
	if(result)
		empiler(actions,key);
	
	*k=j;
	return result;
}
