/*
 * menu_mode.cxx
 *
 *  Created on: Jan 3, 2015
 *      Author: Kristofer
 */


#include "game_mode.hxx"
#include "main.hxx"
#include "menu_mode.hxx"
#include "planet_generation/planet_generation_mode.hxx"

#include <iostream>

namespace spacenomad {

static bool menu_option_start(main_class& main)
{
	main.push_mode(new game_mode(main.ren, main.win));
	return false;
}

static bool menu_option_option(main_class& main)
{
	return false;
}

static bool menu_option_credits(main_class& main)
{
	return false;
}

static bool menu_option_quit(main_class& main)
{
	return true;
}

menu_mode::menu_mode(SDL_Renderer *ren)
: selection_index(0) // menu bar selection
, menu_options({
	menu_option(menu_option_start, "Play Game"),
			menu_option(menu_option_option, "Options"),
			menu_option(menu_option_credits, "Credits"),
			menu_option(menu_option_quit, "Quit"),
})
, stars(ren)
, pos(0)
{
}

bool menu_mode::processEvents(SDL_Event *event, main_class& main)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		if (event->key.repeat)
			break;

		switch (event->key.keysym.sym)
		{
		// case Up
		case SDLK_UP:
		case SDLK_w:
			if (selection_index > 0)
				selection_index--;
			break;
			// case down
		case SDLK_DOWN:
		case SDLK_s:
			if (selection_index < SPACE_NOMAD_ARRAY_SIZE(menu_options) - 1)
				selection_index++;
			break;

			// case right
		case SDLK_RIGHT:
		case SDLK_d:

			// case enter or space
		case SDLK_KP_ENTER:
		case SDLK_RETURN:
			return menu_options[selection_index].do_thing(main);
			// case derpy testing by Kristofer Brink the one and only who would dare for their name to be like that
		case SDLK_F12:
			main.push_mode(new spacenomad::planet_generation_mode(main.ren));
			return false;
		}
	}

	return false;
}

void
menu_mode::animate()
{
	pos+=3;
}



void
menu_mode::render(SDL_Renderer *ren, camera& display_camera, TTF_Font *font)
{
	display_camera.clear();
	auto clearRadius = 64;
	SDL_Rect font_dst = { (int)pos - 512, -300, 1024, 256 };
	display_camera.considerObject(font_dst, clearRadius);
	SDL_Rect menu_back_dst({ (int)pos - 550/2, 0, 550, 500 });
	display_camera.considerObject(menu_back_dst, clearRadius);
	display_camera.calculateTransforms();

	stars.draw(ren, display_camera);


	// Menu back
	// Draw the menu back. It is a nice blue.
	display_camera.transform(menu_back_dst);
	menu_back_dst.h++;
	SDL_SetRenderDrawColor(ren, 12, 12, 200, 255);
	SDL_RenderFillRect(ren, &menu_back_dst);


	// Draw space_nomad_SDL_texture
	display_camera.transform(font_dst);
	if (font_dst.h != space_nomad_height) {
		space_nomad_height = font_dst.h;
		space_nomad_width = font_dst.w;
		auto space_surf = renderString("Space Nomad", {255, 255, 128}, font_dst);
		space_nomad_texture = createTexture(ren, space_surf);
	}
	int font_new_w;
	SDL_QueryTexture(space_nomad_texture.get(), NULL, NULL, &font_new_w, &font_dst.h);
	font_dst.x += (font_dst.w - font_new_w)/2;
	font_dst.w = font_new_w;
	SDL_RenderCopy(ren, space_nomad_texture.get(), NULL, &font_dst);
	//std::cerr << "font=" << font_dst.x << "," << font_dst.y << "," << font_dst.w << "," << font_dst.h << std::endl;



	// Draw the menu options
	SDL_Rect menu_option_dst({((int)pos - 550/2 + 50), 50, 550 - 2*50, (500 - 150)/4});

	for (int i = 0; i < SPACE_NOMAD_ARRAY_SIZE(menu_options); i++) {
		menu_options[i].render(ren, menu_option_dst, display_camera);
		menu_option_dst.y += (500 - 75)/4;
	}



	// Choose bar
	SDL_Rect choose_dst({(int)pos - 550/2 + 25, 50, 550 - 2*50 + 50, (500 - 150)/4});
	choose_dst.y += (500 - 75) / 4 * selection_index;
	display_camera.transform(choose_dst);
	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 100);
	SDL_RenderFillRect(ren, &choose_dst);
	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_NONE);

	SDL_Rect width_choose_outline;
	width_choose_outline.w = 10;
	display_camera.transform(width_choose_outline);

	for (int i = 0; i < width_choose_outline.w; i++) {
		SDL_RenderDrawRect(ren, &choose_dst);
		choose_dst.x--;
		choose_dst.y--;
		choose_dst.h += 2;
		choose_dst.w += 2;
	}
}

menu_mode::~menu_mode()
{
}

void menu_option::render(SDL_Renderer *ren, const SDL_Rect& menu_option_dst, const camera& display_camera) {
	SDL_Rect this_option_dst(menu_option_dst);
	display_camera.transform(this_option_dst);
	if (last_width != this_option_dst.w
			|| last_height != this_option_dst.h)
	{
		last_width = this_option_dst.w;
		last_height = this_option_dst.h;
		auto menu_option_surf = renderString(text, {255, 255, 255}, this_option_dst);
		texture = createTexture(ren, menu_option_surf);
		SDL_QueryTexture(texture.get(), NULL, NULL, &texture_width, NULL);
	}
	this_option_dst.w = texture_width;
	SDL_RenderCopy(ren, texture.get(), NULL, &this_option_dst);
}

} /* namespace spacenomad */


