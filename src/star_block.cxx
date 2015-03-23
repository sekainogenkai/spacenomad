/*
 * star_block.cxx
 *
 *  Created on: Mar 21, 2015
 *      Author: Kristofer
 */

#include "star_block.hxx"
#include <random>


star_block::star_block(int texture_count)
: stars(1024)
, block_side_length(2048)
{
	// TODO Auto-generated constructor stub
	std::default_random_engine generator;
	std::uniform_int_distribution<int> coord_distribution(0, block_side_length - 1);
	std::uniform_int_distribution<int> texture_distribution(0, texture_count - 1);
	for (auto stars_iter = stars.begin(); stars_iter != stars.end(); stars_iter++) {
		stars_iter->x = coord_distribution(generator);
		stars_iter->y = coord_distribution(generator);
		stars_iter->texture_i = texture_distribution(generator);
	}
}

void star_block::draw(SDL_Renderer *ren, camera& display_camera, SDL_Texture **textures, int offset_x, int offset_y) {
	for (auto stars_iter = stars.cbegin(); stars_iter != stars.cend(); stars_iter++) {
		SDL_Rect dst;
		SDL_QueryTexture(textures[stars_iter->texture_i], NULL, NULL, &dst.w, &dst.h);
		dst.x = offset_x + stars_iter->x;
		dst.y = offset_y + stars_iter->y;
		if (display_camera.transform(&dst))
			SDL_RenderCopyEx(ren, textures[stars_iter->texture_i], NULL, &dst, 0, NULL, SDL_FLIP_NONE);
	}
}

star_block::~star_block() {
	// TODO Auto-generated destructor stub
}

