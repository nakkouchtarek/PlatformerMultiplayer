#include <SDL2/SDL.h>
#include <stdbool.h>
#include <entity.h>
#include <SDL2/SDL_ttf.h>
#include <player.h>

int elems = 0;
int block_count = 0;
int target_count = 0;
int vel = 2;
int block_vel = 2;
int x_vel = 0;
int y_vel = 0;
int x_block = 0;
int y_block = 0;
int x_plus = 16;
int y_plus = 8;
int score = 0;
int c;
int LEVEL_CAP = 10;
int level = 1;
int last_val_x;
int last_val_y;
int player_count_c=0;
int target_count_c=0;
int block_count_c=0;
int block_index = -1;
int count = -1;
int indexo=0;

double seconds = 0;

SDL_Surface* text;
SDL_Texture* text_texture;

SDL_Event e; 
Uint32 starting_tick;

char dir = 'n';
char game_mode = 'm';
char flag = 'n';
char selected;

bool pressed=false;
bool moving=false;
bool running = true;
bool built = false;
bool editor_built=false;
bool collided=false;

char level_phrase[64] = "Level /";
char score_phrase[64] = "Score /";
char step_count[64] = "Count:";
char time_count[64] = "Time:";
char count_phrase[64] = "Push:";

const char* title = "SOKOBAN2";

Uint64 start_mark;

const int FPS = 60;
const int MAIN_SCREEN_WIDTH = 640;
const int MAIN_SCREEN_HEIGHT = 580;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int x_range = (int)(SCREEN_WIDTH / 32);
const int y_range = (int)(SCREEN_HEIGHT / 32);

SDL_Rect src_fire2 = {0,80,16,16};
SDL_Rect dst_fire2 = {300,300,32,32};
SDL_Rect fire_rect2 = {300,300,10,24};

SDL_Rect text_src = { 0, 0, 32, 32 };
SDL_Rect text_dst = { 0, 0, 32, 32 };

SDL_Rect mouse = {0,0,5,5};

SDL_Rect stone_src = {0,0,SCREEN_WIDTH,MAIN_SCREEN_HEIGHT-SCREEN_HEIGHT};
SDL_Rect stone_dst = {0,SCREEN_HEIGHT,SCREEN_WIDTH,MAIN_SCREEN_HEIGHT-SCREEN_HEIGHT};

SDL_Rect norm = {0,0,32,32};

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font;
SDL_Color color = { 255, 255, 255 };
SDL_Surface* icon;

Entity start;
Entity brick;
Entity tnt;
Entity fire;
Entity p;
Entity background;
Entity background2;
Entity next;
Entity reset;
Entity prev;
Entity stone;
Entity save;
Entity none;
Entity up;
Entity down;
Entity fire2;

Entity map[300] = {0};
Entity targets[255] = {0};
Entity blocks[255] = {0};
Entity elems_to_draw[300] = {0};

Player player;
Player player2;
Player players[2] = {0};

int player_count = 0;