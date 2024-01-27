#include "projectile.hpp"

#include "parameters.hpp"


using namespace Asteroids;

Projectile::Projectile() {}


void Projectile::Init(glm::vec2 pos, float angle) {
	this->pos = pos;
	this->speed = scaleVector(speed_Projectile * scaleVectorReverse(glm::vec2(sin(angle), cos(angle))));
	this->angle = -angleBetweenVerticalDir(speed);

	color = glm::vec3(1, 0, 0);

	// clang-format off
	float tmpPoints[numTriangles_Projectile * 3 * 2] = {
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
