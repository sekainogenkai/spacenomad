/*
 * star_block.cxx
 *
 *  Created on: Mar 21, 2015
 *      Author: Kristofer
 */

#include "star_block.hxx"

#include <iostream>

star_block::star_block(
		SDL_Texture **textures, int texture_count, int block_size_length,
		std::default_random_engine& random_engine, int grid_x, int grid_y)
: block(block_size_length, grid_x, grid_y)
, stars(256)
, textures(textures)
{
	std::uniform_int_distribution<int> coord_distribution(0, get_block_side_length() - 1);
	std::uniform_int_distribution<int> texture_distribution(0, texture_count - 1);
	for (auto stars_iter = stars.begin(); stars_iter != stars.end(); stars_iter++) {
		stars_iter->x = coord_distribution(random_engine);
		stars_iter->y = coord_distribution(random_engine);
		stars_iter->texture_i = texture_distribution(random_engine);
	}
}

void star_block::draw(SDL_Renderer *ren, const camera& display_camera) const {
	SDL_SetRenderDrawColor(ren, 128,255,255,255);
	auto x = get_x();
	auto y = get_y();
	SDL_Rect block_dst = { x, y, get_block_side_length(), get_block_side_length(), };
	display_camera.transform(&block_dst);
	SDL_RenderDrawRect(ren, &block_dst);
	for (auto stars_iter = stars.cbegin(); stars_iter != stars.cend(); stars_iter++) {
		SDL_Rect dst;
		SDL_QueryTexture(textures[stars_iter->texture_i], NULL, NULL, &dst.w, &dst.h);
		dst.x = x + stars_iter->x;
		dst.y = y + stars_iter->y;
		if (display_camera.transform(&dst))
			SDL_RenderCopyEx(ren, textures[stars_iter->texture_i], NULL, &dst, 0, NULL, SDL_FLIP_NONE);
	}
}

star_block::~star_block() {
	// TODO Auto-generated destructor stub
}

