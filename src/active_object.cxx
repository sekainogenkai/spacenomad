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
:object(ren, textureFilename, x, y, xVel, yVel, angular, mass),
 random_engine(time(NULL))

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
		int spread, int damage, int frame_life, int alpha_start, double grow_factor) {
	std::cout << "Shooting 1" << std::endl;
	universe.add_universal_object(std::unique_ptr<object>(
			new spacenomad::fading_projectile(
					ren,
					radius,
					color,
					x, y, // Shooting start location
					xVel + this->xVel, yVel + this->yVel, // Trajectory
					spread, damage,
					frame_life, alpha_start,
					grow_factor)));
	std::cout << "SHooting 2" << std::endl;
}


void active_object::make_jet(SDL_Renderer *ren, universe& universe, SDL_Color color, double x, double y,
		double angle,
		int magnitude_min, int magnitude_max,
		int frame_life_min, int frame_life_max,
		int next_frame_min, int next_frame_max,
		double angle_variant_min, double angle_variant_max,
		int radius_min, int radius_max,
		int alpha_start_min, int alpha_start_max,
		double grow_min, double grow_max
) {
	make_jet_next_frame_count--;
	while(make_jet_next_frame_count < 0) {
		make_jet_next_frame_count++;
		std::cout << "I am doing something?aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << std::endl;
		std::uniform_int_distribution<int> frame_life_dstr(frame_life_min, frame_life_max);
		std::uniform_real_distribution<double> angle_variant_dstr(angle_variant_min, angle_variant_max);
		std::uniform_real_distribution<double> magnitude_dstr(magnitude_min, magnitude_max);
		std::uniform_int_distribution<int> radius_dstr(radius_min, radius_max);
		std::uniform_int_distribution<int> alpha_start_dstr(alpha_start_min, alpha_start_max);
		std::uniform_real_distribution<double> grow_dstr(grow_min, grow_max);
		// Make the bullets(particles I mean) appear

		double x_jet_vel,y_jet_vel;
		to_cartesian(x_jet_vel, y_jet_vel, angle + angle_variant_dstr(random_engine), magnitude_dstr(random_engine));
		make_fading_projectile(
				ren, universe,
				radius_dstr(random_engine), // Radius
				color, // Color
				x, y, // Shooting start location
				x_jet_vel, y_jet_vel, // Trajectory
				0, 0, // Damage and spread
				frame_life_dstr(random_engine), // Time and alpha start.. This is for testing it
				alpha_start_dstr(random_engine), // Alpha start 255 is opaque
				grow_dstr(random_engine));
	}
	if (make_jet_next_frame_count == 0) {
		std::uniform_int_distribution<int> frame_count_dstr(next_frame_min, next_frame_max); // make the next frame
		make_jet_next_frame_count += frame_count_dstr(random_engine);
	}
}


// TODO make fading projectile.

// TODO make jet stream.

active_object::~active_object() {
	// TODO Auto-generated destructor stub
}

} /* namespace spacenomad */
