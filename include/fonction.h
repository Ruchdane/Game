#ifndef FONCTION_MINIM
#define FONCTION_MINIM

#define PIX 34
#define TEST 0
#include "structure.h"

SDL_Texture* TextureFromImage(char *title,SDL_Window* window,SDL_Renderer *renderer);



void  SDL_stop(const char *message,SDL_Window* window,SDL_Renderer *renderer,SDL_Texture *texture);



void translate (Level *nivo);//transforme un tableau en donner l'ecrit en memoire voir 'perso'


#endif



