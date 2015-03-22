/*
 * menu_mode.hxx
 *
 *  Created on: Jan 3, 2015
 *      Author: Kristofer
 */

#ifndef SRC_MENU_MODE_HXX_
#define SRC_MENU_MODE_HXX_

extern "C" {
#include <SDL.h>
}

#include "camera.hxx"
#include "mode.hxx"
#include "star_block.hxx"

class menu_option{
public:
	typedef bool (*do_thing_func_t)(mode *&, SDL_Renderer *ren);
	do_thing_func_t do_thing;
	menu_option(do_thing_func_t do_thing)
	: do_thing(do_thing)
	{
	}
};

class menu_mode : public mode
{
public:
	menu_mode(SDL_Renderer *ren);
	virtual bool processEvents(SDL_Event *event, mode *& new_mode, SDL_Renderer *ren);
	virtual void animate();
	virtual void render(SDL_Renderer* ren, camera& display_camera, TTF_Font* font);
	virtual ~menu_mode();
private:
	space_nomad_SDL_Texture_unique_ptr tex_menu_back;
	space_nomad_SDL_Texture_unique_ptr tex_choose_bar;
	unsigned int selection_index;
	menu_option menu_options[4];
	space_nomad_SDL_Texture_unique_ptr star_0_texture;
	space_nomad_SDL_Texture_unique_ptr star_1_texture;
	space_nomad_SDL_Texture_unique_ptr star_2_texture;
	SDL_Texture *star_texture_ptrs[3];
	star_block stars;
};


#endif /* SRC_MENU_MODE_HXX_ */
