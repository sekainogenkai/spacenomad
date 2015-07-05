/*
 * brush_creation.hxx
 *
 *  Created on: Jun 24, 2015
 *      Author: Kristofer
 */

#ifndef SRC_BRUSH_CREATION_HXX_
#define SRC_BRUSH_CREATION_HXX_

#include "camera.hxx"
#include "main.hxx"
#include "mode.hxx"
#include "player.hxx"
#include "star_field.hxx"
#include "universe.hxx"

class brush_creation {
public:
	brush_creation();
	brush_creation(SDL_Renderer * ren, std::default_random_engine & random_engine);
	void draw(int x, int y);
	space_nomad_SDL_Texture_unique_ptr get();
	virtual ~brush_creation();
};

#endif /* SRC_BRUSH_CREATION_HXX_ */
