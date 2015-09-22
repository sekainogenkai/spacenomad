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

player::player(SDL_Renderer *ren, const char *textureFilename)
: object(ren, textureFilename)
, up(false)
, down(false)
, left(false)
, right(false)
, shift(false)
, space(false)
, gun_barrel_tex(loadTexture(ren, "astronaut/gun_barrel.png"))
{
        mass = 1;
}

void player::set_mouse_pos(int x, int y) {
	mouse_pos.x = x;
	mouse_pos.y = y;
	std::cout << "MOUSE MOVING: " << mouse_pos.x << ", " << mouse_pos.y << std::endl;
}

void player::shoot() {
	std::cout << "SHOOTING" << std::endl;
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

void player::draw(SDL_Renderer *ren, const camera& displayCamera) const {
	SDL_Rect gun_barrel_dst;
	SDL_QueryTexture(gun_barrel_tex.get(), NULL, NULL, &gun_barrel_dst.w, &gun_barrel_dst.h);
	gun_barrel_dst.x = x - gun_barrel_dst.w/2;
	gun_barrel_dst.y = y - gun_barrel_dst.h;
	std::cout << "Gun Barrel Height: " << gun_barrel_dst.h << std::endl;
	if (displayCamera.transform(&gun_barrel_dst)) {
		auto gun_barrel_facing_direction = angle(mouse_pos.x - gun_barrel_dst.x - gun_barrel_dst.w/2, mouse_pos.y - gun_barrel_dst.y - gun_barrel_dst.h) + 90;
		SDL_Point center = {gun_barrel_dst.w/2, gun_barrel_dst.h};
		SDL_RenderCopyEx(ren, gun_barrel_tex.get(), NULL, &gun_barrel_dst, gun_barrel_facing_direction, &center, SDL_FLIP_NONE);\
	}
	object::draw(ren, displayCamera);
}


player::~player() {
}

