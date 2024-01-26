#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "object.hpp"

/*
	PROJECTILE
	---------------------------------------------------------------------
	This is the class that describes a projectile
*/

namespace Asteroids {

class Projectile : public Object {
   public:
	Projectile();


	// Init: implemented as required by class Object
	void Init(glm::vec2 pos, glm::vec2 speedDirection) override;


   private:
	// points: the array of points defining the triangles of the spaceship
	float points[numTriangles_Projectile * 3 * 2] = {0};


   protected:
	// projectile can exit the screen: the default "false" is overwritten here
	bool canExitTheScreen() const override {
		return true;
	};

	// set number of triangles to be rendered
	virtual int numTriangles() const override {
		return numTriangles_Projectile;
	};
};

}  // namespace Asteroids

#endif
