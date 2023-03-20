#include <SDL2/SDL.h>
#include <entity.h>
#include <block.h>
#include <global.h>

SDL_Rect player_src = {
		.x=0,
		.y=0,
		.w=140,
		.h=140
};

SDL_Rect player_dst = {
    .x=150,
    .y=150,
    .w=64,
    .h=64
};

SDL_Rect player_rect = {
    .w=1,
    .h=1
};