#pragma once
#include <SDL2/SDL.h>
#include <entity.h>

void draw_rect(SDL_Rect* r);
void draw(Entity* s);
void draw_map();
void draw_player();
void add_target(int x, int y);
void add_block(int x, int y);
void build_map(int lvl);
void build_map_v2(int lvl);
void draw_grid();
void draw_editor();