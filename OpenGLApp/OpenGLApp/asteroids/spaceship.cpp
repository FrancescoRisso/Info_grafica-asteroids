#include "spaceship.h"

using namespace Asteroids;

Spaceship::Spaceship() : shader() {}

void Spaceship::Init() {
	shader = Shader("./resources/shaders/shader.vs", "./resources/shaders/shader.fs");

	pos = glm::vec3((float) 0);
	angle = 0;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	updateTransform();
}

void Spaceship::Draw() {
	shader.use();
	shader.setMat4("model", transform);
	shader.setVec3("objectColor", 1, 0, 0);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 9);
}

void Spaceship::updateTransform() {
	transform = glm::mat4((float) 1);
	transform = glm::translate(transform, glm::vec3(pos, 0));
	transform = glm::rotate(transform, angle, glm::vec3(0, 0, 1));
}

void Spaceship::Move(direction dir) {
	glm::vec2 offset(0);

	switch(dir) {
		case up: offset.y = moveBase; break;
		case down: offset.y = -moveBase; break;
		case left: offset.x = -moveBase; break;
		case right: offset.x = moveBase; break;
	}

	pos = pos + offset;

	if(pos.x + radius > 1) pos.x = 1 - radius;
	if(pos.x - radius < -1) pos.x = radius - 1;
	if(pos.y + radius > 1) pos.y = 1 - radius;
	if(pos.y - radius < -1) pos.y = radius - 1;

	updateTransform();
}

void Spaceship::PointTo(glm::vec2 mousePos) {
	float newAngle = angleBetween(pos + YaxisVersor, mousePos, pos) - 3.14;
	if(newAngle == newAngle) angle = newAngle;  // to avoid indeterminate forms
	updateTransform();
}
