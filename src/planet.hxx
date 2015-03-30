/*
 * planet.hxx
 *
 *  Created on: Mar 29, 2015
 *      Author: Kristofer
 */

#ifndef SRC_PLANET_HXX_
#define SRC_PLANET_HXX_

#include "object.hxx"

class planet : public object{
public:
	planet(SDL_Renderer *ren, double x, double y, double xVel, double yVel, double angleVel, int radius, double density);
	virtual ~planet();
private:
	int radius;
	double weight;
};

#endif /* SRC_PLANET_HXX_ */
