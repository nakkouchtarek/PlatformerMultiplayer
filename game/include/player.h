#pragma once
#include <SDL2/SDL.h>
#include <entity.h>

extern SDL_Rect player_src;
extern SDL_Rect player_dst;
extern SDL_Rect player_rect;

typedef struct Player
{
    Entity p;
    int block_index;
    char dir;
    bool moving;
    int x_vel;
    int y_vel;
    int x_plus;
    int y_plus;
    int x_block;
    int y_block;
    int vote;
    char flag;
}Player;