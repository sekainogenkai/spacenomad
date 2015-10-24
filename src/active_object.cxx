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
#include "fading_projectile.hxx"
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
						xVel + this->xVel, yVel + this->yVel, // Trajectory
						spread, damage)));
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
							xVel + this->xVel, yVel + this->yVel, // Trajectory
							spread, damage)));
	std::cout << "SHooting 2" << std::endl;
}

void active_object::make_fading_projectile(SDL_Renderer* ren, universe& universe, int radius,
		SDL_Color color, double x, double y, double xVel, double yVel,
		int spread, int damage, int frame_life, int alpha_start) {
	std::cout << "Shooting 1" << std::endl;
	universe.add_universal_object(std::unique_ptr<object>(
					new spacenomad::fading_projectile(
							ren,
							radius,
							color,
							x, y, // Shooting start location
							xVel + this->xVel, yVel + this->yVel, // Trajectory
							spread, damage,
							frame_life, alpha_start))); // Trajectory
	std::cout << "SHooting 2" << std::endl;
}


void active_object::make_jet(SDL_Renderer *ren, universe& universe, double x, double y, double angle) {


}

void active_object::make_jet_particles(SDL_Renderer *ren, universe& universe, double x, double y, double angle, SDL_Color color, double distance) {
	active_object::make_fading_projectile(ren, universe, 10, {255, 0, 255, 255}, x, y, 10, 10, 60);

}

// TODO make fading projecile.

// TODO make jet stream.

active_object::~active_object() {
	// TODO Auto-generated destructor stub
}

} /* namespace spacenomad */
