#include "stdio.h"
#include "stdlib.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Polynome.h"
#include "fonction.h"
#include "structure.h"
#include "rule.h"
/*<>*/
SDL_Texture* TextureFromImage(char *title,SDL_Window* window,SDL_Renderer *renderer)
{
		SDL_Surface* surface= IMG_Load(title);
		SDL_Texture* texture = NULL;
		SDL_Rect rectangle={0,0,PIX,PIX};
		if(surface==NULL)
			SDL_stop("surface non aloue",window,renderer,NULL);

		texture=SDL_CreateTextureFromSurface(renderer,surface);

			SDL_FreeSurface(surface);
		if(texture==NULL)
			SDL_stop("surface non convertie en texture",window,renderer,NULL);
		
		SDL_QueryTexture(texture,NULL,NULL,&rectangle.w,&rectangle.h);
		return texture;
}
void  SDL_stop(const char *message,SDL_Window* window,SDL_Renderer *renderer,SDL_Texture *texture)
{
	printf("EROR :%s --%s\n",message,SDL_GetError());
	if(window!=NULL)
		SDL_DestroyWindow(window);
	if(renderer!=NULL)
		SDL_DestroyRenderer(renderer);
	if(texture!=NULL)
		SDL_DestroyTexture(texture);
	
	SDL_Quit();
	exit(EXIT_FAILURE);
}
void verification(int **t)/*Inprimer le tableau des des donner-*/

{
	int s1,s2;
	  for(s1=0;s1!=TAILLE;s1++)
		{
		  for(s2=0;s2!=TAILLE;s2++)
			printf(" %d ",t[s1][s2]);
		  printf("\n");
		}
		   printf("\n");
	 
}

int init0 (int **t,int j)
{
	char c;
	int s=0,s1,s2,s3,nivo[TAILLE]={0};
	FILE *niveau=NULL;

	/*Bon les commentaire c'est pas mon fort
	donc je charge les nombre ecrit sur TAILLE bit 
	je les charges dans TAILLE tableau chaque nombre
	representes TAILLE cases sur la s1-iéme ligne
	le remplisage bon 
	0=vide;
	1=mur;
	2=perle verte;
	3=boite;
	4=2+3;
	5=mario
	*/
	if(j>0)/*j represente le niveau*/
	{
		niveau=fopen("niveaux/niveau","r");

		for(j--;j;j--)
		{
			c=fgetc(niveau);
			while(c!='\n'&&feof(niveau)==0)
				c=fgetc(niveau);
		}/*positioner le curseur au niveau de la line j*/
	}

	else
	{
		niveau=fopen("niveaux/perso","r");
	}
	
	if(j==3)/*Euh il n'y a pas de niveau 3*/
	{	
		fclose(niveau);
		return 0;
	}
	else
	{
		fscanf(niveau,"%d,",&s);
		s3=s;/*Le nombre de perle qu'il y a*/
		for(s1=0;s1!=TAILLE;s1++)/*j'initialise le tableau*/
			fscanf(niveau,"%d,",&nivo[s1]);/*niveau contient un nombre ecrit sur Taille-bit*/

		
		for(;s!=0;s--)
		{
			fscanf(niveau,"(%d,%d),",&s1,&s2);/*les positions des perles vertes*/
			t[s1][s2]=2;
		}

	for(s=s3;s!=0;s--)
		{
			fscanf(niveau,"(%d,%d),",&s1,&s2);/*les positions des boites*/
			if(t[s1][s2]==2)
				t[s1][s2]=4;
			else
				t[s1][s2]=3;
		}
	}
  
	fscanf(niveau,"(%d,%d),",&s1,&s2);
	if(2*TAILLE-s1-s2)/*nohomo*/
		t[s1][s2]=5;
	else
	  printf("coordonates of mario couldn't be loaded");
	for(s1=0;s1!=TAILLE;s1++)                            
		for(s=1<<TAILLE-1,s2=0;s2!=TAILLE;s/=2,s2++)
		if(s&nivo[s1])
		t[s1][s2]=1;//je de dechifre les valeur ecrites sur talle bit
	if(TEST)
		verification(t);
	  
		  fclose(niveau);
	  return 1;

}
void translate (int **t)

{
	unsigned int s=0,mask;
	int brak=1,s1,s2;
	FILE* niveau;
	/*donc translate c'est l'oposé de init1 
	il transforme le tableau en donné*/
	niveau=fopen("niveaux/perso","w+");
	for(s1=0;s1!=TAILLE;s1++)                            
		for(s2=0;s2!=TAILLE;s2++)
			if(t[s1][s2]==2 || t[s1][s2]==4 )
				s++;

	fprintf(niveau,"%d,",s);

 	for(s=0,s1=0;s1!=TAILLE;s1++)                            
   {	
		for(mask=1<<TAILLE,s2=0;s2!=TAILLE,mask/=2;s2++)
			if(t[s1][s2]==1)
				s|=mask;
	 fprintf(niveau,"%d,",s);
	 s=0;
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

	for(s1=0;s1!=TAILLE;s1++)                            
		for(s2=0;s2!=TAILLE;s2++)
			if(t[s1][s2]==2||t[s1][s2]==4)
				fprintf(niveau,"(%d,%d),",s1,s2);

	for(s1=0;s1!=TAILLE;s1++)
		for(s2=0;s2!=TAILLE;s2++)
			if(t[s1][s2]==3||t[s1][s2]==4)
				fprintf(niveau,"(%d,%d),",s1,s2);

	for(s1=0;s1!=TAILLE&&brak;s1++)                            
		for(s2=0;s2!=TAILLE&&brak;s2++)
			if(t[s1][s2]==5)
			{
				fprintf(niveau,"(%d,%d),",s1,s2);
				brak=0;
			}

 fclose(niveau);
}
void init1 (int **t,int j,
			SDL_Window *ecran,SDL_Renderer* renderer,SDL_Texture **textures)

{
	int s1=0,s2=0,b=1,k;
	SDL_Rect cadre={0,0,34,34};
	
	SDL_SetRenderDrawColor(renderer,0,0,0,225);
	SDL_RenderClear(renderer);
	/*donc maintenant on a represente tout les TAILLE*PIX*TAILLE*PIX pixel en 144 PIX*PIX
	Voyez ça comme un changement de reper 
	donc la position PIX,PIX
	devent 1,1 ce qui revient a notre tableau de TAILLE*TAILLE 
	wow je suis un genie ruch le boss
	*/
  
	
	for(s1=0;s1!=TAILLE;s1++)
		for(s2=0;s2!=TAILLE;s2++)
		{
		cadre.y=s1*PIX;
		cadre.x=s2*PIX;
		if((2*TAILLE-s1-s2)<0)
		printf("eror");
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

		k=t[s1][s2];
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
