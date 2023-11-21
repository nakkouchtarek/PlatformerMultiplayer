#pragma once
#include <SDL2/SDL.h>

extern Entity p2;
extern char dir2;

#include <global.h>
#include <player.h>

void velocity(Player *p);
void dir_change_vel(Player* p);
void reset_player_vel(Player* p);
void player_mouvement(SDL_Event *e, Player* p);
void player_stop_mouvement(SDL_Event *e, Player* p);

