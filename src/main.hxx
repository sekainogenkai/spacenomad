#ifndef _TESTSDL_MAIN_HXX
#define _TESTSDL_MAIN_HXX

#include <memory>
#include <sstream>
#include <string> 

extern "C" {
#include <SDL.h>
}

#define SPACE_NOMAD_ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

extern int space_nomad_fps;

//Number to string done  Copyright © 2014 Nathan Phillip Brink <ohnobinki@ohnopublishing.net>
template <class T> static std::string str(const T &o)
{
  std::stringstream sb;
  sb << o;
  return sb.str();
}

class space_nomad_SDL_Texture_deleter
{
public:
	void operator()(SDL_Texture *texture);
};
typedef std::unique_ptr<SDL_Texture, space_nomad_SDL_Texture_deleter> space_nomad_SDL_Texture_unique_ptr;
space_nomad_SDL_Texture_unique_ptr loadTexture(SDL_Renderer *ren, const char *filename);

class space_nomad_SDL_Surface_deleter
{
public:
	void operator()(SDL_Surface *surface);
};
typedef std::unique_ptr<SDL_Surface, space_nomad_SDL_Surface_deleter> space_nomad_SDL_Surface_unique_ptr;
space_nomad_SDL_Surface_unique_ptr loadSurface(const char *filename);

#endif /* _TESTSDL_MAIN_HXX */
