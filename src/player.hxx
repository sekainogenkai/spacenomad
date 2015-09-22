/*
 * player.hxx
 *
 *  Created on: Mar 20, 2015
 *      Author: Kristofer
 */

#ifndef SRC_PLAYER_HXX_
#define SRC_PLAYER_HXX_

#include "object.hxx"

class player : public object {
public:
	player(SDL_Renderer *ren, const char *textureFilename);
	bool up;
	bool down;
	bool left;
	bool right;
	bool shift;
	bool space;
	virtual void animate();
	void draw(SDL_Renderer *ren, const camera& displayCamera) const;
	void set_mouse_pos(int x, int y);
	void shoot();
	virtual ~player();
private:
	space_nomad_SDL_Texture_unique_ptr gun_barrel_tex;
	SDL_Point mouse_pos;
};

#endif /* SRC_PLAYER_HXX_ */
