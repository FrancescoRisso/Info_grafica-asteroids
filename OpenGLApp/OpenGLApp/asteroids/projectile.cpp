#include "projectile.hpp"

using namespace Asteroids;

Projectile::Projectile() {}


void Projectile::Init(glm::vec2 pos, glm::vec2 speedDirection) {
	shader = Shader("./resources/shaders/shader.vs", "./resources/shaders/shader.fs");

	this->pos = pos;
	this->speed = scaleVector(1.0f * scaleVectorReverse(glm::normalize(speedDirection)));
	angle = angleBetweenVerticalDir(speed);

	radius = 0.01;

	// clang-format off
	float tmpPoints[NumTrianglesProjectile * 3 * 2] = {
		(float) radius * root2div2,		(float) radius * root2div2,
		(float) -radius * root2div2,	(float) radius * root2div2,
		(float) radius * root2div2,		(float) -radius * root2div2,

		(float) -radius * root2div2,	(float) -radius * root2div2,
		(float) -radius * root2div2,	(float) radius * root2div2,
		(float) radius * root2div2,		(float) -radius * root2div2,
	};
	// clang-format on

	memcpy(points, tmpPoints, NumTrianglesProjectile * 3 * 2 * sizeof(float));

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	updateTransform();
}

void Projectile::Draw() const {
	shader.use();
	shader.setMat4("model", transform);
	shader.setVec3("objectColor", 1, 0, 0);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 9);
}
