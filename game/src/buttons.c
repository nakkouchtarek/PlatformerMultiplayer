#include <SDL2/SDL.h>

// Next button

SDL_Rect next_src = {
    .x=0,
    .y=0,
    .w=420,
    .h=170
};
SDL_Rect next_dst =
{
    .x=520,
    .y=495,
    .w=128,
    .h=64
};

// Reset Button

SDL_Rect reset_src = {
    .x=0,
    .y=0,
    .w=330,
    .h=300
};
SDL_Rect reset_dst =
{
    .x=418,
    .y=463,
    .w=110,
    .h=125
};

SDL_Rect prev_src = {
    .x=0,
    .y=0,
    .w=400,
    .h=200
};

// Previous button

SDL_Rect prev_dst =
{
    .x=300,
    .y=495,
    .w=128,
    .h=64
};

// Save button

SDL_Rect save_src = {0,0,420,170};
SDL_Rect save_dst = {490,475,128,64};

// Up button

SDL_Rect up_src = {192,48,16,16};
SDL_Rect up_dst = {435,495,32,32};

// Down button

SDL_Rect down_src = {208,48,16,16};
SDL_Rect down_dst = {435,540,32,32};

