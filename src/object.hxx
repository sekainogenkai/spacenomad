/*
 * object.h
 *
 *  Created on: Mar 20, 2015
 *      Author: Kristofer
 */

#ifndef SRC_OBJECT_HXX_
#define SRC_OBJECT_HXX_

#include "main.hxx"
extern "C" {
#include <SDL.h>
}

#include "camera.hxx"

class object {
public:
	object(
		SDL_Renderer *ren,
		const char *texture,
		double x,
		double y);
	object(
		SDL_Renderer *ren,
		const char *texture);
	virtual void animate();
	void draw(SDL_Renderer *ren, camera& displayCamera);
	void angularVel_dampening(double dampening);
	void movement_dampening(double dampening);
	void considerCamera(camera& displayCamera, int clearFactor);
	virtual ~object();
protected:
	double x;
	double y;
	double xVel;
	double yVel;
	double facingDirection;
	double angularVel;

	space_nomad_SDL_Texture_unique_ptr texture;
};

#endif /* SRC_OBJECT_HXX_ */
