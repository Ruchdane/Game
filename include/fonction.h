#ifndef FONCTION_MINIM
#define FONCTION_MINIM

#include <stdio.h>
#include "stdlib.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "fonction.h"
#include "structure.h"
#include "rule.h"
#include "main.h"

SDL_Texture *TextureFromImage(char *title);

void SDL_stop(const char *message, SDL_Texture *texture);

void translate(Level *nivo); //transforme un tableau en donner l'ecrit en memoire voir 'perso'

#endif
