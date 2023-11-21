#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <background.h>
#include <block.h>
#include <brick.h>
#include <buttons.h>
#include <collision.h>
#include <entity.h>
#include <editor.h>
#include <game.h>
#include <global.h>
#include <level.h>
#include <map.h>
#include <menu.h>
#include <methods.h>
#include <mouvement.h>
#include <player.h>
#include <setup.h>
#include <step.h>
#include <target.h>
#include <text.h>
#include <time.h>

char dir2;
bool moving2=false;

void player_const(Player* p, int bi, char d, Entity pl, int xb, int yb, int xv, int yv, int xp, int yp, bool m)
{
	p->block_index=bi;
	p->dir=d;
	p->p=pl;
	p->x_block=xb;
	p->y_block=yb;
	p->x_vel=xv;
	p->y_vel=yv;
	p->x_plus=xp;
	p->y_plus=yp;
	p->moving=m;
}

int main(int argc, char* args[])
{

	load_setup();

	load_entities();

	icon = IMG_Load("img/amoguscon.png");
    SDL_SetWindowIcon(window, icon);

	SDL_SetWindowResizable(window,SDL_FALSE);
	
	player_const(&player,block_index,dir,p,x_block,y_block,x_vel,y_vel,x_plus,y_plus,moving);

	players[0] = player;

	while(running)
	{ 
		switch(game_mode)
		{
			case 'g':
				main_game();
				break;
			case 'm':
				main_menu();
				break;
			case 'e':
				main_editor();
				break;
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}