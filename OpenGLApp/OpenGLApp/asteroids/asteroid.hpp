#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "object.hpp"
#include "parameters.hpp"

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


	/*
		Spawn
		---------------------------------------------------------------------
		Executes the Init(), spawning an asteroid in a random place on the
		border of the screen, with a random initial speed
	*/
	void Spawn();


	/*
		ShouldSpawn
		---------------------------------------------------------------------
		Tells if an asteroid should be spawned right now
		---------------------------------------------------------------------
		OUTPUT:
			- whether the main callee should spawn an asteroid or not
	*/
	bool ShouldSpawn();


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
