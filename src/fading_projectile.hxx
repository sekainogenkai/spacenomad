/*
 * fading_projectile.hxx
 *
 *  Created on: Oct 24, 2015
 *      Author: Kristofer
 */

#ifndef SRC_FADING_PROJECTILE_HXX_
#define SRC_FADING_PROJECTILE_HXX_

#include "projectile.hxx"

namespace spacenomad {

class fading_projectile: public projectile {
public:
	fading_projectile(SDL_Renderer *ren, const std::string& textureFilename, const std::string& textureTrail,
				double x, double y, double xVel, double yVel, int spread = 0, int damage = 10, int frame_life = 60, int alpha_start = 250);
	fading_projectile(SDL_Renderer *ren, int radius, SDL_Color color,
			double x, double y, double xVel, double yVel, int spread = 0, int damage = 10, int frame_life = 60, int alpha_start = 250);
	virtual void animate();
	void draw(SDL_Renderer *ren, const camera& displayCamera);
	virtual ~fading_projectile();
private:
	int frame_life;
	int frame_life_beginning;
	int alpha_start;
};

} /* namespace spacenomad */

#endif /* SRC_FADING_PROJECTILE_HXX_ */
