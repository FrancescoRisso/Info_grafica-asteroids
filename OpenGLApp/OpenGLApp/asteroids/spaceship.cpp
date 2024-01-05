#include "spaceship.h"

using namespace Asteroids;

Spaceship::Spaceship() : shader("./resources/shaders/shader.vs", "./resources/shaders/shader.fs") {
	pos = glm::vec3((float) 0);
	angle = 0;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
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
	transform = glm::rotate(transform, angle, glm::vec3(0, 0, 1));
	transform = glm::translate(transform, pos);
}
