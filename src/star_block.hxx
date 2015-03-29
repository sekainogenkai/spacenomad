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

#include <random>
#include <vector>

struct star {
	int x;
	int y;
	int texture_i;
};

class star_block {
public:
	star_block(int texture_count, int block_size_length, std::default_random_engine& random_engine,
				int grid_x, int grid_y);
	bool draw(SDL_Renderer *ren, camera& display_camera, SDL_Texture **textures) const;
	double get_x() const;
	double get_y() const;
	/**
	 * \brief Yield the grid_x and grid_y values of the block that should be created if x and y need to be displayed on-screen.
	 */
	static void snap(int block_size_length, double x, double y, int& grid_x, int& grid_y);
	virtual ~star_block();
	int grid_x;
	int grid_y;
private:
	std::vector<star> stars;
	int block_side_length;
};

#endif /* SRC_STAR_BLOCK_HXX_ */
