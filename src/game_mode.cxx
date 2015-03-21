/*
 * game_mode.cxx
 *
 *  Created on: Jan 5, 2015
 *      Author: Kristofer
 */


#include "game_mode.hxx"

game_mode::game_mode(
		SDL_Renderer *ren)
: space_suit_texture_uptr(loadTexture(ren, "astronaut/space_suit.png"))
{
}

bool game_mode::processEvents(SDL_Event *event, mode *& new_mode, SDL_Renderer *ren)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_BACKSPACE:
			return true;
		}
	}
	return false;
}
void game_mode::animate()
{
}
void game_mode::render(SDL_Renderer *ren, TTF_Font *font)
{
	SDL_RenderCopy(ren, space_suit_texture_uptr.get(), NULL, NULL);
}

game_mode::~game_mode()
{
}
