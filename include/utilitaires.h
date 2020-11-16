#ifndef RUCHDANEUTIL
#define RUCHDANEUTIL
#include <stdio.h>
#include "stdlib.h"
#include "SDL.h"
#include "structure.h"
#include "main.h"
int PositionInButtons(Button button, Vector2 position);
int SDL_SetRenderDrawColorWithColor(SDL_Renderer *renderer, SDL_Color color);
int NotQuit(SDL_Event event);
void ApllicationQuit();
SDL_Color DimColor(SDL_Color color, int intensity);
SDL_Color LightenColor(SDL_Color color, int intensity);
void ClearScreen();
#endif