/*
 * player.cxx
 *
 *  Created on: Mar 20, 2015
 *      Author: Kristofer
 */

#include "player.hxx"

#include <algorithm>
#include <iostream>
#include <cmath>
#include <memory>

namespace spacenomad {

player::player(SDL_Renderer *ren, const char *textureFilename)
: active_object(ren, textureFilename)
, up(false)
, down(false)
, left(false)
, right(false)
, shift(false)
, space(false)
,shot(false)
, gun_barrel_tex(loadTexture(ren, "astronaut/gun_barrel.png"))
{
	mass = 1;
}

void player::set_mouse_pos(int x, int y) {
	mouse_pos.x = x;
	mouse_pos.y = y;

}

void player::start_shooting() {
	shot = true;
}

void player::stop_shooting(){
	shot = false;
}

void player::shoot(double angle, int barrel_length, int speed, universe& universe, SDL_Renderer *ren) {

	// Get vector of gun barrel end
	double barrel_shot_distance = barrel_length - 10; // Make it start a little bit inside the barrel
	auto barrel_end_x_vec = barrel_shot_distance * cos(angle/180.0*M_PI);
	auto barrel_end_y_vec = barrel_shot_distance * sin(angle/180.0*M_PI);
	// Get vector of gun trajectory
	auto x_vec = speed * cos(angle/180.0*M_PI);
	auto y_vec = speed * sin(angle/180.0*M_PI);

	// Make the bullets appear
	active_object::make_fading_projectile(
			ren, universe,
			10, // Radius
			{255, 255, 255, 255},
			barrel_end_x_vec + x, y + barrel_end_y_vec, // Shooting start location
			x_vec, y_vec, // Trajectory
			500, 1, // Damage and spread
			1000, 100); // Time and alpha start.. This is for testing it
}



void player::animate() {
	// Turning
	const auto turnAccelSpeed = .2;
	if (left) {
		if (angularVel > 0) {
			object::angularVel_dampening(1.2);
		}
		angularVel -= turnAccelSpeed;
	}
	if (right) {
		if (angularVel < 0) {
			object::angularVel_dampening(1.2);
		}
		angularVel += turnAccelSpeed;
	}
	if (!right && !left){
		object::angularVel_dampening(1.2);
	}

	// Moving forwards
	const auto moveAccelSpeed = 1;
	if (up || down) {
		double xAccel, yAccel;
		to_cartesian(xAccel, yAccel, facingDirection, moveAccelSpeed);
		if (up) {
			xVel += xAccel;
			yVel += yAccel;
		}
		if (down) {
			xVel -= xAccel;
			yVel -= yAccel;
		}
	}
	object::animate();
}

void player::draw(SDL_Renderer *ren, const camera& displayCamera, universe& universe) {

	// Gun barrel draw
	SDL_Rect gun_barrel_dst;
	SDL_QueryTexture(gun_barrel_tex.get(), NULL, NULL, &gun_barrel_dst.w, &gun_barrel_dst.h);
	gun_barrel_dst.x = x - gun_barrel_dst.w/2;
	gun_barrel_dst.y = y - gun_barrel_dst.h;
	auto gun_barrel_length = gun_barrel_dst.h;
	if (displayCamera.transform(&gun_barrel_dst)) {
		auto gun_barrel_facing_direction = angle(mouse_pos.x - gun_barrel_dst.x - gun_barrel_dst.w/2, mouse_pos.y - gun_barrel_dst.y - gun_barrel_dst.h);
		SDL_Point center = {gun_barrel_dst.w/2, gun_barrel_dst.h};
		SDL_RenderCopyEx(ren, gun_barrel_tex.get(), NULL, &gun_barrel_dst, gun_barrel_facing_direction + 90, &center, SDL_FLIP_NONE);

		if (shot) {
			shoot(gun_barrel_facing_direction, gun_barrel_length, 10, universe, ren);
		}
	}

	// Jet particles
	if (up || down) {
		int dir = up?-1 : 1;


		active_object::make_jet(ren, universe, {200, 0, 200, 255}, // Yellow Jet
				x, y,
				facingDirection, // mag, angle
				14 * dir, 20 * dir, // magnitude  min/max
				5, 25, // Frame life min/max
				-10, 2, // Next frame min/max
				-20, 20,// angle variant min/max
				2, 5, // Radius min/max
				200, 255, // Alpha start min/max
				1, 1.1 // Grow min/max
		);
		active_object::make_jet(ren, universe, {200, 0, 0, 255}, // Red Jet
				x, y,
				facingDirection, // angle
				8 * dir, 14 * dir, // magnitude  min/max
				5, 20, // Frame life min/max
				-3, 1, // Next frame min/max
				-15, 15,// angle variant min/max
				2, 20, // Radius min/max
				50, 255, // Alpha start min/max
				.99, 1.02 // Grow min/max
		);
		active_object::make_jet(ren, universe, {0, 200, 0, 255}, // Blue Jet
				x, y,
				facingDirection, // angle
				4 * dir, 12 *dir, // magnitude  min/max
				5, 19, // Frame life min/max
				-10, 2, // Next frame min/max
				-10, 10,// angle variant min/max
				2, 12, // Radius min/max
				200, 255, // Alpha start min/max
				.98, 1 // Grow min/max
		);
	}


	object::draw(ren, displayCamera);

	// Draw location of bullets exit
	//SDL_Rect transformed_barrel_end_dst = {x_vec + x - 5, y + y_vec - 5, 10, 10};

	//	if (displayCamera.transform(&transformed_barrel_end_dst)) {
	//
	//		SDL_SetRenderDrawColor(ren , 0, 255, 255, 255);
	//		SDL_RenderFillRect(ren, &transformed_barrel_end_dst);
	//	}
	//std::cout << "Player (X, Y) " << x << ", " << y << std::endl << "Barrel(X,Y) " << transformed_barrel_end_dst.x << ", " << transformed_barrel_end_dst.y << std::endl;


}


player::~player() {
}

} /* namespace spacenomad */

