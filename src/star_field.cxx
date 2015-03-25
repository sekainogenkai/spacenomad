/*
 * starfield.cxx
 *
 *  Created on: Mar 21, 2015
 *      Author: Kristofer
 */

#include "main.hxx"
#include "star_field.hxx"

#include <algorithm>
#include <ctime>
#include <iostream>

const int block_side_length = 4096;

star_field::star_field(SDL_Renderer *ren)
: star_0_texture(loadTexture(ren, "star_field/star_0.png"))
, star_1_texture(loadTexture(ren, "star_field/star_1.png"))
, star_2_texture(loadTexture(ren, "star_field/star_2.png"))
, star_texture_ptrs {
	star_0_texture.get(),
	star_1_texture.get(),
	star_2_texture.get(),
}
, random_engine(time(NULL))
{
}

void star_field::draw(SDL_Renderer* ren, camera& display_camera) {
	layer.draw(ren, display_camera, star_texture_ptrs, SPACE_NOMAD_ARRAY_SIZE(star_texture_ptrs), random_engine);
}

star_layer::star_layer()
: grid_x_min(0)
, grid_y_min(0)
, grid_x_max(0)
, grid_y_max(0)
{
}

void star_layer::draw(SDL_Renderer* ren, camera& display_camera, SDL_Texture **textures, int textures_count, std::default_random_engine& random_engine) {
	// What two coordinates do we need to hit?
	SDL_Rect visible_area;
	display_camera.get_visible_area(&visible_area);
	int new_grid_x_min, new_grid_y_min;
	star_block::snap(block_side_length, visible_area.x, visible_area.y, new_grid_x_min, new_grid_y_min);
	int new_grid_x_max, new_grid_y_max;
	star_block::snap(block_side_length, visible_area.x + visible_area.w, visible_area.y + visible_area.h, new_grid_x_max, new_grid_y_max);

	// Widen block area by 1 so that stars just outside the screen do not change randomly.
	new_grid_x_min--;
	new_grid_y_min--;
	new_grid_x_max++;
	new_grid_y_max++;
	std::cerr << "min-=(" << new_grid_x_min << "," << new_grid_y_min << "), max+=(" << new_grid_x_max << "," << new_grid_y_max << ")\n";

	// Drop blocks outside our displayed/kept area.
	for (auto i = star_blocks.size(); i > 0; i--)
	{
		auto star_block_i = star_blocks.begin() + i - 1;
		std::cerr << "have (" << star_block_i->grid_x << "," << star_block_i->grid_y << ")\n";
		if (star_block_i->grid_x > new_grid_x_max
				|| star_block_i->grid_x < new_grid_x_min
				|| star_block_i->grid_y > new_grid_y_max
				|| star_block_i->grid_y < new_grid_y_min)
			star_blocks.erase(star_block_i);
	}

	// Intersect our rectangles if they overlap. Otherwise, initialize to a point.
	if (star_blocks.size())
		// Overlap! Intersect
	{
		grid_x_min = std::max(grid_x_min, new_grid_x_min);
		grid_y_min = std::max(grid_y_min, new_grid_y_min);
		grid_x_max = std::min(grid_x_max, new_grid_x_max);
		grid_y_max = std::min(grid_y_max, new_grid_y_max);
	}
	else
		// No overlap, reset.
	{
		std::cerr << "reset\n";
		grid_x_min = grid_x_max = new_grid_x_min;
		grid_y_min = grid_y_max = new_grid_y_min;
		add_block(textures_count, block_side_length, random_engine, grid_x_min, grid_y_min);
	}
	std::cerr << "grid_min=(" << grid_x_min << "," << grid_y_min << "), grid_max=(" << grid_x_max << "," << grid_y_max <<")\n";

	// Grow new blocks as necessary.
	for (; grid_x_min > new_grid_x_min; grid_x_min--)
		for (auto grid_y = grid_y_min; grid_y <= grid_y_max; grid_y++)
			add_block(textures_count, block_side_length, random_engine, grid_x_min - 1, grid_y);
	for (; grid_y_min > new_grid_y_min; grid_y_min--)
		for (auto grid_x = grid_x_min; grid_x <= grid_x_max; grid_x++)
			add_block(textures_count, block_side_length, random_engine, grid_x, grid_y_min - 1);

	for (; grid_x_max < new_grid_x_max; grid_x_max++)
		for (auto grid_y = grid_y_min; grid_y <= grid_y_max; grid_y++)
			add_block(textures_count, block_side_length, random_engine, grid_x_max + 1, grid_y);
	for (; grid_y_max < new_grid_y_max; grid_y_max++)
		for (auto grid_x = grid_x_min; grid_x <= grid_x_max; grid_x++)
			add_block(textures_count, block_side_length, random_engine, grid_x, grid_y_max + 1);

	std::cerr << "num_blocks=" << star_blocks.size() << "\n";

	for (auto block_i = star_blocks.cbegin(); block_i != star_blocks.cend(); block_i++)
		block_i->draw(ren, display_camera, textures);
}

void star_layer::add_block(int textures_count, int block_side_length, std::default_random_engine& random_engine, int grid_x, int grid_y) {
	std::cerr << "add(" << grid_x << "," << grid_y << ")\n";
	star_blocks.push_back(
			star_block(
					textures_count,
					block_side_length,
					random_engine,
					grid_x,
					grid_y));
}

star_field::~star_field() {
}
