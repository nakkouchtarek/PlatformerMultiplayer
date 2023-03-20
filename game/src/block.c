#include <SDL2/SDL.h>
#include <stdio.h>
#include <global.h>
#include <entity.h>
#include <stdbool.h>

SDL_Rect src_tnt = {
    .x=128,
    .y=0,
    .w=16,
    .h=16
};

SDL_Rect dst_tnt = {
    .x=300,
    .y=300,
    .w=32,
    .h=32
};