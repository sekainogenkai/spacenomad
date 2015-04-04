/*
 * universe.cxx
 *
 *  Created on: Apr 3, 2015
 *      Author: Kristofer
 */

#include "universe.hxx"

universe::universe(SDL_Renderer *ren, player& player)
: myPlayer(player)
{
	planets.push_back(std::unique_ptr<planet>(new planet(ren, 300, 400, 8, 2, 2, 400, 1)));
	planets.push_back(std::unique_ptr<planet>(new planet(ren, 300, 0, 8, 1, 2, 400, 1)));
	//myPlanet(ren, 300, 400, 8, 2, 2, 400, 1)
}

void universe::animate() {
	for (auto pt = planets.begin() ; pt != planets.end(); ++pt) {
		auto planet = pt->get();
		planet->animate();
	}
	myPlayer.animate();
}

void universe::draw(SDL_Renderer *ren, camera& displayCamera){
	for (auto pt = planets.begin() ; pt != planets.end(); ++pt) {
		auto planet = pt->get();
		planet->draw(ren, displayCamera);
	}
	// Draw player
	myPlayer.draw(ren, displayCamera);
}

universe::~universe() {

}

