/*
 * projectile.cxx
 *
 *  Created on: Sep 11, 2015
 *      Author: Kristofer
 */

#include "projectile.hxx"

namespace spacenomad {

projectile::projectile(SDL_Renderer *ren, const char * textureFilename, const char * textureTrail) {
	// TODO Auto-generated constructor stub
	object::object(SDL_Renderer *ren, const char * textureFilename);

}

virtual void animate() {
	object::animate();
}

void draw(SDL_Renderer *ren, const camera& displayCamera) const {
	object::draw(ren, displayCamera);
}

projectile::~projectile() {
	// TODO Auto-generated destructor stub
}

} /* namespace spacenomad */


