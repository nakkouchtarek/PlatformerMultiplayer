#include <SDL2/SDL.h>
#include <global.h>
#include <entity.h>

void constructor_entity(Entity* e, SDL_Rect* src, SDL_Rect* dst, SDL_Rect* rect, const char* text_name, char type)
{
	e->dst = *dst;
	e->src = *src;
	e->rect = *rect;
	e->texture = IMG_LoadTexture(renderer, text_name);
	e->type = type;
}