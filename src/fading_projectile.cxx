/*
 * fading_projectile.cxx
 *
 *  Created on: Oct 24, 2015
 *      Author: Kristofer
 */

#include "fading_projectile.hxx"
#include <iostream>

namespace spacenomad {


// Filename
fading_projectile::fading_projectile(SDL_Renderer *ren, const std::string& textureFilename, const std::string& textureTrail,
		double x, double y, double xVel, double yVel, int spread, int damage, int frame_life, int alpha_start, double grow_factor)
: projectile(ren, textureFilename.c_str(), textureTrail.c_str(), x, y, xVel, yVel, spread, damage),
  frame_life(frame_life),
  frame_life_beginning(frame_life),
  alpha_start(alpha_start),
  grow_factor(grow_factor)
{
}

// Radius + Color
fading_projectile::fading_projectile(SDL_Renderer *ren, int radius, SDL_Color color,
		double x, double y, double xVel, double yVel, int spread, int damage, int frame_life, int alpha_start, double grow_factor)
:projectile(ren, radius, color,
		x, y, xVel, yVel, spread, damage),
		frame_life(frame_life),
		frame_life_beginning(frame_life),
		alpha_start(alpha_start),
		grow_factor(grow_factor)
{
	// TODO Auto-generated constructor stub

}

void fading_projectile::animate() {

	frame_life--; // Make this thingy starta fading mate.
	if (frame_life <= 0)
		delete_self = true;

	// Make growth factor do something
	current_scale *= grow_factor;

	projectile::animate();

}

void fading_projectile::draw(SDL_Renderer *ren, const camera& displayCamera) const{
	int alpha_fade = (int)((double)alpha_start * (double)frame_life/(double)frame_life_beginning);
	SDL_SetTextureAlphaMod(texture.get(), alpha_fade);

	// Like object draw but scale
	SDL_Rect dst;
		SDL_QueryTexture(texture.get(), NULL, NULL, &dst.w, &dst.h);
		dst.w *= current_scale;
		dst.h *= current_scale;
		dst.x = x - dst.w/2;
		dst.y = y - dst.h/2;
		if (displayCamera.transform(&dst))
			SDL_RenderCopyEx(ren, texture.get(), NULL, &dst, facingDirection, NULL, SDL_FLIP_NONE);
}

fading_projectile::~fading_projectile() {
	// TODO Auto-generated destructor stub
}

} /* namespace spacenomad */
