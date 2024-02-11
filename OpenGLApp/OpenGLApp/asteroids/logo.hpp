#ifndef _LOGO_H
#define _LOGO_H

#include "object.hpp"
#include "logo.hpp"

namespace Asteroids {

class Spacevoid : public Object {
   public:
	Spacevoid();

	void Init(glm::vec2 pos, float angle) override {};
	void Init(glm::vec2 pos);

	staticVariablesAndFunctionDefinitions_hpp(Spacevoid);

   protected:
	// projectile can exit the screen: the default "false" is overwritten here
	bool canExitTheScreen() const override {
		return true;
	};

	// set number of triangles to be rendered
	int numTriangles() const override {
		return numTriangles_Spacevoid;
	};

	availableShaders shaderChoice() const override {
		return shader_withTexture;
	}

	float radius() const override {
		return radius_Spacevoid;
	}
};

}  // namespace Asteroids
#endif
