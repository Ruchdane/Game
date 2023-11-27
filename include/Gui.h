#ifndef RUCHDANEGUI
#define RUCHDANEGUI
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "rule.h"
#include "ini.h"
#include "structure.h"
#include "main.h"
#include "utilitaires.h"

void renderLevel(Level *niveau, int j, SDL_Texture **textures);
int renderButton(Button button, TTF_Font *writer, int state);
int menuButton(int bn, Button **B);

#endif