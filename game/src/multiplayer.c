#include <SDL2/SDL_ttf.h>
#include <pthread.h>

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
#include <score.h>
#include <client.h>
#include <multiplayer.h>

bool created=false;
Entity p2;

void setup_multi()
{
    if(!created)
    {
        pthread_t thread;
        pthread_create(&thread, NULL, main_client, NULL);
        created=true;
    }
}

void player2_dir(Player* p)
{
	switch(p->dir)
	{
		case 'u':
		{
			p->p.src.y=420;
			break;
		}
		case 'd':
		{
			p->p.src.y=0;
			break;
		}
		case 'l':
		{
			p->p.src.y=140;
			break;
		}
		case 'r':
		{
			p->p.src.y=280;
			break;
		}
		case 'n':
			p->p.src.x=140;
			p->y_vel=0;
			break;
	}
}

void game()
{
	if(connected)
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
					if(e.key.keysym.sym == SDLK_ESCAPE)
					{
						closesocket(s);
						WSACleanup();
						hard_reset();
						game_mode = 'm';
					}
					
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
						//advance_level();
						player.vote++;
						player.flag='a';
					}
					else if(SDL_HasIntersection(&mouse,&reset.dst))
					{
						//reset_level();
						player.vote++;
						player.flag='r';
					}
					else if(SDL_HasIntersection(&mouse,&prev.dst))
					{
						//downgrade_level();
						player.vote++;
						player.flag='d';
					}
				}
			}

			// clear renderer of color
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

			// clear renderer
			SDL_RenderClear(renderer);

			// handle score
			score_func();

			// check if you won
			check_win();

			// move rect of fire
			target_rect_move();

			// calculate each 32 block passed
			keep_step_count();
			keep_block_count();

			// send coords
			send_coords();

			// change vel of objects that get affected by mouvement
			dir_change_vel(&player);

			if(player.vote!=0 && player.vote == player2.vote)
			{
				if(player.flag == player2.flag)
				{
					switch(player.flag)
					{
						case 'a':
							advance_level();
							break;
						case 'r':
							reset_level();
							break;
						case 'd':
							downgrade_level();
							break;
					}
				}
				
				player.vote=0;
				player2.vote=0;
			}
			
			// handle velocity
			velocity(&player);
			velocity(&player2);

			// checks collision
			collision(&player);
			collision(&player2);	
			
			player2_dir(&player2);

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
	else
	{
		while( SDL_PollEvent( &e ) )
			{
				if(e.type==SDL_QUIT)
						running = false;
					
			}
	
		// clear renderer
		SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
		SDL_RenderClear(renderer);
		
		draw_text("WAITING FOR PLAYERS",65,250,550,64);

		SDL_RenderPresent(renderer);

	}
}

void multiplayer()
{
    setup_multi();
    game();
}