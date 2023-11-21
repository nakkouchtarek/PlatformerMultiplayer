#include <SDL2/SDL.h>
#include <stdio.h>
#include <global.h>
#include <entity.h>
#include <player.h>

// Check if block collides with map
bool check_block_map_collision(Entity* block, Player* p)
{
	for(short i=0;i<elems;i++)
	{
		if(SDL_HasIntersection(&map[i].dst,&block->rect))
			return true;
	}

    for(short i=0;i<block_count;i++)
	{
		if(i!=p->block_index && SDL_HasIntersection(&blocks[i].dst,&block->rect))
			return true;
	}

	return false;
}

// check for collision with each tnt on map
// to avoid double condition in loop we add bool var
// after loop it checks if collided else we nullify mouvement
void player_block_collision(Player* p)
{
	bool player_col=false;

	for(short i=0;i<block_count;i++)
	{
		if(SDL_HasIntersection(&p->p.rect,&blocks[i].dst))
		{
			p->block_index=i;
			
			if(!check_block_map_collision(&blocks[i],p))
			{
				player_col=true;
				p->block_index = i;
				switch(p->dir)
				{
					case 'l':
						p->x_block = -block_vel;
						break;
					case 'r':
						p->x_block = block_vel;
						break;
					case 'u':
						p->y_block = -block_vel;
						break;
					case 'd':
						p->y_block = block_vel;
						break;
				}
			}
			else
			{
				p->x_vel=0;
				p->y_vel=0;
			}
		}
	}

	if(!player_col)
	{
		p->block_index=-1;
		p->x_block=0;
		p->y_block=0;
	}
}

// check for collision with each brick on map
void player_map_collision(Player* p)
{
	for(short i=0;i<elems;i++)
	{
		if(SDL_HasIntersection(&p->p.rect, &map[i].dst))
		{
			p->x_vel = 0;
			p->y_vel = 0;
		}
	}
}

// main collision per player
void collision(Player* p)
{
    player_block_collision(p);
    player_map_collision(p);
}