/*
 * brush_creation.cxx
 *
 *  Created on: Jun 24, 2015
 *      Author: Kristofer
 *
 *  Will create a random brush for making textures on planets.
 */


// Step one, random dotted brush, work on different opacity also.

/*
 * Things to randomize
 * Size
 * Number of "dots", reacts to size
 * Type of dots, reacts to Number of dots
 * Per dot, shape, size, opacity, position
 */
#include "brush_creation.hxx"

#include <iostream>

brush_creation::brush_creation() {
	// DO nothing
}

brush_creation::brush_creation(SDL_Renderer * ren, std::default_random_engine & random_engine) {
	std::cout << "Making brush" << std::endl;
	std::uniform_int_distribution<int> randomNumberDist(0,10000);
	std::cout << "Testing the randomness in brush_creation " << randomNumberDist(random_engine) << std::endl;
}

brush_creation::~brush_creation() {
	// TODO Auto-generated destructor stub
}

