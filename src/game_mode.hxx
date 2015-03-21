/*
 * game_mode.hxx
 *
 *  Created on: Jan 5, 2015
 *      Author: Kristofer
 */

#ifndef SRC_GAME_MODE_HXX_
#define SRC_GAME_MODE_HXX_

#include "main.hxx"
#include "mode.hxx"

class game_mode
: public mode
{
public:
	game_mode(SDL_Renderer *ren);
	virtual bool processEvents(SDL_Event *event, mode *& new_mode, SDL_Renderer *ren);
	virtual void animate();
	virtual void render(SDL_Renderer *ren, TTF_Font *font);
	~game_mode();
private:
	space_nomad_SDL_Texture_unique_ptr
		space_suit_texture_uptr;
};


#endif /* SRC_GAME_MODE_HXX_ */
