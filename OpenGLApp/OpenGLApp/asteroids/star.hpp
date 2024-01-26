#ifndef _STAR_H
#define _STAR_H

#include "projectile.hpp"

/*
	STAR
	---------------------------------------------------------------------
	This is the class that describes a star
*/

#define NumTrianglesStar 2

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


	// Draw: implemented as required by class Object
	void Draw() const override;


	// Init: implemented as required by class Object
	void Init(glm::vec2 pos, glm::vec2 speedDirection) override;


   private:
	// points: the array of points defining the triangles of the spaceship
	float points[NumTrianglesStar * 3 * 2] = {0};


   protected:
	// projectile can exit the screen: the default "false" is overwritten here
	bool canExitTheScreen() const override {
		return true;
	};
};

}  // namespace Asteroids

#endif
