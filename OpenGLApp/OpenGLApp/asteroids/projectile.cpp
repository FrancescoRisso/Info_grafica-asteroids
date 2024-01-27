#include "projectile.hpp"

#include "parameters.hpp"


using namespace Asteroids;

Projectile::Projectile() {}


void Projectile::Init(glm::vec2 pos, float angle) {
	shader = Shader("./resources/shaders/shader.vs", "./resources/shaders/shader.fs");

	this->pos = pos;
	this->speed = scaleVector(speed_Projectile * scaleVectorReverse(glm::vec2(sin(angle), cos(angle))));
	this->angle = -angleBetweenVerticalDir(speed);

	radius = radius_Projectile;

	// clang-format off
	float tmpPoints[numTriangles_Projectile * 3 * 2] = {
		(float) radius * root2div2,		(float) radius * root2div2,
		(float) -radius * root2div2,	(float) radius * root2div2,
		(float) radius * root2div2,		(float) -radius * root2div2,

		(float) -radius * root2div2,	(float) -radius * root2div2,
		(float) -radius * root2div2,	(float) radius * root2div2,
		(float) radius * root2div2,		(float) -radius * root2div2,
	};
	// clang-format on

	memcpy(points, tmpPoints, numTriangles_Projectile * 3 * 2 * sizeof(float));

	color = glm::vec3(1, 0, 0);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	updateTransform();
}
