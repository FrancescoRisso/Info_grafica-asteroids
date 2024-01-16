#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "object.hpp"

/*
	ASTEROID
	---------------------------------------------------------------------
	This is the class that describes an asteroid
*/

#define NumTrianglesAsteroid 2

namespace Asteroids {

class Asteroid : public Object {
   public:
	Asteroid();


	// Draw: implemented as required by class Object
	void Draw() const override;


	// Init: implemented as required by class Object
	void Init(glm::vec2 pos, glm::vec2 speed) override;


   private:
	// points: the array of points defining the triangles of the spaceship
	float points[NumTrianglesAsteroid * 3 * 2] = {0};


   protected:
	// Asteroid can exit the screen: the default "false" is overwritten here
	bool canExitTheScreen() const override {
		return true;
	};
};

}  // namespace Asteroids

#endif
