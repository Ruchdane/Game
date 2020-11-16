#ifndef RUCHDANERULES
#define RUCHDANERULES
#define TEST 0
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "structure.h"
#include "rule.h"
#include "fonction.h"
#include "Gui.h"
#include "main.h"

int nohomo(int z, int limit); //permet de régulariser les nombre

void verification(Level *niveau); //IF TEST
int estMouvement(SDL_Event event);
int estAnnulation(SDL_Event event);
void annuler(int *j, Level *niveau, int k, Pile *actions);
int estQuiter(SDL_Event event);
int estRecommencer(SDL_Event event);
int judge(int *k, Level *niveau, int key, Pile *action);
#endif