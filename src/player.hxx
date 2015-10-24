/*
 * player.hxx
 *
 *  Created on: Mar 20, 2015
 *      Author: Kristofer
 */

#ifndef SRC_PLAYER_HXX_
#define SRC_PLAYER_HXX_

#include "active_object.hxx"

namespace spacenomad {

class universe;

class player: public active_object {
public:
	player(SDL_Renderer *ren, const char *textureFilename);
	bool up;
	bool down;
	bool left;
	bool right;
	bool shift;
	bool space;
	bool shot;
	virtual void animate();
	void draw(SDL_Renderer *ren, const camera& displayCamera, universe& universe);
	void set_mouse_pos(int x, int y);
	void start_shooting();
	void stop_shooting();

	virtual ~player();
private:
	void shoot(double angle, int barrel_length, int speed, universe& universe, SDL_Renderer *ren);
	space_nomad_SDL_Texture_unique_ptr gun_barrel_tex;
	SDL_Point mouse_pos;
};

} /* namespace spacenomad*/

#endif /* SRC_PLAYER_HXX_ */
