#include <global.h>
#include <player.h>
#include <stdio.h>
#include <methods.h>

// main velocity function
void velocity(Player *p)
{
	p->p.dst.x += p->x_vel;
	p->p.dst.y += p->y_vel;

	p->p.rect.x = p->p.dst.x + p->x_plus;
	p->p.rect.y = p->p.dst.y + p->y_plus;

	if(p->block_index!=-1)
	{
		blocks[p->block_index].dst.x += p->x_block;
		blocks[p->block_index].dst.y += p->y_block;
	}
}

void dir_change_vel(Player* p)
{
	// Change player rect depending on his direction
	switch(p->dir)
	{
		case 'd':
			p->y_plus = 55;
			p->x_plus = 14;
			p->p.rect.w = 30;
			p->p.rect.h = 1;
			break;
		case 'u':
			p->y_plus = 12;
			p->x_plus = 14;
			p->p.rect.w = 30;
			p->p.rect.h = 1;	
			break;
		case 'l':
			p->y_plus = 18;
			p->x_plus = 10;
			p->p.rect.w = 1;
			p->p.rect.h = 36;
			break;
		case 'r':
			p->y_plus = 18;
			p->x_plus = 45;
			p->p.rect.w = 1;
			p->p.rect.h = 36;
			break;
		case 'n':
			p->x_plus = 32;
			p->y_plus = 32;
			p->p.rect.w = 1;
			p->p.rect.h = 1;
			break;
	}

	// change blocks hitbox depending on player direction
	for(int i=0;i<block_count;i++)
    {
        blocks[i].rect = blocks[i].dst;

        switch(p->dir)
        {
            case 'l':
                blocks[i].rect.w = 1;
                blocks[i].rect.h = 26;
                blocks[i].rect.y = blocks[i].dst.y + 2;
				blocks[i].rect.x = blocks[i].dst.x - 4;
                break;
            case 'r':
                blocks[i].rect.w = 1;
                blocks[i].rect.h = 26;
                blocks[i].rect.x = blocks[i].dst.x + 32;
                blocks[i].rect.y = blocks[i].dst.y + 2;
                break;
            case 'u':
                blocks[i].rect.w = 26;
                blocks[i].rect.h = 1;
                blocks[i].rect.x = blocks[i].dst.x + 2;
				blocks[i].rect.y = blocks[i].dst.y - 4;
                break;
            case 'd':
                blocks[i].rect.w = 26;
                blocks[i].rect.h = 1;
                blocks[i].rect.y = blocks[i].dst.y + 32;
                blocks[i].rect.x = blocks[i].dst.x + 2;
                break;
        }
    }
}

// reset player velocity values
void reset_player_vel(Player* p)
{
	p->x_plus=0;
	p->y_plus=0;
	p->x_vel=0;
	p->y_vel=0;
}

// mouvement when key is down
void player_mouvement(SDL_Event *e, Player* p)
{
	pressed=true;

	switch(e->key.keysym.sym)
	{
	case SDLK_UP:
	{
		p->moving=true;
		p->p.src.y=420;
		p->y_vel = -vel;
		p->dir='u';
		break;
	}
	case SDLK_DOWN:
	{
		p->moving=true;
		p->p.src.y=0;
		p->y_vel = vel;
		p->dir='d';
		break;
	}
	case SDLK_LEFT:
	{
		p->moving=true;
		p->p.src.y=140;
		p->x_vel = -vel;
		p->dir='l';
		break;
	}
	case SDLK_RIGHT:
	{
		p->moving=true;
		p->p.src.y=280;
		p->x_vel = vel;
		p->dir='r';
		break;
	}
	case SDLK_ESCAPE:
		//pressed=false;
		hard_reset();
		game_mode = 'm';
		break;
	}
}

// stop mouvement when key is up
void player_stop_mouvement(SDL_Event *e, Player* p)
{
	pressed=false;

	if (e->key.keysym.sym == SDLK_UP || e->key.keysym.sym == SDLK_DOWN)
	{
		p->moving=false;
		p->dir = 'n';
		p->p.src.x=140;
		p->y_vel=0;
		
	}
	else if (e->key.keysym.sym == SDLK_LEFT || e->key.keysym.sym == SDLK_RIGHT)
	{
		p->moving=false;
		p->dir='n';
		p->p.src.x=140;
		p->x_vel=0;
	}
}
