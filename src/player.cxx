/*
 * player.cxx
 *
 *  Created on: Mar 20, 2015
 *      Author: Kristofer
 */

#include "player.hxx"
#include "universe.hxx"
#include "projectile.hxx"
#include "object.hxx"

#include <algorithm>
#include <iostream>
#include <cmath>
#include <memory>


player::player(SDL_Renderer *ren, const char *textureFilename)
: object(ren, textureFilename)
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
	std::cout << "MOUSE MOVING: " << mouse_pos.x << ", " << mouse_pos.y << std::endl;
}

void player::start_shooting() {
	shot = true;
}

void player::stop_shooting(){
	shot = false;
}

void player::shoot(double angle, int barrel_length, int speed, universe& universe, SDL_Renderer *ren) {
	std::cout << "SHOOTING" << std::endl;

	// Get vector of gun barrel end
	double barrel_shot_distance = barrel_length - 10; // Make it start a little bit inside the barrel
	auto barrel_end_x_vec = barrel_shot_distance * cos(angle/180.0*M_PI);
	auto barrel_end_y_vec = barrel_shot_distance * sin(angle/180.0*M_PI);
	// Get vector of gun trajectory
	auto x_vec = speed * cos(angle/180.0*M_PI);
	auto y_vec = speed * sin(angle/180.0*M_PI);

	// Make the bullets appear
	object::make_projectile(
					ren, universe,
					10,
					{255, 255, 255, 255},
					barrel_end_x_vec + x, y + barrel_end_y_vec, // Shooting start location
					x_vec, y_vec); // Trajectory
}

void player::make_jet(SDL_Renderer *ren, universe& universe, double x, double y, double angle) {


}

void player::make_jet_particles(SDL_Renderer *ren, universe& universe, double x, double y, double angle, SDL_Color color, double distance) {
	object::make_projectile(ren, universe, 10, {255, 0, 255, 255}, x, y, 10, 10);

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
		double xAccel = sin((180-facingDirection)/180*M_PI) * moveAccelSpeed;
		double yAccel = cos((180+facingDirection)/180*M_PI) * moveAccelSpeed;
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
	SDL_Rect gun_barrel_dst;
	SDL_QueryTexture(gun_barrel_tex.get(), NULL, NULL, &gun_barrel_dst.w, &gun_barrel_dst.h);
	gun_barrel_dst.x = x - gun_barrel_dst.w/2;
	gun_barrel_dst.y = y - gun_barrel_dst.h;
	auto gun_barrel_length = gun_barrel_dst.h;
	std::cout << "Gun Barrel Height: " << gun_barrel_length << std::endl;
	if (displayCamera.transform(&gun_barrel_dst)) {
		auto gun_barrel_facing_direction = angle(mouse_pos.x - gun_barrel_dst.x - gun_barrel_dst.w/2, mouse_pos.y - gun_barrel_dst.y - gun_barrel_dst.h);
		SDL_Point center = {gun_barrel_dst.w/2, gun_barrel_dst.h};
		SDL_RenderCopyEx(ren, gun_barrel_tex.get(), NULL, &gun_barrel_dst, gun_barrel_facing_direction + 90, &center, SDL_FLIP_NONE);

		if (shot) {
			shoot(gun_barrel_facing_direction, gun_barrel_length, 20, universe, ren);
		}
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

