/*
 * star_block.cxx
 *
 *  Created on: Mar 21, 2015
 *      Author: Kristofer
 */

#include "star_block.hxx"

#include <iostream>

star_block::star_block(
		int texture_count, int block_size_length,
		std::default_random_engine& random_engine, int grid_x, int grid_y)
: grid_x(grid_x)
, grid_y(grid_y)
, stars(256)
, block_side_length(block_size_length)
{
	std::uniform_int_distribution<int> coord_distribution(0, block_side_length - 1);
	std::uniform_int_distribution<int> texture_distribution(0, texture_count - 1);
	for (auto stars_iter = stars.begin(); stars_iter != stars.end(); stars_iter++) {
		stars_iter->x = coord_distribution(random_engine);
		stars_iter->y = coord_distribution(random_engine);
		stars_iter->texture_i = texture_distribution(random_engine);
	}
}

double star_block::get_x() const {
	return block_side_length * (double)grid_x;
}

double star_block::get_y() const {
	return block_side_length * (double)grid_y;
}

void star_block::snap(int block_size_length, double x, double y, int& grid_x, int& grid_y) {
	grid_x = (int)x/block_size_length;
	grid_y = (int)y/block_size_length;
}

bool star_block::draw(SDL_Renderer *ren, camera& display_camera, SDL_Texture **textures, double parallax_factor) const {
	auto x = get_x();
	auto y = get_y();
	for (auto stars_iter = stars.cbegin(); stars_iter != stars.cend(); stars_iter++) {
		SDL_Rect dst;
		SDL_QueryTexture(textures[stars_iter->texture_i], NULL, NULL, &dst.w, &dst.h);
		dst.x = x + stars_iter->x;
		dst.y = y + stars_iter->y;
		if (display_camera.transform(&dst, parallax_factor))
			SDL_RenderCopyEx(ren, textures[stars_iter->texture_i], NULL, &dst, 0, NULL, SDL_FLIP_NONE);
	}
}

star_block::~star_block() {
	// TODO Auto-generated destructor stub
}

