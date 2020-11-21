#include "utilitaires.h"

int PositionInButtons(Button button, Vector2 position)
{
	return button.cadre.x < position.x &&
		   position.x < button.cadre.x + button.cadre.w + 2 * (button.padin.x + button.margin.x) &&
		   button.cadre.y < position.y && position.y < button.cadre.y + button.cadre.h + 2 * (button.padin.y + button.margin.y);
}
int SDL_SetRenderDrawColorWithColor(SDL_Renderer *renderer, SDL_Color color)
{
	return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}
int NotQuit(SDL_Event event)
{
	if (event.type == SDL_QUIT)
	{
		ApllicationQuit();
		return 0;
	}
	return 1;
}

void ApllicationQuit()
{
	SDL_Window *ecran = GetWindow();
	SDL_Renderer *renderer = SDL_GetRenderer(ecran);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(ecran);
	TTF_Quit();
	SDL_Quit();
}
SDL_Color DimColor(SDL_Color color, int intensity)
{
	color.r *= 0.9;
	color.g *= 0.9;
	color.b *= 0.9;
	if (intensity == 1)
		return color;
	return DimColor(color, intensity - 1);
}
SDL_Color LightenColor(SDL_Color color, int intensity)
{
	color.r *= 1.1;
	color.g *= 1.1;
	color.b *= 1.1;
	if (intensity == 1)
		return color;
	return LightenColor(color, intensity - 1);
}
void ClearScreen()
{
	SDL_Renderer *renderer = SDL_GetRenderer(GetWindow());
	int i;
	if (i < FPS * 1000)
		SDL_Delay(i);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);
	SDL_RenderClear(renderer);
}