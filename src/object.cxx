/*
 * object.cpp
 *
 *  Created on: Mar 20, 2015
 *      Author: Kristofer
 */

#include "object.hxx"

#include <algorithm>
#include <iostream>
#include <math.h>

object::object(
		SDL_Renderer *ren,
		const char *textureFilename,
		double x,
		double y,
		double xVel,
		double yVel,
		double angularVel)
: x(x)
, y(y)
, xVel(xVel)
, yVel(yVel)
, facingDirection(0)
, angularVel(angularVel)
, texture(loadTexture(ren, textureFilename))
, gravitational_radius_of_influence(0)
{
        int w;
        SDL_QueryTexture(texture.get(), NULL, NULL, &w, NULL);
	radius = w/2;
	attractive = false;
	mass = 0;
}

// This is for making a number that is close enough to zero become zero.
static bool min_to_zero(double* number, double min) {
	if (*number < min && *number > -min) {
		number = 0;
		return true;
	}
	return false;
}

void object::angularVel_dampening(double dampening){
	if (!min_to_zero(&angularVel, .001)) {
		angularVel /= dampening;
	}
}

void object::movement_dampening(double dampening) {
	auto const minSpeed = .001;
	min_to_zero(&xVel, minSpeed);
	min_to_zero(&yVel, minSpeed);
}

void object::animate() {
	x += xVel;
	y += yVel;
	facingDirection += angularVel;
	facingDirection = fmod(facingDirection, 360);
}

void object::considerCamera(camera& displayCamera, int clearFactor)
{
	int w, h;
	SDL_QueryTexture(texture.get(), NULL, NULL, &w, &h);
	displayCamera.considerObject(x, y, clearFactor * std::max(w, h));
}

void object::draw(SDL_Renderer *ren, camera& displayCamera) {
	SDL_Rect dst;
	SDL_QueryTexture(texture.get(), NULL, NULL, &dst.w, &dst.h);
	dst.x = x - dst.w/2;
	dst.y = y - dst.h/2;
	if (displayCamera.transform(&dst))
		SDL_RenderCopyEx(ren, texture.get(), NULL, &dst, facingDirection, NULL, SDL_FLIP_NONE);
}



void object::applyForce(double magnitude, double x, double y) {

	auto acceleration_magnitude = magnitude / mass / space_nomad_fps;
	xVel += acceleration_magnitude * x;
	yVel += acceleration_magnitude * y;
}

object::~object() {
	// TODO Auto-generated destructor stub
}

