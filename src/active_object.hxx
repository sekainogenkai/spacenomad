/*
 * active_object.hxx
 *
 *  Created on: Oct 22, 2015
 *      Author: Kristofer
 */

#ifndef SRC_ACTIVE_OBJECT_HXX_
#define SRC_ACTIVE_OBJECT_HXX_

#include "object.hxx"


namespace spacenomad {

class universe;

class active_object: public object {
public:
	active_object(SDL_Renderer *ren,
			const char *textureFilename,
			double x = 0,
			double y = 0,
			double xVel = 0,
			double yVel = 0,
			double angular = 0,
			double mass = 0);
	void make_projectile(SDL_Renderer *ren, universe& universe, const std::string& textureFilename, const std::string& textureTrail,
			double x, double y, double xVel, double yVel, int spread=0, int damage=0);
	void make_projectile(SDL_Renderer *ren, universe& universe, int radius,
			SDL_Color color, double x, double y, double xVel, double yVel, int spread = 0, int damage = 0);
	virtual ~active_object();
};

} /* namespace spacenomad */

#endif /* SRC_ACTIVE_OBJECT_HXX_ */
