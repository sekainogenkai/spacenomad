/*
 * objectfield.cxx
 *
 *  Created on: May 25, 2015
 *      Author: Kristofer
 */

#include <iostream>
#include "object_field.hxx"
#include "planet.hxx"

object_field_layer::object_field_layer(int block_side_length)
: field_layer(block_side_length) {
}

void
object_field::animate(void(*interact)(object& obj1, object& obj2), player& myPlayer)
{
	objects_layer.animate(interact, myPlayer);
}

void
object_field_layer::add_block(std::default_random_engine& random_engine, int grid_x, int grid_y, SDL_Renderer *ren)
{
	std::cerr << "o_add(" << grid_x << "," << grid_y << ")\n";
	object_blocks.push_back(
			object_block(
					ren,
					random_engine,
					get_block_side_length(),
					grid_x,
					grid_y));
}

void
object_field_layer::citerate(std::function<bool(const block&)> visit)
{
	for (size_t i = object_blocks.size(); i > 0; i--)
		if (visit(object_blocks[i - 1]))
			/**/{auto b = (object_blocks.begin () + i - 1);std::cerr << "cit_del(" << b->get_grid_x() << "," << b->get_grid_y() << ")" << std::endl;
			object_blocks.erase(object_blocks.begin() + i - 1);
			/**/}
}

void
object_field_layer::iterate_objects(std::function<void(object&)> visit)
{
	for (auto block_iter = object_blocks.begin(); block_iter != object_blocks.cend(); block_iter++)
		block_iter->iterate(visit);
}

void
object_field_layer::animate(void(*interact)(object&, object&), player& myPlayer) {
	// In the future, do objects within each block, then objects between
	// adjacent blocks. For now, just be incorrect and only have things
	// inside a block interact.
	for (auto block_iter = object_blocks.begin(); block_iter != object_blocks.end(); block_iter++)
	{
		for (auto obj_iter = block_iter->objects.begin(); obj_iter != block_iter->objects.end(); obj_iter++) {
			auto obj = obj_iter->get();
			for (auto obj2_iter = obj_iter + 1 ; obj2_iter != block_iter->objects.end(); obj2_iter++) {
				auto obj2 = obj2_iter->get();
				interact(*obj, *obj2);
			}
			interact(*obj, myPlayer);
			obj->animate();
		}
	}
}

object_field_layer::~object_field_layer() {
}

object_field::object_field()
: field(4096)
, objects_layer(get_block_side_length()) {
}

void
object_field::iterate(std::function<void(field_layer&)> visit) {
	visit(objects_layer);
}

object_field::~object_field() {
}
