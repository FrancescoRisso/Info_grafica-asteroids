#include "star.hpp"


using namespace Asteroids;

Star::Star() {}


void Star::Init(glm::vec2 pos, float angle) {
	this->pos = pos;
	this->speed = scaleVector(speed_Star * scaleVectorReverse(glm::vec2(cos(angle), sin(angle))));
	this->angle = angle;

	// clang-format off
	float tmpPoints[numTriangles_Star * 3 * 2] = {
		(float) radius() * root2div2,		(float) radius() * root2div2,
		(float) -radius() * root2div2,		(float) radius() * root2div2,
		(float) radius() * root2div2,		(float) -radius() * root2div2,

		(float) -radius() * root2div2,		(float) -radius() * root2div2,
		(float) -radius() * root2div2,		(float) radius() * root2div2,
		(float) radius() * root2div2,		(float) -radius() * root2div2,
	};
	// clang-format on

	initGL(tmpPoints);
}


void Star::Spawn() {
	float posX = (float) rand() / RAND_MAX * 2 - 1;
	float posY = (float) rand() / RAND_MAX * 2 - 1;

	float angle = glm::radians((float) rand() / RAND_MAX * 360);

	Init(glm::vec2(posX, posY), angle);
}
