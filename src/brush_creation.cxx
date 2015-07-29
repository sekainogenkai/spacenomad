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
void
brush_creation::fill_circle(SDL_Renderer *ren, const SDL_Rect& bounds) {
	// Using ellipse standard form (x - h)^2/a^2 + (y-k)^2/b^2 = 1.
	// Draw a pixel if its center satisfies <= 1.
	auto a = bounds.w / 2.0;
	auto h = bounds.x + a;
	auto b = bounds.h / 2.0;
	auto k = bounds.y + b;
	auto y = bounds.y + b;

	for (auto x = bounds.x; x < bounds.x + bounds.w/2 + 1; x++) {
			// Measure from the center of each pixel rather than something else.
			double pix_center_x = x + 0.5;
			double pix_center_y;
			do {
				y--;
				pix_center_y = y + 0.5;
			} while ((pix_center_x - h)*(pix_center_x - h) / (a*a) + (pix_center_y - k)*(pix_center_y - k) / (b*b) <= 1);
			y++;
				SDL_RenderDrawLine(ren, x, y, x,  bounds.y + bounds.h - (y - bounds.y));
				auto x_mirrored = bounds.x + bounds.w - (x - bounds.x);
				SDL_RenderDrawLine(ren, x_mirrored, y, x_mirrored,  bounds.y + bounds.h - (y - bounds.y));
				continue;
			//std::cerr << x << "," << y << ": " << ((pix_center_x - h)*(pix_center_x - h) / (a*a) + (pix_center_y - k)*(pix_center_y - k) / (b*b)) << std::endl;
		}
}

brush_creation::brush_creation(SDL_Renderer * ren, std::default_random_engine & random_engine) {

	// Test to see if randomness works
	std::cout << "Making brush" << std::endl;
	std::uniform_int_distribution<int> randomNumberDist(0,10000);
	std::cout << "Testing the randomness in brush_creation " << randomNumberDist(random_engine) << std::endl;

	// Size of brush
	std::uniform_int_distribution<int> distr_randSize(5, 300);
	auto size = distr_randSize(random_engine);
	// Make surface
	surface = std::move(space_nomad_SDL_Surface_unique_ptr(SDL_CreateRGBSurface(0, size, size, 32, 0, 0, 0, 0)));
	space_nomad_SDL_Renderer_unique_ptr surface_ren(SDL_CreateSoftwareRenderer(surface.get()));

	// Amount of specs in brush
	std::uniform_int_distribution<int> distr_randSpecs(1, 5);

	// Set up to make specs
	auto numSpecs = distr_randSpecs(random_engine);
	SDL_Rect dst;

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


		fill_circle(surface_ren.get(), dst);
	}
}

brush_creation::brush_creation(brush_creation&& orig) {
	surface = std::move(orig.surface);
}

space_nomad_SDL_Renderer_unique_ptr&
brush_creation::get_renderer() {
	return surface_ren;
}

brush_creation::~brush_creation() {
	// TODO Auto-generated destructor stub
}
