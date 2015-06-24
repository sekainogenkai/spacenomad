/*
 * planet_generation_mode.hxx
 *
 *  Created on: Jun 23, 2015
 *      Author: Kristofer
 */

#ifndef SRC_PLANET_GENERATION_MODE_HXX_
#define SRC_PLANET_GENERATION_MODE_HXX_

#include "camera.hxx"
#include "main.hxx"
#include "mode.hxx"
#include "player.hxx"
#include "star_field.hxx"
#include "universe.hxx"

class planet_generation_mode
: public mode {
public:
	planet_generation_mode(SDL_Renderer *ren);
	virtual bool processEvents(SDL_Event *event, mode *& new_mode, SDL_Renderer *ren);
	virtual void animate();
	virtual void render(SDL_Renderer *ren, camera& displayCamera, TTF_Font *font);
	virtual ~planet_generation_mode();
private:
	space_nomad_SDL_Texture_unique_ptr meBraggingAbout4k;
};

#endif /* SRC_PLANET_GENERATION_MODE_HXX_ */
