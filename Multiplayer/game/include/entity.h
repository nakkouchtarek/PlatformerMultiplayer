#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct Entity
{
	SDL_Rect src;
	SDL_Rect dst;
	SDL_Rect rect;
	char type;
	SDL_Texture* texture;
}Entity;

void constructor_entity(Entity* e, SDL_Rect* src, SDL_Rect* dst, SDL_Rect* rect, const char* text_name,char type);