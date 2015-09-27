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
	projectile(SDL_Renderer *ren, const char * textureFilename, const char * textureTrail);

	virtual void animate();
	void draw(SDL_Renderer *ren, const camera& displayCamera) const;
	virtual ~projectile();
private:
	double damage;
	double spread;
};

} /* namespace spacenomad */

#endif /* SRC_PROJECTILE_HXX_ */
