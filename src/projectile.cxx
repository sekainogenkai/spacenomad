/*
 * projectile.cxx
 *
 *  Created on: Sep 11, 2015
 *      Author: Kristofer
 */

#include "projectile.hxx"
#include "main.hxx"

#include <iostream> // debugging

extern "C" {
#include <SDL.h>
}


namespace spacenomad {

static space_nomad_SDL_Surface_unique_ptr build_filled_circle(int radius, SDL_Color color) {
	std::cout << "I am making color" << std::endl;
	auto surface = space_nomad_SDL_Surface_unique_ptr(SDL_CreateRGBSurface(0, 2*radius, 2*radius, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff));
	auto ren = space_nomad_SDL_Renderer_unique_ptr(SDL_CreateSoftwareRenderer(surface.get()));
	SDL_SetRenderDrawColor(ren.get(), color.r, color.b, color.g, color.a);
	fill_circle(ren.get(), {0, 0, 2*radius, 2*radius}, false);
	std::cout << "I am done making color" << std::endl;

	return std::move(surface);
}

// Filename
projectile::projectile(SDL_Renderer *ren, const std::string& textureFilename, const std::string& textureTrail,
		double x, double y, double xVel, double yVel, int spread, int damage)
: object(ren, textureFilename.c_str(), x, y, xVel, yVel) {
}

// Radius + Color
projectile::projectile(SDL_Renderer* ren, int radius,
		SDL_Color color, double x, double y, double xVel, double yVel,
		int spread, int damage)
: object(ren, build_filled_circle(radius, color), x, y, xVel, yVel) {

	std::cout << "I am done making the thingy" << std::endl;
}

void projectile::animate() {
	object::animate();
}

void projectile::draw(SDL_Renderer *ren, const camera& displayCamera) const {
	object::draw(ren, displayCamera);
}

projectile::~projectile() {
	// TODO Auto-generated destructor stub
}

} /* namespace spacenomad */


