#ifndef _STAR_H
#define _STAR_H

#include "projectile.hpp"

/*
	STAR
	---------------------------------------------------------------------
	This is the class that describes a star
*/

namespace Asteroids {

class Star : public Object {
   public:
	Star();


	/*
		Spawn
		---------------------------------------------------------------------
		Spawns a star in a random location, rotated at a random angle
	*/
	void Spawn();


	// Init: implemented as required by class Object
	void Init(glm::vec2 pos, glm::vec2 speedDirection) override;


   private:
	// points: the array of points defining the triangles of the spaceship
	float points[numTriangles_Star * 3 * 2] = {0};


   protected:
	// projectile can exit the screen: the default "false" is overwritten here
	bool canExitTheScreen() const override {
		return true;
	};

	// set number of triangles to be rendered
	virtual int numTriangles() const override {
		return numTriangles_Star;
	};
};

}  // namespace Asteroids

#endif
