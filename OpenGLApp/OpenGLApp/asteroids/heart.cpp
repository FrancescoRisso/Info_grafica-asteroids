#include "heart.hpp"


using namespace Asteroids;

Heart::Heart() {}


staticVariablesInitialize_cpp(Heart);


void Heart::Init(glm::vec2 pos, int position) {
	this->basePos = pos;
	this->speed = scaleVector(0.0f * scaleVectorReverse(glm::vec2(cos(angle), sin(angle))));
	this->angle = 0;
	this->position = position;

	// clang-format off
	float tmpPoints[numTriangles_Heart * 3 * 2 * 2] = {
		(float) radius(),		(float) radius(),		1,	1,
		(float) -radius(),		(float) radius(), 		0,	1,
		(float) radius(),		(float) -radius(),		1,	0,

		(float) -radius(),		(float) -radius(),		0,	0,
		(float) -radius(),		(float) radius(),		0,	1,
		(float) radius(),		(float) -radius(),		1,	0,
	};
	// clang-format on

	addTexture("./resources/textures/heart.png");

	initGL(tmpPoints);
}

void Heart::extraUpdateTransform() {
	pos = basePos - scaleVector(glm::vec2(radius() * 2.3 * position, 0));
}
