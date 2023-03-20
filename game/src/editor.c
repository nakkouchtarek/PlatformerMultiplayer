#include <SDL2/SDL_ttf.h>
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
#include <scode.h>
#include <setup.h>
#include <step.h>
#include <target.h>
#include <text.h>
#include <time.h>
#include <editorf.h>

void main_editor()
{
	if(!editor_built)
	{
		change_level();
		build_map_v2(level);
		editor_built=true;
	}

	while( SDL_PollEvent( &e ) )
	{
		if(e.type==SDL_QUIT)
				running = false;
        else if (e.type == SDL_KEYDOWN) 
		{
			switch(e.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				{
					hard_reset();
					game_mode = 'm';
					break;
				}
            }
	    }
		else if(e.type==SDL_MOUSEMOTION)
		{
			mouse.x = e.button.x;
			mouse.y = e.button.y;
		}
		else if(e.type==SDL_MOUSEBUTTONDOWN)
		{
			handle_editor_mouse_click(&e);
		}
    }
	
	// clear renderer
	p.dst.w = 32;
	p.dst.h = 32;

	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	SDL_RenderClear(renderer);

	draw_editor();

	// position and draw buttons
	fixpos();
	
	SDL_RenderPresent(renderer);

}