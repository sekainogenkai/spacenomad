/*
 * universe.hxx
 *
 *  Created on: Apr 3, 2015
 *      Author: Kristofer
 */

#ifndef SRC_UNIVERSE_HXX_
#define SRC_UNIVERSE_HXX_

#include "object_field.hxx"
#include "player.hxx"
#include <memory>
#include <vector>

namespace spacenomad {

class universe {
public:
	// Gravitational constant.
	static constexpr double G = 10;

	universe(SDL_Renderer *ren, player& player);
	void animate();
	void draw(SDL_Renderer *ren, camera& displayCamera);
	void add_universal_object(std::unique_ptr<object>&& object);
	virtual ~universe();
private:
	object_field objects;
	std::vector<std::unique_ptr<object>> universal_objects;
	player& myPlayer;
};

} /* namespace spacenomad*/

#endif /* SRC_UNIVERSE_HXX_ */
