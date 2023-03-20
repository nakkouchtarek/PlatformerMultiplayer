#include <SDL2/SDL.h>
#include <methods.h>
#include <SDL2/SDL_ttf.h>
#include <global.h>

void draw_text(char* word, int x, int y, int w, int h)
{
    text_dst.x = x;
    text_dst.y = y;

    text_src.w = w;
    text_src.h = h;
    text_dst.w = w;
    text_dst.h = h;

    text = TTF_RenderText_Solid( font, word, color );

	if ( !text ) 
	{
		GetSDLError("Failed to render text: ");
	}

	text_texture = SDL_CreateTextureFromSurface( renderer, text );

	SDL_RenderCopy( renderer, text_texture, &text_src, &text_dst );

    SDL_DestroyTexture( text_texture );
    SDL_FreeSurface( text );
}