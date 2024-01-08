#include "spaceship.hpp"

using namespace Asteroids;

Spaceship::Spaceship() : lastMousePos(0.0f) {}

void Spaceship::Init(glm::vec2 pos, glm::vec2 speed) {
	shader = Shader("./resources/shaders/shader.vs", "./resources/shaders/shader.fs");

	this->pos = pos;
	this->speed = glm::vec2(0.5);
	angle = 0;

	radius = 0.1;

	// clang-format off
	float tmpPoints[NumTrianglesSpaceship * 3 * 2] = {
		(float) radius * root2div2,		(float) radius * root2div2,
		(float) -radius * root2div2,	(float) radius * root2div2,
		(float) radius * root2div2,		(float) -radius * root2div2,

		(float) -radius * root2div2,	(float) -radius * root2div2,
		(float) -radius * root2div2,	(float) radius * root2div2,
		(float) radius * root2div2,		(float) -radius * root2div2,

		(float) radius * root2div2,		(float) radius * root2div2,
		(float) -radius * root2div2,	(float) radius * root2div2,
		(float) 0,						(float) radius,
	};
	// clang-format on

	memcpy(points, tmpPoints, NumTrianglesSpaceship * 3 * 2 * sizeof(float));

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	updateTransform();
}

void Spaceship::Draw() const {
	shader.use();
	shader.setMat4("model", transform);
	shader.setVec3("objectColor", 1, 0, 0);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3 * NumTrianglesSpaceship);
}

void Spaceship::MoveDir(direction dir) {
	glm::vec2 offset(0);

	switch(dir) {
		case up: offset.y = speed.x * deltaTime; break;
		case down: offset.y = -speed.x * deltaTime; break;
		case left: offset.x = -speed.y * deltaTime; break;
		case right: offset.x = speed.y * deltaTime; break;
	}

	pos = pos + offset;

	PointTo(lastMousePos);

	limitMovementToScreen();
	updateTransform();
}

void Spaceship::PointTo(glm::vec2 mousePos) {
	lastMousePos = mousePos;

	float newAngle = angleBetween(pos + YaxisVersor, mousePos, pos) - 3.14;
	if(newAngle == newAngle) angle = newAngle;  // to avoid indeterminate forms
	updateTransform();
}
