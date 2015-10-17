/*
 * projectile.cxx
 *
 *  Created on: Sep 11, 2015
 *      Author: Kristofer
 */

#include "projectile.hxx"

namespace spacenomad {

projectile::projectile(SDL_Renderer *ren, const std::string& textureFilename, const std::string& textureTrail,
		double x, double y, double xVel, double yVel, int spread, int damage)
: object(ren, textureFilename.c_str(), x, y, xVel, yVel) {
}

void projectile::animate() {
	object::animate();
}

void projectile::draw(SDL_Renderer *ren, const camera& displayCamera) const {
	object::draw(ren, displayCamera);
}

projectile::~projectile() {
	// TODO Auto-generated destructor stub
}

} /* namespace spacenomad */


