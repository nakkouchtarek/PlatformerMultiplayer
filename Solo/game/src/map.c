#include <SDL2/SDL.h>
#include <stdio.h>
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
#include <score.h>
#include <setup.h>
#include <step.h>
#include <target.h>
#include <text.h>
#include <time.h>
#include <editorf.h>

void add_target(int x, int y)
{
	fire.dst.x = x;
	fire.dst.y = y;
	targets[target_count] = fire;
	target_count++;
}

void add_block(int x, int y)
{
	tnt.dst.x = x;
	tnt.dst.y = y;
	blocks[block_count] = tnt;
	block_count++;
}

void build_map(int lvl)
{
	block_count=0;
	elems=0;
	target_count=0;

	char str[10] = "lvls/lvl";
	char tmp = lvl + '0';

	if(lvl==10)
		tmp='a';
	
    strncat(str, &tmp, 1);

	FILE *fptr = fopen(str,"r");

	int x=0;
	int y=0;
	char ch;
	
	do {
		ch = fgetc(fptr);
		if(ch=='1')
		{
			brick.dst.x = 32*x;
			brick.dst.y = 32*y;
			map[elems] = brick;
			elems++;
			x++;
		}
		else if(ch=='\n')
		{
			y++;
			x=0;
		}
		else if(ch=='T')
		{
			add_block(32*x,32*y);
			x++;
		}
		else if(ch=='F')
		{		
			add_target(32*x,32*y);
			x++;
		}
		else if(ch=='P')
		{
			player.p.dst.x = 32*x;
			player.p.dst.y = 32*y;
			player.p.src.y=0;
			player.p.src.x=140;
			player2.p.dst.x = 32*x;
			player2.p.dst.y = 32*y;
			player2.p.src.y=0;
			player2.p.src.x=140;
			x++;
		}
		else
		{
			x++;
		}

	} while (ch != EOF);
	fclose(fptr);

	change_score();
	change_level();
}

void draw_rect(SDL_Rect* r)
{
	// set renderer color to r,g,b alpha to 255 for clarity
	SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );

	// Draw non filled rect
	SDL_RenderDrawRect(renderer, r);
}

void draw(Entity* s)
{
	//draw_rect(renderer, &s->dst);	
	SDL_RenderCopy(renderer, s->texture, &s->src, &s->dst);
}

void draw_player()
{
	if(player.moving)
		player.p.src.x = ((starting_tick / 100) % 3) * 140;

	if(player2.moving)
		player2.p.src.x = ((starting_tick / 100) % 3) * 140;

	draw(&player.p);
}

void draw_map()
{

	draw(&background);

	for(short i=0;i<elems;i++)
		draw(&map[i]);

	for(short i=0;i<target_count;i++)
	{
		draw(&targets[i]);
		//draw_rect(renderer, &targets[i].rect);
	}

	for(short i=0;i<block_count;i++)
	{
		draw(&blocks[i]);
		//draw_rect(renderer, &blocks[i].rect);
	}

	draw_player();
}

void build_map_v2(int lvl)
{

	memset(elems_to_draw, 0, sizeof(*elems_to_draw));

	indexo=0;
    player_count_c=0;
	target_count_c=0;
	block_count_c=0;

	char str[10] = "lvls/lvl";
	char tmp = lvl + '0';

	if(lvl==10)
		tmp='a';
	
    strncat(str, &tmp, 1);

	FILE *fptr = fopen(str,"r");

	int x=0;
	int y=0;
	char ch;
	p.dst.w = 32;
	p.dst.h = 32;
	
	do {
		ch = fgetc(fptr);
		if(ch=='1')
		{
			brick.dst.x = 32*x;
			brick.dst.y = 32*y;
			elems_to_draw[indexo] = brick;
			indexo++;
			x++;
		}
		else if(ch=='\n')
		{
			y++;
			x=0;
		}
		else if(ch=='T')
		{
			tnt.dst.x = 32*x;
			tnt.dst.y = 32*y;
			elems_to_draw[indexo] = tnt;
			block_count_c++;
			indexo++;
			x++;
		}
		else if(ch=='F')
		{		
			fire.dst.x = 32*x;
			fire.dst.y = 32*y;
			elems_to_draw[indexo] = fire;
			target_count_c++;
			indexo++;
			x++;
		}
		else if(ch=='P')
		{
			p.dst.x = 32*x;
			p.dst.y = 32*y;
			p.src.y=0;
			p.src.x=140;
			elems_to_draw[indexo] = p;
			indexo++;
			player_count_c++;
			x++;
		}
		else
		{
			x++;
		}

	} while (ch != EOF);
	fclose(fptr);
}

void draw_grid()
{
	for(short i=0;i<x_range;i++)
	{
		norm.x = 32*i;
		norm.y = 0;
		norm.h = SCREEN_HEIGHT;
		draw_rect(&norm);
	}

	for(short i=0;i<y_range;i++)
	{
		norm.x = 0;
		norm.y = 32*i;
		norm.w = SCREEN_WIDTH;
		draw_rect(&norm);
	}
}

void draw_editor()
{
	draw(&background);

	draw_grid();

	draw(&stone);

	for(short i=0;i<indexo;i++)
	{
		draw(&elems_to_draw[i]);
	}

	draw(&save);
	draw(&up);
	draw(&down);

	draw_text(level_phrase,475,545,156,24);
}