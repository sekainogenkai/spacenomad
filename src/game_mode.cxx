/*
 * game_mode.cxx
 *
 *  Created on: Jan 5, 2015
 *      Author: Kristofer
 */


#include "game_mode.hxx"

game_mode::game_mode(
		SDL_Renderer *ren)
: myPlayer(ren, "astronaut/space_suit.png")
, myStaticPlayer(ren, "astronaut/space_suit.png")
, myPlanet(ren, 300, 400, 8, 2, 2, 400, 1)
, stars(ren)
{
}

bool game_mode::processEvents(SDL_Event *event, mode *& new_mode, SDL_Renderer *ren)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_BACKSPACE:
			return true;
		// WASD
		case SDLK_w:
			myPlayer.up = true;
			break;
		case SDLK_s:
			myPlayer.down = true;
			break;
		case SDLK_a:
			myPlayer.left = true;
			break;
		case SDLK_d:
			myPlayer.right = true;
			break;
		//Shift
		case SDLK_LSHIFT:
			myPlayer.shift = true;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event->key.keysym.sym)
		{
		// WASD
		case SDLK_w:
			myPlayer.up = false;
			break;
		case SDLK_s:
			myPlayer.down = false;
			break;
		case SDLK_a:
			myPlayer.left = false;
			break;
		case SDLK_d:
			myPlayer.right = false;
			break;
		//Shift
		case SDLK_LSHIFT:
			myPlayer.shift = false;
			break;
		}
		break;
	}
	return false;
}
void game_mode::animate()
{
	myPlayer.animate();
	myPlanet.animate();
}
void game_mode::render(SDL_Renderer *ren, camera& displayCamera, TTF_Font *font)
{
	// Set the camera.
	displayCamera.clear();
	myPlayer.considerCamera(displayCamera, 6);
	//myStaticPlayer.considerCamera(displayCamera, 1); // Static player is weird
	displayCamera.calculateTransforms();

	stars.draw(ren, displayCamera);
	myPlanet.draw(ren, displayCamera);
	myPlayer.draw(ren, displayCamera);
	myStaticPlayer.draw(ren, displayCamera);
}

game_mode::~game_mode()
{
}
