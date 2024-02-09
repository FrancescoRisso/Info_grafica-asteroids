#ifndef _HEART_H
#define _HEART_H

#include "object.hpp"

/*
	HEART
	---------------------------------------------------------------------
	This is the class that describes a heart
*/

namespace Asteroids {

class Heart : public Object {
   public:
	Heart();


	// Init: implemented as required by class Object
	void Init(glm::vec2 pos, float angle) override {};
	void Init(glm::vec2 pos, int position);


	staticVariablesAndFunctionDefinitions_hpp(Heart);


   protected:
	// projectile can exit the screen: the default "false" is overwritten here
	bool canExitTheScreen() const override {
		return true;
	};

	// set number of triangles to be rendered
	int numTriangles() const override {
		return numTriangles_Heart;
	};

	availableShaders shaderChoice() const override {
		return shader_withTexture;
	}

	float radius() const override {
		return radius_Heart;
	}

	void extraUpdateTransform() override;

   private:
	glm::vec2 basePos;
	int position = 0;
};

}  // namespace Asteroids

#endif
