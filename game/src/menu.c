#include <SDL2/SDL_ttf.h>

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

SDL_Rect text_rect1 = {200,300,225,75};
SDL_Rect text_rect2 = {200,400,220,50};
SDL_Rect text_rect3 = {200,450,220,50};

void main_menu()
{
	while( SDL_PollEvent( &e ) )
	{
		if(e.type==SDL_QUIT)
				running = false;
		else if(e.type==SDL_MOUSEMOTION)
		{
			mouse.x = e.button.x;
			mouse.y = e.button.y;
		}
		else if(e.type==SDL_MOUSEBUTTONDOWN)
		{
			if(SDL_HasIntersection(&mouse,&text_rect1))
			{
				hard_reset();
				game_mode = 'g';
			}
			else if(SDL_HasIntersection(&mouse,&text_rect2))
			{
				hard_reset();
				game_mode = 'e';
			}
			else if(SDL_HasIntersection(&mouse,&text_rect3))
			{
				hard_reset();
				game_mode = 'c';
			}
		}
			
	}
	
	// clear renderer
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	SDL_RenderClear(renderer);

	draw(&background2);
	
	draw_text("SOKOBAN",100,100,450,128);

	draw_text("PLAY",200,300,225,75);

	draw_text("LEVEL EDITOR",200,400,220,50);

	draw_text("MULTIPLAYER",200,450,220,50);

	SDL_RenderPresent(renderer);

}