#ifndef RUCHDANERULES
#define RUCHDANERULES

int nohomo(int z,int limit);//permet de régulariser les nombre

void verification(Level *niveau);//IF TEST
int estMouvement(SDL_Event event);
int estAnnulation(SDL_Event event);
void annuler(int *j,Level *niveau,int k,Pile *actions);
int estQuiter(SDL_Event event);
int estRecommencer(SDL_Event event);
int judge(int *k,Level *niveau,int key,Pile *action);
#endif