#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

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
#include <scode.h>
#include <setup.h>
#include <step.h>
#include <target.h>
#include <text.h>
#include <time.h>
#include <step.h>

void GetSDLError(char* string)
{
	printf("%s || Error: %s\n", string, SDL_GetError());
}

// Check if all tnts are on targets
void check_win()
{
	if(score==target_count)
	{
		if(level>LEVEL_CAP)
		{
			hard_reset();
			game_mode='m';
		}
		else
		{
			advance_level();
		}
		
	}
}

// Reset our display phrases
void hard_reset_phrases()
{
	for(short i=0;i<3;i++)
	{
		step_count[6+i] = 0;
	}

	for(short i=0;i<3;i++)
	{
		time_count[6+i] = 0;
	}

	for(short i=0;i<3;i++)
	{
		count_phrase[6+i] = 0;
	}
}

// Reset variables
void hard_reset()
{
	memset(map, 0, sizeof(*map));
	memset(targets, 0, sizeof(*targets));
	memset(blocks, 0, sizeof(*blocks));
	memset(elems_to_draw, 0, sizeof(*elems_to_draw));
	level=1;
	score=0;
	seconds=0;
	count=-1;
	target_count=0;
	block_count=0;
	block_count_r=0;
	player.p.dst.w = 64;
	player.p.dst.h = 64;
	player.x_plus=0;
	player.y_plus=0;
	player.x_vel=0;
	player.y_vel=0;
	hard_reset_phrases();
	change_bc();
	player.moving=false;
	pressed=false;
	built=false;
	editor_built=false;
}