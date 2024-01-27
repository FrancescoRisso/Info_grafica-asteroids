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
	void Init(glm::vec2 pos, float angle) override;


   protected:
	// projectile can exit the screen: the default "false" is overwritten here
	bool canExitTheScreen() const override {
		return true;
	};

	// set number of triangles to be rendered
	int numTriangles() const override {
		return numTriangles_Projectile;
	};

	availableShaders shaderChoice() const override {
		return shader_monochromatic;
	}

	float radius() const override {
		return radius_Projectile;
	}
};

}  // namespace Asteroids

#endif
