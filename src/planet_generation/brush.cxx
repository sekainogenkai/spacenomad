/*
 * brush.cxx
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
#include "brush.hxx"

#include <iostream>
#include <vector>

namespace spacenomad {


brush::brush(std::default_random_engine & random_engine) {

	// Test to see if randomness works
	std::cout << "Making brush" << std::endl;
	std::uniform_int_distribution<int> randomNumberDist(0,10000);
	std::cout << "Testing the randomness in brush " << randomNumberDist(random_engine) << std::endl;

	// Size of brush
	std::uniform_int_distribution<int> distr_randSize(5, 300);
	auto size = distr_randSize(random_engine);

	// Make surface
	surface = std::move(space_nomad_SDL_Surface_unique_ptr(SDL_CreateRGBSurface(0, size, size, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000)));
	space_nomad_SDL_Renderer_unique_ptr surface_ren(SDL_CreateSoftwareRenderer(surface.get()));
	//SDL_SetRenderDrawBlendMode(surface_ren.get(), SDL_BLENDMODE_BLEND);
	//SDL_SetRenderDrawColor(surface_ren.get(), 0, 0, 0, 0);
	//SDL_RenderClear(surface_ren.get());

	// Amount of specs in brush
	std::uniform_int_distribution<int> distr_randSpecs(1, 5);

	// Set up to make specs
	auto numSpecs = distr_randSpecs(random_engine);
	SDL_Rect dst;

	// Set up base random color
	std::uniform_int_distribution<int> distr_randColor(0, 255);
	// Don't make invisible/barely visible brushes: constrain the alpha to >1.
	std::uniform_int_distribution<int> distr_randAlpha(2, 255);
	std::vector<int> rgb;
	for (int i = 0; i < 3; i++) {
		rgb.push_back(distr_randColor(random_engine));
	}
	auto alpha = distr_randAlpha(random_engine);

	// Making the specs
	for (int i = 0; i < numSpecs; i++) {

		// Location and size
		std::uniform_int_distribution<int> distr_length(1, size/2);
		dst.w = distr_length(random_engine);
		dst.h = distr_length(random_engine);
		std::uniform_int_distribution<int> distr_pos_x(dst.w, size - dst.w);
		std::uniform_int_distribution<int> distr_pos_y(dst.h, size - dst.h);
		dst.x = distr_pos_x(random_engine);
		dst.y = distr_pos_y(random_engine);

		// Random color
		std::cerr << "c=" << rgb[0] << "," << rgb[1] << "," << rgb[2] << "," << alpha << std::endl;
		SDL_SetRenderDrawColor(surface_ren.get(), rgb[0], rgb[1], rgb[2], alpha);
		//TODO make the color vary slightly

		fill_circle(surface_ren.get(), dst);
	}
}


brush::brush(brush&& orig) {
	surface = std::move(orig.surface);
}


brush::~brush() {
}

}; /* namespace spacenomad */
