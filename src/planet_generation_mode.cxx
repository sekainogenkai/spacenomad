/*
 * planet_generation_mode.cxx
 *
 *  Created on: Jun 23, 2015
 *      Author: Kristofer
 */

#include "main.hxx"
#include "camera.hxx"
#include "player.hxx"
#include "star_field.hxx"
#include "universe.hxx"
#include "planet_generation_mode.hxx"

#include <ctime>
#include <functional>
#include <iostream>

planet_generation_mode::planet_generation_mode(SDL_Renderer *ren)
: meBraggingAbout4k(loadTexture(ren, "planet_generation_mode/This is 4k.png"))
, random_engine(time(NULL))
{
}

bool planet_generation_mode::processEvents(SDL_Event *event, main_class& main) {
	switch (event->type)
	{
	case SDL_KEYDOWN:
		if (event->key.repeat)
			break;

		switch (event->key.keysym.sym)
		{
		// case Up
		case SDLK_BACKSPACE:
			return true;
		}
	}
	return false;
}

void planet_generation_mode::animate() {
	std::uniform_int_distribution<int> randomNumber(0,10);
	std::cout << randomNumber(random_engine);
}

void planet_generation_mode::render(SDL_Renderer *ren, camera& displayCamera, TTF_Font *font) {
	SDL_Rect dst;

	// This Renders the image about me bragging about 4k
	SDL_QueryTexture(meBraggingAbout4k.get(), NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, meBraggingAbout4k.get(),NULL, &dst);
}

planet_generation_mode::~planet_generation_mode() {
	// TODO Auto-generated destructor stub

}


