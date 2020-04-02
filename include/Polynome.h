#ifndef POLYNOMES$
#define POLYNOMES$

int menu (SDL_Window *ecran,SDL_Renderer* renderer );//Un menu qui renvoie le nombre selectioner

int menu1 (int k, SDL_Window *ecran,SDL_Renderer* renderer );//second menu meme chose

void jouer( SDL_Window *ecran,SDL_Renderer* renderer ,SDL_Texture **textures ,int k);//eh bein jouer ;prend le niveau requis

void niveau(SDL_Window *ecran,SDL_Renderer* renderer ,SDL_Texture **textures);//edite les niveau

#endif

