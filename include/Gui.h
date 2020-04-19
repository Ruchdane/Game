#ifndef RUCHDANEGUI
#define RUCHDANEGUI

void renderLevel (Level *niveau,int j,SDL_Window *ecran,SDL_Renderer* renderer,SDL_Texture **textures);
int renderButton(Button button,SDL_Window* window,SDL_Renderer* renderer,TTF_Font *writer,int state);
int menuButton(SDL_Window* window,SDL_Renderer* renderer,int bn,Button *b1, ...);

#endif