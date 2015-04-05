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
		double x = 0,
		double y = 0,
		double xVel = 0,
		double yVel = 0,
		double angular = 0);
	virtual void animate();
	void draw(SDL_Renderer *ren, camera& displayCamera);
	void angularVel_dampening(double dampening);
	void movement_dampening(double dampening);
	void considerCamera(camera& displayCamera, int clearFactor);
	bool getAttractive() const { return attractive;};
	double getX() const { return x; };
	double getY() const { return y; };
	int getRadius() const { return radius; };
	double getGROI() const { return gravitational_radius_of_influence; };
	double getMass() const { return mass; };
	void applyForce(double magnitude, double towards_x, double towards_y);
	virtual ~object();
protected:
	double x;
	double y;
	double xVel;
	double yVel;
	double facingDirection;
	double angularVel;
	bool attractive;
	double mass;
	int radius;
	double gravitational_radius_of_influence;
	space_nomad_SDL_Texture_unique_ptr texture;
};

#endif /* SRC_OBJECT_HXX_ */
