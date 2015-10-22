/*
 * object_block.cxx
 *
 *  Created on: May 25, 2015
 *      Author: Kristofer
 */

#include "object_block.hxx"
#include "planet.hxx"

extern "C" {
#include <SDL.h>
}

namespace spacenomad {

object_block::object_block(
		SDL_Renderer *ren,
		std::default_random_engine& random_engine,
		int block_side_length,
		int grid_x,
		int grid_y)
: block(block_side_length, grid_x, grid_y)
{
	std::uniform_int_distribution<int> objects_count_distribution(1, 2);
	std::uniform_int_distribution<int> coord_distribution(0, get_block_side_length() - 1);
	std::uniform_int_distribution<int> vel_distribution(-4, 4);
	auto objects_count = objects_count_distribution(random_engine);
	for (int object_i = 0; object_i < objects_count; object_i++)
	{
		objects.push_back(
				std::unique_ptr<planet>(
						new planet(
								ren,
								get_x() + coord_distribution(random_engine),
								get_y() + coord_distribution(random_engine),
								vel_distribution(random_engine),
								vel_distribution(random_engine),
								2,
								1)));
	}
}

object_block::object_block(object_block&& that)
: block(std::move(that))
, objects(std::move(that.objects))
{
}

object_block&
object_block::operator=(object_block&& that) {
	block::operator=(std::move(that));
	objects = std::move(that.objects);
	return *this;
}

void
object_block::citerate(std::function<void(const object&)> visit)
{
	for (auto iter = objects.cbegin(); iter != objects.cend(); iter++)
		visit(*iter->get());
}

void
object_block::draw(SDL_Renderer *ren, const camera& display_camera) const {
	SDL_SetRenderDrawColor(ren, 255, 255, 128, 255);
	SDL_Rect bounds_rect = { get_x(), get_y(), get_block_side_length(), get_block_side_length(), };
	display_camera.transform(&bounds_rect);
	SDL_RenderDrawRect(ren, &bounds_rect);
	for (auto citer = objects.cbegin(); citer != objects.cend(); citer++) {
		const auto& o = *citer->get();
		o.draw(ren, display_camera);
	}
}

void
object_block::iterate(std::function<void(object&)> visit)
{
	for (auto iter = objects.begin(); iter != objects.end(); iter++)
		visit(*iter->get());
}

object_block::~object_block() {
}

} /* namespace spacenomad */


