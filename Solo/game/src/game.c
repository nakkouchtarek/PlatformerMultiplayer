#include <SDL2/SDL.h>
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
#include <score.h>
#include <setup.h>
#include <step.h>
#include <target.h>
#include <text.h>
#include <time.h>

void draw_text_main()
{
	draw_text(level_phrase,5,520,128,24);
	draw_text(score_phrase,5,490,128,24);
	draw_text(step_count, 5, 550, 128, 24);
	draw_text(time_count, 170, 500, 128, 24);
	draw_text(count_phrase , 170, 530, 128, 24);
}

void draw_buttons()
{
	draw(&next);
	draw(&prev);
	draw(&reset);
}

void main_game()
{
	starting_tick = SDL_GetTicks();

	if(!built)
	{
		change_level();
		change_score();
		build_map(level);
		
		if(target_count==0)
		{
			hard_reset();
			game_mode='m';
		}
		else
			built=true;
	}

	while( SDL_PollEvent( &e ) )
	{
		if(e.type==SDL_QUIT)
				running = false;
		else if (e.type == SDL_KEYDOWN && pressed==false) 
		{
			player_mouvement(&e,&player);
		}
		else if(e.type== SDL_KEYUP && pressed==true)
		{	
			player_stop_mouvement(&e,&player);
		}
		else if(e.type==SDL_MOUSEMOTION)
		{
			mouse.x = e.button.x;
			mouse.y = e.button.y;
		}
		else if(e.type==SDL_MOUSEBUTTONDOWN)
		{
			if(SDL_HasIntersection(&mouse,&next.dst))
			{
				advance_level();
			}
			else if(SDL_HasIntersection(&mouse,&reset.dst))
			{
				reset_level();
			}
			else if(SDL_HasIntersection(&mouse,&prev.dst))
			{
				downgrade_level();
			}
		}
	}

		// clear renderer of color
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		// clear renderer
		SDL_RenderClear(renderer);

		// checks collision
		collision(&player);	

		// handle score
		score_func();

		// check if you won
		check_win();

		// move rect of fire
		target_rect_move();

		// calculate each 32 block passed
		keep_step_count();
		keep_block_count();

		// change vel of objects that get affected by mouvement
		dir_change_vel(&player);
		
		// handle velocity
		velocity(&player);
		
		// draw map and elems and player
		draw_map();

		// draw text
		draw_text_main();

		// draw buttons
		draw_buttons();

		// Present rendered objects
		SDL_RenderPresent(renderer);

		// calculate time passed
		seconds+=((SDL_GetTicks() - starting_tick) / 1000.0);
		change_time();
}