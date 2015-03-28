/*
 * starfield.hxx
 *
 *  Created on: Mar 21, 2015
 *      Author: Kristofer
 */

#ifndef SRC_STAR_FIELD_HXX_
#define SRC_STAR_FIELD_HXX_


extern "C" {
#include <SDL.h>
}

#include "main.hxx"
#include "star_block.hxx"
#include <vector>


struct star_layer {
	std::vector<star_block> star_blocks;
	int grid_x_min, grid_y_min;
	int grid_x_max, grid_y_max;
	double parallax_factor;
	star_layer(double parallax_factor);
	void draw(SDL_Renderer* ren, camera& display_camera, SDL_Texture **textures, int textures_count, std::default_random_engine& random_engine);
	void add_block(int textures_count, int block_side_length, std::default_random_engine& random_engine, int grid_x, int grid_y);
};

class star_field {
public:
	star_field(SDL_Renderer *ren);
	void draw(SDL_Renderer* ren, camera& display_camera);
	virtual ~star_field();
private:
	star_layer layers[3];
	space_nomad_SDL_Texture_unique_ptr star_0_texture;
	space_nomad_SDL_Texture_unique_ptr star_1_texture;
	space_nomad_SDL_Texture_unique_ptr star_2_texture;
	SDL_Texture *star_texture_ptrs[3];
	std::default_random_engine random_engine;
};


#endif /* SRC_STAR_FIELD_HXX_ */
