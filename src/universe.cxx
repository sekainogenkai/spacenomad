/*
 * universe.cxx
 *
 *  Created on: Apr 3, 2015
 *      Author: Kristofer
 */

#include "universe.hxx"
#include <cmath>
#include <iostream>


universe::universe(SDL_Renderer *ren, player& player)
: myPlayer(player)
{
	planets.push_back(std::unique_ptr<planet>(new planet(ren, 300, 400, 8, -9, 2, 400, 1)));
	planets.push_back(std::unique_ptr<planet>(new planet(ren, -700, 0, 8, 1, 2, 400, 1)));
	//myPlanet(ren, 300, 400, 8, 2, 2, 400, 1)
}

// objects colliding
bool universe::circlesAreColliding(const object& obj1, const object& obj2, double& distance) {
	// Triangle to radius added together
	return circlesAreColliding(obj1.getX(), obj1.getY(), obj1.getRadius(), obj2.getX(), obj2.getY(), obj2.getRadius(), distance);
}

bool universe::circlesAreColliding(double x1, double y1, double r1, double x2, double y2, double r2, double& distance)
{
	distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	return distance <= (r1 + r2);
}


static void normalize_vector(double& x, double& y)
{
	auto current_magnitude = sqrt(pow(x, 2) + pow(y, 2));
	x /= current_magnitude;
	y /= current_magnitude;
}

// ojb2 should be planet
void universe::gravity(object& obj1, object& obj2) {
	// Has attractiveness and in gravitational_radius_of_influence
	double distance;

	if ((obj1.getAttractive() || obj2.getAttractive())
		&& circlesAreColliding(obj1.getX(), obj1.getY(), std::max(obj1.getGROI(), obj2.getGROI()), obj2.getX(), obj2.getY(), 0, distance)) {
		double force = 10*obj1.getMass()*obj2.getMass()/pow(distance, 2);

		// norm_x/norm_y are direction towards obj1 from obj2's perspective
		double norm_x = obj1.getX() - obj2.getX();
		double norm_y = obj1.getY() - obj2.getY();
		normalize_vector(norm_x, norm_y);
		if (obj1.getAttractive())
			obj2.applyForce(force, norm_x, norm_y);
		if (obj2.getAttractive())
			obj1.applyForce(force, -norm_x, -norm_y);
	}
}


void universe::animate() {
	for (auto pt = planets.begin() ; pt != planets.end(); ++pt) {
		auto planet = pt->get();
		for (auto pt2 = pt + 1 ; pt2 != planets.end(); ++pt2) {
			auto planet2 = pt2->get();
			gravity(*planet, *planet2);
		}
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

