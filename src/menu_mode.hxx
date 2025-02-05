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
#include "star_field.hxx"

namespace spacenomad {

class menu_option{
public:
	typedef bool (*do_thing_func_t)(main_class& main);
	do_thing_func_t do_thing;
	menu_option(do_thing_func_t do_thing, std::string&& text)
	: do_thing(do_thing)
	, text(text)
	{
	}
	void render(SDL_Renderer *ren, const SDL_Rect& menu_option_dst, const camera& display_camera);
private:
	std::string text;
	space_nomad_SDL_Texture_unique_ptr texture;
	int last_width=-1;
	int last_height=-1;
	int texture_width=-1;
};

class menu_mode : public mode
{
public:
	menu_mode(SDL_Renderer *ren);
	virtual bool processEvents(SDL_Event *event, main_class& main);
	virtual void animate();
	virtual void render(SDL_Renderer* ren, camera& display_camera, TTF_Font* font);
	virtual ~menu_mode();
private:
	unsigned int selection_index;
	menu_option menu_options[4];
	star_field stars;
	double pos;
	space_nomad_SDL_Texture_unique_ptr space_nomad_texture;
	int space_nomad_width=-1;
	int space_nomad_height=-1;

};

} /* namespace spacenomad */


#endif /* SRC_MENU_MODE_HXX_ */
