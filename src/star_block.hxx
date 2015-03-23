/*
 * star_block.hxx
 *
 *  Created on: Mar 21, 2015
 *      Author: Kristofer
 */

#ifndef SRC_STAR_BLOCK_HXX_
#define SRC_STAR_BLOCK_HXX_

extern "C" {
#include <SDL.h>
}

#include "camera.hxx"

#include <vector>

struct star {
	int x;
	int y;
	int texture_i;
};

class star_block {
public:
	star_block(int texture_count);
	void draw(SDL_Renderer *ren, camera& display_camera, SDL_Texture **textures, int offset_x, int offset_y);
	virtual ~star_block();
private:
	std::vector<star> stars;
	int block_side_length;
};

#endif /* SRC_STAR_BLOCK_HXX_ */
