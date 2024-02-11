#include "logo.hpp"

using namespace Asteroids;


Spacevoid::Spacevoid() {}

staticVariablesInitialize_cpp(Spacevoid);

void Spacevoid::Init(glm::vec2 pos) {
	this->pos = pos;
	this->speed = scaleVector(0.0f * scaleVectorReverse(glm::vec2(cos(angle), sin(angle))));
	this->angle = 0;

	float width = 1.0;
	float height = 997.0f / 3743.0f;

	scale = 2.0f;

	// clang-format off
	float tmpPoints[numTriangles_Spacevoid * 3 * 2 * 2] = {
		(float) width/2,		(float) height/2,		1,	1,
		(float) -width/2,		(float) height/2, 		0,	1,
		(float) width/2,		(float) -height/2,		1,	0,

		(float) -width/2,		(float) -height/2,		0,	0,
		(float) -width/2,		(float) height/2,		0,	1,
		(float) width/2,		(float) -height/2,		1,	0,
	};
	// clang-format on

	addTexture("./resources/textures/SpaceVoid.PNG");

	initGL(tmpPoints);
}
