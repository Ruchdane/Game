#include "rule.h"

void verification(Level *niveau)/*Inprimer le tableau des des donner-*/

{
	int s1,s2;
	  for(s1=0;s1!=niveau->resolution.x;s1++)
		{
		  for(s2=0;s2!=niveau->resolution.y;s2++)
			printf(" %d ",niveau->t[s1][s2]);
		  printf("\n");
		}
		   printf("\n");
	 
}

int nohomo(int z,int limit)/*eviter des ereiur de segmentation*/

{
	int n;
	if (z<0)
		n=0;
	else if(z>(limit-1))
		n=limit-1;
	else
		n=z;
	return n;
}

void verdict(Level *niveau,int *pos,int* pas1,int* pas2,int *result)
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
				niveau->np--;
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
				niveau->np++;
			}
			break;
			
			case 2:
				{
					*pos=(*pos-5)/2;
					*pas1=9;
					*pas2=4;
					/*niveau->np--;*/
					/*niveau->np++;*/
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
void annuler(int *j,Level *niveau,int k,Pile *actions)
{
	Pile *tmp;
	tmp=Pinverse(actions);
	Mfree(niveau->t,niveau->resolution.y);
	
	niveau->t=Minitialiser(niveau->resolution.x,niveau->resolution.y);
	Linitialiser(niveau,k);
	for(;tmp->premier->suivant!=NULL;depiler(tmp))
		judge(j,niveau,tmp->premier->nombre,actions);
	Pfree(tmp);
}
int judge(int *k,Level *niveau,int key,Pile *actions)
{
	int s1=0,s2=0,j,result=1,stop=1;
	int **t=niveau->t;
	for(;s1!=niveau->resolution.x && stop ;s1++)
		for(s2=0;s2!=niveau->resolution.y && stop;s2++)
			if(niveau->t[s1][s2]==5 || niveau->t[s1][s2]==9 )
				stop=0;
	s1--;
	s2--;
	switch(key)
	{
		case SDLK_RIGHT:
		{
			j=3;
			verdict(niveau,&t[s1][s2],&t[s1][nohomo(s2+1,niveau->resolution.y)],
									&t[s1][nohomo(s2+2,niveau->resolution.y)],&result);
		}
		break;
		case SDLK_LEFT:
		{
			j=0;
			verdict(niveau,&t[s1][s2],&t[s1][nohomo(s2-1,niveau->resolution.y)],
									&t[s1][nohomo(s2-2,niveau->resolution.y)],&result);
			
		}
		break;
		case SDLK_DOWN:
		{
			j=2;
			verdict(niveau,&t[s1][s2],&t[nohomo(s1+1,niveau->resolution.x)][s2],
							&t[nohomo(s1+2,niveau->resolution.x)][s2],&result);
		}
		break;
		
		case SDLK_UP:
		{
			j=1;
			verdict(niveau,&t[s1][s2],&t[nohomo(s1-1,niveau->resolution.x)][s2],
							&t[nohomo(s1-2,niveau->resolution.x)][s2],&result);
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
