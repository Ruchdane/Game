#define PIX 34
#define TAILLE 18
#define TEST 0
#include "stdio.h"
#include "SDL.h"
#include"SDL_image.h"
#include "SDL_ttf.h"
#include "fonction.h"
#include "structure.h"
#include "Gui.h"
#include "rule.h"
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

int win (int t[TAILLE][TAILLE])
{
	int brak=0,s1,s2;
	for(s1=0;s1!=TAILLE;s1++)
		for(s2=0;s2!=TAILLE;s2++)
			if(t[s1][s2]==2)
			brak=1;
  return brak;
}

/*		switch(key)
	{
		case SDLK_LEFT:
		return 0;
		break;
		
		case SDLK_UP:
		return 1;
		
		case SDLK_DOWN:
		return 2;
		break;
		
		case SDLK_RIGHT:
		return 3
		break ;
	}

}*/
int judge(int *k,int t[TAILLE][TAILLE],int key)
{
	int s1=0,s2=0,j,result=1,stop=1;
	for(;s1!=TAILLE && stop ;s1++)
		for(s2=0;s2!=TAILLE && stop;s2++)
			if(t[s1][s2]==5)
				stop=0;
	s1--;
	s2--;
	switch(key)
	{
		case SDLK_LEFT:
		{
				j=0;
			switch(t[s1][nohomo(s2-1)])
			{
				case 0:
				{
					t[s1][s2]=0;
					t[s1][nohomo(s2-1)]=5;
				}
			break;

			case 3:
				switch(t[s1][nohomo(s2-2)])
				{
					case 0:
					{
						t[s1][s2]=0;
						t[s1][nohomo(s2-1)]=5;
						t[s1][nohomo(s2-2)]=3;
					}
					break;
					
					case 2:
						{
							t[s1][s2]=0;
							t[s1][nohomo(s2-1)]=5;
							t[s1][nohomo(s2-2)]=4;
						}   
						
						break;
					default:
				result=0;
						break;
				}
				break;

			default:
				result=0;
			break;
			} 
		
		}
		break;
		
		case SDLK_UP:
			{
				j=1;
				switch(t[nohomo(s1-1)][s2])
				{
					case 0:
					{
						t[s1][s2]=0;
						t[nohomo(s1-1)][s2]=5;
					}
					break;
			
				case 3:
					switch(t[nohomo(s1-2)][s2])
					{
						case 0:
						{
							t[s1][s2]=0;
							t[nohomo(s1-1)][s2]=5;
							t[nohomo(s1-2)][s2]=3;
						}
						break;

						case 2:
						{
							t[s1][s2]=0;
							t[nohomo(s1-1)][s2]=5;
							t[nohomo(s1-2)][s2]=4;
						}
						break;
					default:
				result=0;
						break;
					}
					break;

			default:
				result=0;
				break;
			}
			s1=nohomo(s1);
		
			}
			break;
			
		case SDLK_DOWN:
		{j=2;
			switch(t[nohomo(s1+1)][s2])
			{ case 0:
				{ t[s1][s2]=0;
				t[nohomo(s1+1)][s2]=5;}
				break;
				
			case 3:
				switch(t[nohomo(s1+2)][s2])
				{case 0:
				{t[s1][s2]=0;
				t[nohomo(s1+2)][s2]=3;
				t[nohomo(s1+1)][s2]=5;
				}
				break;
				case 2:
				{t[s1][s2]=0;
				t[nohomo(s1+2)][s2]=4;
				t[nohomo(s1+1)][s2]=5;
				}
				break;
			
				default:
				result=0;
				break;
				}
				break;
				
			default:
				result=0;
			break;
			}
			
		}
		break;
		
		case SDLK_RIGHT:
		{j=3;
			switch(t[s1][nohomo(s2+1)])
			{case 0:
			{t[s1][s2]=0;
			t[s1][nohomo(s2+1)]=5;}
			break;
			
			case 3:
			switch(t[s1][nohomo(s2+2)])
			{case 0:
				{t[s1][s2]=0;
				t[s1][nohomo(s2+2)]=3;
				t[s1][nohomo(s2+1)]=5;
				}
				break;
			case 2:
				{t[s1][s2]=0;
				t[s1][nohomo(s2+2)]=4;
				t[s1][nohomo(s2+1)]=5;
				}
				break;
			
			default:
				result=0;
				break;
			}
			
			default:
				result=0;
				break;
			}

			
		}
		
			break ;
			
		default:
				result=0;
		break;
	}
	*k=j;
	return result;
}
