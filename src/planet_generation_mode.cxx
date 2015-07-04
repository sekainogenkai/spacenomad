/*
 * planet_generation_mode.cxx
 *
 *  Created on: Jun 23, 2015
 *      Author: Kristofer
 */

#include "brush_creation.hxx"
#include "main.hxx"
#include "camera.hxx"
#include "player.hxx"
#include "star_field.hxx"
#include "universe.hxx"
#include "planet_generation_mode.hxx"


#include <ctime>
#include <functional>
#include <iostream>
#include <array>

planet_generation_mode::planet_generation_mode(SDL_Renderer *ren)
: meBraggingAbout4k(loadTexture(ren, "planet_generation_mode/This is 4k.png"))
, random_engine(time(NULL))
{


	std::uniform_int_distribution<int> random_number(1,100);
	// Amount of brushes to make
	int brush_amount = random_number(random_engine);
	std::cout << "I am going to make " << brush_amount << " brushes.";
	brush_creation brushes[brush_amount];
	for (int i = 0; i < brush_amount; i++) {
		brushes[i] = brush_creation(ren, random_engine);
	}

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


