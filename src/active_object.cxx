/*
 * active_object.cxx
 *
 *  Created on: Oct 22, 2015
 *      Author: Kristofer
 */

#include "active_object.hxx"
#include "object.hxx"
#include "projectile.hxx"
#include "universe.hxx"
#include <iostream>  /// debugging


namespace spacenomad {

class universe;

active_object::active_object(SDL_Renderer *ren, const char *textureFilename, double x, double y, double xVel, double yVel, double angular, double mass)
:object(ren, textureFilename, x, y, xVel, yVel, angular, mass)

{
	// TODO Auto-generated constructor stub

}

// Filename
void active_object::make_projectile(SDL_Renderer* ren, universe& universe,
		const std::string& textureFilename, const std::string& textureTrail,
		double x, double y, double xVel, double yVel, int spread, int damage) {

	universe.add_universal_object(std::unique_ptr<object>(
				new spacenomad::projectile(
						ren,
						textureFilename,
						textureTrail,
						x, y, // Shooting start location
						xVel + this->xVel, yVel + this->yVel))); // Trajectory
}

// Radius + Color
void active_object::make_projectile(SDL_Renderer* ren, universe& universe, int radius,
		SDL_Color color, double x, double y, double xVel, double yVel,
		int spread, int damage) {
	std::cout << "Shooting 1" << std::endl;
	universe.add_universal_object(std::unique_ptr<object>(
					new spacenomad::projectile(
							ren,
							radius,
							color,
							x, y, // Shooting start location
							xVel + this->xVel, yVel + this->yVel))); // Trajectory
	std::cout << "SHooting 2" << std::endl;

}

// TODO make fading projecile.

// TODO make jet stream.

active_object::~active_object() {
	// TODO Auto-generated destructor stub
}

} /* namespace spacenomad */
