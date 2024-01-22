#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "object.hpp"

/*
	ASTEROID
	---------------------------------------------------------------------
	This is the class that describes an asteroid
*/

#define NumTrianglesAsteroid 2

// A freshly spawned asteroid's speed points to the center of the screen
// plus or minus a random value <= AsteroidAngleRandomness (in deg)
#define AsteroidAngleRandomness 30

namespace Asteroids {

class Asteroid : public Object {
   public:
	Asteroid();


	// Draw: implemented as required by class Object
	void Draw() const override;


	// Init: implemented as required by class Object
	void Init(glm::vec2 pos, glm::vec2 speed) override;


	/*
		Spawn
		---------------------------------------------------------------------
		Executes the Init(), spawning an asteroid in a random place on the
		border of the screen, with a random initial speed
	*/
	void Spawn();


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
