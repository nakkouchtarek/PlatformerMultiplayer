#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <entity.h>
#include <player.h>

extern int elems;
extern int block_count;
extern int target_count;
extern int vel;
extern int block_vel;
extern int x_vel;
extern int y_vel;
extern int x_block;
extern int y_block;
extern int x_plus;
extern int y_plus;
extern int indexo;
extern int player_count_c;
extern int target_count_c;
extern int block_count_c;
extern int count;
extern int MAX_LEVEL_CAP;
extern int block_index;
extern int score;
extern int c;
extern int level;
extern int last_val_x;
extern int last_val_y;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;
extern SDL_Color color;
extern SDL_Surface* text;
extern SDL_Texture* text_texture;
extern SDL_Rect text_src;
extern SDL_Rect text_dst;
extern SDL_Rect mouse;
extern SDL_Rect stone_src;
extern SDL_Rect stone_dst;
extern SDL_Rect src_fire2;
extern SDL_Rect dst_fire2;
extern SDL_Rect fire_rect2;
extern SDL_Event e;
extern SDL_Rect norm;
extern SDL_Surface* icon;

extern char dir;
extern char game_mode;
extern char selected;
extern char flag;

extern char score_phrase[];
extern char level_phrase[];
extern char step_count[];
extern char time_count[];
extern char count_phrase[];

extern bool pressed;
extern bool moving;
extern bool running;
extern bool built;
extern bool editor_built;
extern bool collided;

extern double seconds;

extern const int LEVEL_CAP;
extern const int FPS;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int MAIN_SCREEN_WIDTH;
extern const int MAIN_SCREEN_HEIGHT;
extern const int x_range;
extern const int y_range;
extern const int max;
extern const char* title;

extern Uint32 starting_tick;

extern Entity start;
extern Entity brick;
extern Entity tnt;
extern Entity fire;
extern Entity p;
extern Entity background;
extern Entity background2;
extern Entity next;
extern Entity reset;
extern Entity prev;
extern Entity stone;
extern Entity save;
extern Entity none;
extern Entity up;
extern Entity down;
extern Entity fire2;

extern Entity map[];
extern Entity targets[];
extern Entity blocks[];
extern Entity elems_to_draw[];

extern Player player;
extern Player player2;
extern Player players[2];

extern int player_count;
