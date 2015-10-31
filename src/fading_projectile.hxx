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
				double x, double y, double xVel, double yVel, int spread = 0, int damage = 10, int frame_life = 60, int alpha_start = 250, double grow_factor=1);
	fading_projectile(SDL_Renderer *ren, int radius, SDL_Color color,
			double x, double y, double xVel, double yVel, int spread = 0, int damage = 10, int frame_life = 60, int alpha_start = 250, double grow_factor=1);
	virtual void animate();
	virtual void draw(SDL_Renderer *ren, const camera& displayCamera) const override;
	virtual ~fading_projectile();
private:
	int frame_life;
	int frame_life_beginning;
	int alpha_start;
	double current_scale = 1; // Multiplied by growth factor
	double grow_factor; //  < 1 means shrink 1 stay same, > 1 grow
};

} /* namespace spacenomad */

#endif /* SRC_FADING_PROJECTILE_HXX_ */
