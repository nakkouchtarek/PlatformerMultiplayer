#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <global.h>
#include <methods.h>
#include <target.h>
#include <player.h>
#include <brick.h>
#include <block.h>
#include <background.h>
#include <buttons.h>

void load_setup()
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		GetSDLError("Failed to init SDL");
	}

	if ( TTF_Init() < 0 ) 
	{
		GetSDLError("Error initializing SDL_ttf: ");
	}

	font = TTF_OpenFont("fonts/minecraft.ttf", 24);

	if ( !font ) 
	{
		GetSDLError("Failed to load font: ");
	}

	window = SDL_CreateWindow( title, 
								SDL_WINDOWPOS_UNDEFINED, 
								SDL_WINDOWPOS_UNDEFINED, 
								MAIN_SCREEN_WIDTH, 
								MAIN_SCREEN_HEIGHT, 
								SDL_WINDOW_RESIZABLE 
							);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	if( window == NULL )
	{
		GetSDLError("Failed to create window");
	}

	if( renderer == NULL )
	{
		GetSDLError("Failed to load renderer");
	}

	if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
	{
		GetSDLError("Failed to initialize PNG");
	}
}

void load_entities()
{
	constructor_entity(&brick, &src_brick, &dst_brick, &dst_brick, "img/blocks.png", 'c');
	constructor_entity(&tnt, &src_tnt, &dst_tnt, &dst_tnt, "img/blocks.png", 't');
	constructor_entity(&fire, &src_fire, &dst_fire, &fire_rect, "img/blocks.png", 'f');
	constructor_entity(&p, &player_src, &player_dst, &player_rect, "img/amogus2.png", 'p');

	constructor_entity(&up, &up_src, &up_dst, &up_dst, "img/blocks.png", 'b');
	constructor_entity(&down, &down_src, &down_dst, &down_dst, "img/blocks.png", 'b');
	constructor_entity(&background, &background_src, &background_dst, &background_dst, "img/mario2.jpg", 'b');
	constructor_entity(&background2, &background2_src, &background2_dst, &background2_dst, "img/mario2.jpg", 'b');
	constructor_entity(&next, &next_src, &next_dst, &next_dst, "img/next.png", 'b');
	constructor_entity(&prev, &prev_src, &prev_dst, &prev_dst, "img/back.png", 'b');
	constructor_entity(&reset, &reset_src, &reset_dst, &reset_dst, "img/reset.png", 'b');
	constructor_entity(&stone, &stone_src, &stone_dst, &stone_dst, "img/stone.png", 'b');
	constructor_entity(&save, &save_src, &save_dst, &save_dst, "img/save.png", 'b');
	constructor_entity(&fire2, &src_fire2, &dst_fire2, &fire_rect2, "img/blocks.png", 'f');
}