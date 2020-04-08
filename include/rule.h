#ifndef RUCHDANERULES
#define RUCHDANERULES
#define TAILLE 18

int nohomo(int z);//permet de régulariser les nombre
int win (int **t);//regarde s'il n'y a plus de perle
int estMouvement(SDL_Event event);
int estAnnulation(SDL_Event event);
void annuler(int *j,int ***t,int k,Pile *actions);
int estQuiter(SDL_Event event);
int estRecommencer(SDL_Event event);
int judge(int *k,int **t,int key,Pile *action);
#endif