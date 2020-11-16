#ifndef RUCHDANEGUI
#define RUCHDANEGUI
#include "rule.h"
#include "ini.h"
#include <stdio.h>
#include "stdlib.h"
#include "stdarg.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "structure.h"
#include "main.h"

void renderLevel(Level *niveau, int j,SDL_Texture **textures);
int renderButton(Button button, TTF_Font *writer, int state);
int menuButton(int bn, Button *b1, ...);

#endif