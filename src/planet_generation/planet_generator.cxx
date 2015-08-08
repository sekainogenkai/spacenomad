/*
 * planet_generator.cxx
 *
 *  Created on: Jul 31, 2015
 *      Author: Kristofer
 */

#include "planet_generation/brush.hxx"
#include "planet_generation/planet_generator.hxx"

#include <iostream>
#include <cmath>

namespace spacenomad {

planet_generator::planet_generator() {
	planet_type aqueous("aqueous");
	aqueous.add_feature(
			planet_type::FEATURE_TYPE_GROUNDSTUFF,
			{ 64, 192, 64, 200 },
			{ 128, 255, 96, 255 },
			1);
	aqueous.add_feature(
			planet_type::FEATURE_TYPE_GROUNDSTUFF,
			{ 192, 192, 64, 200 },
			{ 255, 255, 128, 255 },
			1);
	aqueous.add_feature(
			planet_type::FEATURE_TYPE_CLOUD,
			{ 200, 200, 200, 32 },
			{ 255, 255, 255, 128 },
			0.25);
	planet_types.push_back(aqueous);

	planet_type dusty("dusty");
	dusty.add_feature(
			planet_type::FEATURE_TYPE_GROUNDSTUFF,
			{ 128, 0, 0, 128 },
			{ 255, 128, 128, 255 },
			1);
	planet_types.push_back(dusty);

	planet_type molten("molten");
	molten.add_feature(
			planet_type::FEATURE_TYPE_GROUNDSTUFF,
			{ 200, 200, 64, 96 },
			{ 255, 255, 128, 128},
			0.5);
	planet_types.push_back(molten);
}

static planet_type::color random_color(std::default_random_engine& random_engine, const planet_type::color& color_min, const planet_type::color& color_max) {
	return {
		std::uniform_int_distribution<int>(color_min.r, color_max.r)(random_engine),
				std::uniform_int_distribution<int>(color_min.g, color_max.g)(random_engine),
				std::uniform_int_distribution<int>(color_min.b, color_max.b)(random_engine),
				std::uniform_int_distribution<int>(color_min.a, color_max.a)(random_engine),
	};
}

planet
planet_generator::generate(SDL_Renderer *ren, std::default_random_engine& random_engine) const {
	// Chose a planet type randomly.
	const auto& planet_type = planet_types[std::uniform_int_distribution<int>(0, planet_types.size() - 1)(random_engine)];
	const auto& features = planet_type.get_features();

	// Make planet_surface
	int size = 1000;
	auto planet_surface = space_nomad_SDL_Surface_unique_ptr(
			SDL_CreateRGBSurface(0, size, size, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000));
	auto planet_surface_ren = space_nomad_SDL_Renderer_unique_ptr(
			SDL_CreateSoftwareRenderer(planet_surface.get()));

	// Fill the square with random color to get ready for the circle
	std::uniform_int_distribution<int> distr_randColor(0, 255);

	auto bgcolor = random_color(random_engine, features[0].color_min, features[1].color_max);
	SDL_SetRenderDrawColor(planet_surface_ren.get(), bgcolor.r, bgcolor.g, bgcolor.b, 255);
	SDL_RenderClear(planet_surface_ren.get());

	// Make brushes
	std::uniform_int_distribution<int> distr_random_number(1, 20);

	// Amount of brushes to make
	int brush_amount = distr_random_number(random_engine);

	std::cout << "I am going to make " << brush_amount << " brushes.";

	SDL_Rect dst;

	for (int i = 0; i < brush_amount; i++) {

		// Get brush width and height
		auto new_brush = brush(random_engine);
		dst.w = new_brush.get_surface()->w;
		dst.h = new_brush.get_surface()->h;

		// Make the surface for the rotated brush to draw onto
		// Calculate max size of rotate brush
		int max_size = sqrt(pow(dst.w, 2) + pow(dst.h, 2));
		std::cerr << "max_size=" << max_size << std::endl;
		auto brush_rotated_surface = space_nomad_SDL_Surface_unique_ptr(
				SDL_CreateRGBSurface(0, max_size, max_size, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000));
		auto brush_rotated_ren = space_nomad_SDL_Renderer_unique_ptr(
				SDL_CreateSoftwareRenderer(brush_rotated_surface.get()));


		auto brush_texture = createTexture(brush_rotated_ren, new_brush.get_surface());

		std::cerr<<"bw=" <<dst.w << ",bh="<<dst.h<<std::endl;
		SDL_QueryTexture(brush_texture.get(), NULL, NULL, &dst.w, & dst.h);
		std::cerr<<"aw=" <<dst.w << ",ah="<<dst.h<<std::endl;
		std::uniform_int_distribution<int> distr_draw_start(0-dst.w, size+dst.w);

		// Random amount of drawing starts and amount of draw time and starting rotation
		std::uniform_int_distribution<int> distr_num_draw_start(0, 100);
		int num_start = distr_num_draw_start(random_engine);
		std::uniform_int_distribution<int> distr_facing_direction(0, 360);
		for (int i = 0; i < num_start; i ++) {
			// Rotation
			int facing_direction = distr_facing_direction(random_engine);


			dst.x = (max_size - dst.w) / 2;
			dst.y = (max_size - dst.h) / 2;
//			SDL_SetRenderDrawColor(brush_rotated_ren.get(), 255, 100, 100, 128);
//			SDL_RenderClear(brush_rotated_ren.get());
//			SDL_SetRenderDrawColor(brush_rotated_ren.get(), 100, 255, 255, 128);
//			SDL_RenderFillRect(brush_rotated_ren.get(), &dst);
			SDL_RenderCopyEx(brush_rotated_ren.get(), brush_texture.get(), NULL, &dst, facing_direction, NULL, SDL_FLIP_NONE);
			auto brush_rotated_texture = createTexture(planet_surface_ren, brush_rotated_surface);

			// Draw start
			dst.x = distr_draw_start(random_engine);
			dst.y = distr_draw_start(random_engine);
			dst.w = max_size;
			dst.h = max_size;

			// Draw time
			std::uniform_int_distribution<int> distr_draw_loops(0, 200);
			int draw_loops = distr_draw_loops(random_engine);
				std::uniform_int_distribution<int> distr_brush_speed_max(0, 20);

			// Drawing around. Right now this isn't done that well.
			for (int i = 0; i < draw_loops; i++) {
				int brush_speed_max = distr_brush_speed_max(random_engine);
				std::uniform_int_distribution<int> distr_move(-brush_speed_max, brush_speed_max);
				distr_move(random_engine); // do stuff
				dst.x += distr_move(random_engine);
				dst.y += distr_move(random_engine);

				SDL_RenderCopy(planet_surface_ren.get(), brush_rotated_texture.get(), NULL, &dst);
			}
		}
	}

	// Turn it into a circle
	dst.x = dst.y = 0;
	dst.w = dst.h = size;
	SDL_SetRenderDrawColor(planet_surface_ren.get(), 0, 0, 0, 0);
	brush::fill_circle(planet_surface_ren.get(), dst, true);

	// Make the thingy be a texture
	return planet(ren, std::move(planet_surface), 0, 0, 0, 0, 0, 5);
}

planet_generator::~planet_generator() {
}

} /* namespace spacenomad */
