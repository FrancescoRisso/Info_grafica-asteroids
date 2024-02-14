#ifndef _LOGO_H
#define _LOGO_H

#include "../model.hpp"
#include "logo.hpp"
#include "object.hpp"


namespace Asteroids {

class Spacevoid : public Object {
   public:
	Spacevoid();

	void Init(glm::vec2 pos, float angle) override {};
	void Init(glm::vec2 pos);

	staticVariablesAndFunctionDefinitions_hpp(Spacevoid);

	void Draw() const override;

   protected:
	// projectile can exit the screen: the default "false" is overwritten here
	bool canExitTheScreen() const override {
		return true;
	};

	// set number of triangles to be rendered
	int numTriangles() const override {
		return 0;
	};

	availableShaders shaderChoice() const override {
		return shader_3D;
	}

	float radius() const override {
		return radius_Spacevoid;
	}
};

}  // namespace Asteroids
#endif
