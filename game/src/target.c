#include <SDL2/SDL.h>
#include <global.h>

SDL_Rect src_fire = {
    .x=0,
    .y=80,
    .w=16,
    .h=16
};

SDL_Rect dst_fire = {
    .x=300,
    .y=300,
    .w=32,
    .h=32
};

SDL_Rect fire_rect = {
    .x=300,
    .y=300,
    .w=10,
    .h=24
};

// change the target's hitbox
void target_rect_move()
{
    for(short i=0;i<target_count;i++)
    {
        targets[i].rect.x = targets[i].dst.x + 11;
        targets[i].rect.y = targets[i].dst.y + 10;
    }
}