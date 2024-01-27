#include "spaceship.hpp"

#include "parameters.hpp"

using namespace Asteroids;

Spaceship::Spaceship() : lastMousePos(0.0f) {}

void Spaceship::Init(glm::vec2 pos, float angle) {
	shader = Shader("./resources/shaders/texture.vs", "./resources/shaders/texture.fs");

	this->pos = pos;
	this->speed = glm::vec2(0.5);
	angle = 0;

	radius = radius_Spaceship;

	// clang-format off
	float tmpPoints[numTriangles_Spaceship * 3 * 2 * 2] = {
		(float) radius,		(float) radius,		1,	1,
		(float) -radius,	(float) radius, 	0,	1,
		(float) radius,		(float) -radius,	1,	0,

		(float) -radius,	(float) -radius,	0,	0,
		(float) -radius,	(float) radius,		0,	1,
		(float) radius,		(float) -radius,	1,	0,
	};
	// clang-format on

	memcpy(points, tmpPoints, numTriangles_Spaceship * 3 * 2 * 2 * sizeof(float));

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) (2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	addTexture("./resources/textures/spaceship.png");

	// update transform matrix
	updateTransform();
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

Projectile Spaceship::Shoot() {
	Projectile p;
	glm::vec2 dir(-sin(angle), cos(angle));
	p.Init(pos + radius * scaleVector(dir), pi_float + angleBetweenVerticalDir(scaleVector(scaleVector(dir))));
	return p;
}
