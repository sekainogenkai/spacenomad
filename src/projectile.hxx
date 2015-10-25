/*
 * projectile.hxx
 *
 *  Created on: Sep 11, 2015
 *      Author: Kristofer
 */

#ifndef SRC_PROJECTILE_HXX_
#define SRC_PROJECTILE_HXX_

#include "object.hxx"

namespace spacenomad {

class projectile : public object {
public:
	projectile(SDL_Renderer *ren, const std::string& textureFilename, const std::string& textureTrail,
			double x, double y, double xVel, double yVel, int spread = 0, int damage = 10);

	projectile(SDL_Renderer *ren, int radius, SDL_Color color,
			double x, double y, double xVel, double yVel, int spread = 0, int damage = 10);


	virtual void animate();
	virtual void draw(SDL_Renderer *ren, const camera& displayCamera) const;
	virtual ~projectile();
private:
	double damage;
	double spread;
};

} /* namespace spacenomad */

#endif /* SRC_PROJECTILE_HXX_ */
