/*
 * universe.hxx
 *
 *  Created on: Apr 3, 2015
 *      Author: Kristofer
 */

#ifndef SRC_UNIVERSE_HXX_
#define SRC_UNIVERSE_HXX_

#include "planet.hxx"
#include "player.hxx"
#include "object.hxx"
#include <memory>
#include <vector>


class universe {
public:
	universe(SDL_Renderer *ren, player& player);
	void animate();
	void draw(SDL_Renderer *ren, camera& displayCamera);
	virtual ~universe();
private:
	std::vector<std::unique_ptr<planet> > planets;
	player& myPlayer;
};

#endif /* SRC_UNIVERSE_HXX_ */
