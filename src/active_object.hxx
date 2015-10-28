/*
 * active_object.hxx
 *
 *  Created on: Oct 22, 2015
 *      Author: Kristofer
 */

#ifndef SRC_ACTIVE_OBJECT_HXX_
#define SRC_ACTIVE_OBJECT_HXX_

#include "object.hxx"

#include <ctime>
#include <random>


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
	void make_fading_projectile(SDL_Renderer *ren, universe& universe, int radius,
				SDL_Color color, double x, double y, double xVel, double yVel, int spread = 0, int damage = 0, int frame_life = 60, int alpha_start = 255);
	void make_jet(SDL_Renderer *ren, universe& universe, SDL_Color color,
			double x, double y,
			double x_vec, double y_vec,
			int frame_life_min, int frame_life_max,
			int next_frame_min, int next_frame_max,
			double speed_varient_min, double speed_varient_max,
			int radius_min, int radius_max,
			int alpha_start_min, int alpha_start_max
			);
	virtual ~active_object();
protected:
	std::default_random_engine random_engine;
private:
	// For making jet
	int make_jet_next_frame_count = 0;
};

} /* namespace spacenomad */

#endif /* SRC_ACTIVE_OBJECT_HXX_ */
