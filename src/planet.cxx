/*
 * planet.cxx
 *
 *  Created on: Mar 29, 2015
 *      Author: Kristofer
 */

#include "planet.hxx"
#include <cmath>

planet::planet(SDL_Renderer *ren, double x, double y, double xVel, double yVel, double angularVel, int radius, double density)
: object(ren, "planet/plain.png", x, y, xVel, yVel, angularVel)
{
	mass = density * pow(radius, 2) * M_PI;
	gravitational_radius_of_influence = 10000000;
	attractive = true;
	this->radius = radius;
}

planet::~planet() {
}
