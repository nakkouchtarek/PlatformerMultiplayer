#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <stdio.h>

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
#include <editorf.h>

// reposition entities to fit button place
void fixpos()
{
	p.dst.x = 50;
	p.dst.y = 500;
	p.src.y=0;
	p.src.x=140;
	p.rect = p.dst;
	p.dst.x = 68;
	p.dst.y = 511;
	p.rect.w = 64;
	p.rect.h = 64;
	SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_RenderFillRect( renderer, &p.rect );
	draw(&p);

	tnt.dst.x = 140;
	tnt.dst.y = 500;
	tnt.rect = tnt.dst;
	tnt.dst.x = 140+15;
	tnt.dst.y = 520;
	tnt.rect.w = 64;
	tnt.rect.h = 64;
	SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
	SDL_RenderFillRect( renderer, &tnt.rect );
	draw(&tnt);

	fire2.dst.x = 230;
	fire2.dst.y = 500;
	fire2.rect = fire2.dst;
	fire2.dst.x = 230+15;
	fire2.dst.y = 510;
	fire2.rect.w = 64;
	fire2.rect.h = 64;
	SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
	SDL_RenderFillRect( renderer, &fire2.rect );
	draw(&fire2);

	brick.dst.x = 320;
	brick.dst.y = 500;
	brick.rect = brick.dst;
	brick.dst.x = 320+15;
	brick.dst.y = 515;
	brick.rect.w = 64;
	brick.rect.h = 64;
	SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
	SDL_RenderFillRect( renderer, &brick.rect );
	draw(&brick);
}

bool check_block_type_file(FILE* fptr, int i, int j)
{
	for(short t=0;t<indexo;t++)
	{
		if(elems_to_draw[t].dst.x == 32*i && elems_to_draw[t].dst.y == 32*j)
		{
			switch(elems_to_draw[t].type)
			{
				case 'c':
					fprintf(fptr,"1",elems_to_draw[i].type);
					break;
				case 'p':
					fprintf(fptr,"P",elems_to_draw[i].type);
					break;
				case 't':
					fprintf(fptr,"T",elems_to_draw[i].type);
					break;
				case 'f':
					fprintf(fptr,"F",elems_to_draw[i].type);
					break;
			}
			
			return true;
		}
	}

	return false;
}

void save_stuff()
{
	char str[10] = "lvls/lvl";
	char tmp = level + '0';

	if(level==10)
		tmp='a';
	
    strncat(str, &tmp, 1);

	FILE *fptr = fopen(str,"w+");

	for(int i=0;i<y_range;i++)
	{
		for(int j=0;j<x_range;j++)
		{
			if(!check_block_type_file(fptr,j,i))
			{
				fprintf(fptr," ");
			}
		}

		fprintf(fptr,"\n");
	}

	fclose(fptr);

	printf("Saved!");
}

void handle_editor_mouse_click(SDL_Event *e)
{
	if(e->button.button == SDL_BUTTON_LEFT )
			{

				if(SDL_HasIntersection(&mouse,&p.rect))
				{
					selected='p';
				}
				else if(SDL_HasIntersection(&mouse,&tnt.rect))
				{
					selected='t';
				}
				else if(SDL_HasIntersection(&mouse,&fire2.rect))
				{
					selected='f';
				}
				else if(SDL_HasIntersection(&mouse,&brick.rect))
				{
					selected='m';
				}else if(SDL_HasIntersection(&mouse,&save.dst))
				{
					if(target_count_c>0&&player_count_c>0&&target_count_c==block_count_c)
						save_stuff();
					else
						printf("Recheck\n");
				}
				else if(SDL_HasIntersection(&mouse,&up.dst))
				{
					level++;

					if(level<=LEVEL_CAP)
					{
						editor_built=false;
					}
					else
					{
						printf("LEVEL LIMIT REACHED\n");
						level--;
					}
				}
				else if(SDL_HasIntersection(&mouse,&down.dst))
				{
					level--;

					if(level != 0)
					{
						editor_built=false;
					}
					else
					{
						level++;
					}
				}
				else
				{
					collided=false;

					for(short i=0;i<indexo;i++)
					{
						if(SDL_HasIntersection(&mouse,&elems_to_draw[i].dst))
						{
							collided=true;
						}
					}
					
					if(!collided)
					{
						if(selected=='p' && player_count_c==0)
						{
							p.dst.x = 32*(mouse.x*x_range/SCREEN_WIDTH);
							p.dst.y = 32*(mouse.y*y_range/SCREEN_HEIGHT);
							elems_to_draw[indexo] = p;
							indexo++;
							player_count_c++;
						}
						else if(selected=='t')
						{
							tnt.dst.x = 32*(mouse.x*x_range/SCREEN_WIDTH);
							tnt.dst.y = 32*(mouse.y*y_range/SCREEN_HEIGHT);
							elems_to_draw[indexo] = tnt;
							block_count_c++;
							indexo++;
						}
						else if(selected=='f')
						{
							fire.dst.x = 32*(mouse.x*x_range/SCREEN_WIDTH);
							fire.dst.y = 32*(mouse.y*y_range/SCREEN_HEIGHT);
							elems_to_draw[indexo] = fire;
							target_count_c++;
							indexo++;
						}
						else if(selected=='m')
						{
							brick.dst.x = 32*(mouse.x*x_range/SCREEN_WIDTH);
							brick.dst.y = 32*(mouse.y*y_range/SCREEN_HEIGHT);
							elems_to_draw[indexo] = brick;
							indexo++;
						}
					}
				}
			}
			else if(e->button.button == SDL_BUTTON_RIGHT)
			{
				for(short i=0;i<indexo;i++)
				{
					if(SDL_HasIntersection(&mouse,&elems_to_draw[i].dst))
					{
						switch(elems_to_draw[i].type)
						{
							case 'p':
								player_count_c=0;
								break;
							case 'f':
								target_count_c--;
								break;
							case 't':
								block_count_c--;
								break;
						}

						memset(&elems_to_draw[i], 0, sizeof(Entity));
					}
				}
			}
}