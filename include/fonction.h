#ifndef FONCTION_MINIM
#define FONCTION_MINIM

#define PIX 34
#define TAILLE 18
#define TEST 0


SDL_Texture* TextureFromImage(char *title,SDL_Window* window,SDL_Renderer *renderer);

void verification(int **t);//IF TEST

void  SDL_stop(const char *message,SDL_Window* window,SDL_Renderer *renderer,SDL_Texture *texture);



int init0 (int **t,int j);//Charger le niveau j s'il n'y a plus de niveau envoi 0

void translate (int **t);//transforme un tableau en donner l'ecrit en memoire voir 'perso'

void init1 (int **t,int j,
			SDL_Window *ecran,SDL_Renderer* renderer,SDL_Texture **textures);
/*l'un de mes chef-d'oeuvre traduit le tableau en image 
  oh il y'a tros de variable mais pas le temp de l'ameliorer
*/

int action (SDL_Event event,int **t,int j);//modifie le tableau en fonction de l'action /j c'ast pour la direction de mario/



void print(SDL_Window *ecran ,SDL_Renderer *renderer,char s[],int c,int s1,int s2);//de ruchdane per met d'ecrire en 1=firegold 0=blanc a la positin (s1 s2)

#endif



