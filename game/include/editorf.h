#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>

void fixpos();
bool check_block_type_file(FILE* fptr, int i, int j);
void save_stuff();
void handle_editor_mouse_click(SDL_Event *e);