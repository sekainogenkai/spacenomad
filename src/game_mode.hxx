/*
 * game_mode.hxx
 *
 *  Created on: Jan 5, 2015
 *      Author: Kristofer
 */

#ifndef SRC_GAME_MODE_HXX_
#define SRC_GAME_MODE_HXX_

#include "camera.hxx"
#include "main.hxx"
#include "mode.hxx"
#include "player.hxx"
#include "star_field.hxx"

class game_mode
: public mode
{
public:
	game_mode(SDL_Renderer *ren);
	virtual bool processEvents(SDL_Event *event, mode *& new_mode, SDL_Renderer *ren);
	virtual void animate();
	virtual void render(SDL_Renderer *ren, camera& displayCamera, TTF_Font *font);
	~game_mode();
private:
	// Player
	player myPlayer;
	player myStaticPlayer;
	star_field stars;
};


#endif /* SRC_GAME_MODE_HXX_ */
