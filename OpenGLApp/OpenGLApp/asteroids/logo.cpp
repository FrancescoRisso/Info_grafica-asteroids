#include "logo.hpp"

using namespace Asteroids;


Spacevoid::Spacevoid() {}

staticVariablesInitialize_cpp(Spacevoid);

void Spacevoid::Init(glm::vec2 pos) {
	this->basePos = pos;
	this->speed = scaleVector(0.0f * scaleVectorReverse(glm::vec2(cos(angle), sin(angle))));
	this->angle = 0;

	// clang-format off
	float tmpPoints[numTriangles_Spacevoid * 3 * 2 * 2] = {
		(float) radius(),		(float) radius(),		1,	1,
		(float) -radius(),		(float) radius(), 		0,	1,
		(float) radius(),		(float) -radius(),		1,	0,

		(float) -radius(),		(float) -radius(),		0,	0,
		(float) -radius(),		(float) radius(),		0,	1,
		(float) radius(),		(float) -radius(),		1,	0,
	};
	// clang-format on

	addTexture("./resources/textures/SpaceVoid.png");

	initGL(tmpPoints);
}

