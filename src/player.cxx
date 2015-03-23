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
{
	// TODO Auto-generated constructor stub
}


void player::animate() {
//	const auto speedMax = 5.0;
//	const auto speedFactor = 0.05;
//	const auto slowFactor = 1.1;
//	if (left)
//		xVel = std::max(xVel - speedFactor, -speedMax);
//	else if (right)
//		xVel = std::min(xVel + speedFactor, speedMax);
//	else
//		xVel /= slowFactor;
//	if (up)
//		yVel = std::max(yVel - speedFactor, -speedMax);
//	else if (down)
//		yVel = std::min(yVel + speedFactor, speedMax);
//	else
//		yVel /= slowFactor;

	// Turning
	const auto turnAccelSpeed = .2;
	if (left) {
		angularVel -= turnAccelSpeed;
	}
	if (right) {
		angularVel += turnAccelSpeed;
	}
	if (!right && !left){
		object::angularVel_dampening(1.2);
	}

	// Moving forwards
	const auto moveAccelSpeed = .3;
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


player::~player() {
	// TODO Auto-generated destructor stub
}

