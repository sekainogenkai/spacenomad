/*
 * brush_creation.cxx
 *
 *  Created on: Jun 24, 2015
 *      Author: Kristofer
 *
 *  Will create a random brush for making textures on planets.
 */


// Step one, random dotted brush, work on different opacity also.

/*
 * Things to randomize
 * Size
 * Number of "dots", reacts to size
 * Type of dots, reacts to Number of dots
 * Per dot, shape, size, opacity, position
 */
#include "brush_creation.hxx"

#include <iostream>

// Assumes that coordinates are pixels or whatever that means
static void render_circle(SDL_Renderer *ren, SDL_Rect bounds) {
	// apparently an ellipse is just a scaled circle according to some part of the internets
	for (auto y_offset = 0; y_offset < bounds.h; y_offset++) {
		auto unit_y = ((double)y_offset)/bounds.h/2.0 - 1.0;
	}
}

brush_creation::brush_creation(SDL_Renderer * ren, std::default_random_engine & random_engine) {
	std::cout << "Making brush" << std::endl;
	std::uniform_int_distribution<int> randomNumberDist(0,10000);
	std::cout << "Testing the randomness in brush_creation " << randomNumberDist(random_engine) << std::endl;

	// Size of brush
	std::uniform_int_distribution<int> randSize(5, 300);
	auto size = randSize(random_engine);
	surface = std::move(space_nomad_SDL_Surface_unique_ptr(SDL_CreateRGBSurface(0, size, size, 8*4, 0, 0, 0, 0)));
	space_nomad_SDL_Renderer_unique_ptr surface_ren(SDL_CreateSoftwareRenderer(surface.get()));

	// Amount of specs in brush
	std::uniform_int_distribution<int> randSpecs(1, 5);
	// Make the specs
	auto numSpecs = randSpecs(random_engine);
	for (int i = 0; i < numSpecs; i++) {
		SDL_RenderDrawPoint(surface_ren, )
	}
}

brush_creation::brush_creation(brush_creation&& orig) {
	surface = std::move(orig.surface);
}


brush_creation::~brush_creation() {
	// TODO Auto-generated destructor stub
}
