#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "object.hpp"

/*
	PROJECTILE
	---------------------------------------------------------------------
	This is the class that describes a projectile
*/

#define NumTrianglesProjectile 2

namespace Asteroids {

class Projectile : public Object {
   public:
	Projectile();


	// Draw: implemented as required by class Object
	void Draw() const override;


	// Init: implemented as required by class Object
	void Init(glm::vec2 pos, glm::vec2 speedDirection) override;


   private:
	// points: the array of points defining the triangles of the spaceship
	float points[NumTrianglesProjectile * 3 * 2] = {0};


   protected:
	// projectile can exit the screen: the default "false" is overwritten here
	bool canExitTheScreen() const override {
		return true;
	};
};

}  // namespace Asteroids

#endif
