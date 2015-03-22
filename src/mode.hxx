#ifndef _TESTSDL_MODE_HXX
#define _TESTSDL_MODE_HXX

extern "C" {
#include <SDL.h>
#include <SDL_ttf.h>
}

#include "camera.hxx"

class mode {
public:
	/**
	 * \param new_mode
	 *   Set to a new mode to be pushed onto the stack.
	 * \returns
	 *   true to pop this mode from the mode stack.
	 */
	virtual bool processEvents(SDL_Event *event, mode *& new_mode, SDL_Renderer *ren) = 0;
	virtual void animate() = 0;
	virtual void render(SDL_Renderer *ren, camera& displayCamera, TTF_Font *font) = 0;
	virtual ~mode();
};

#endif /* _TESTSDL_MODE_HXX */
