#include "asteroid.hpp"

using namespace Asteroids;

Asteroid::Asteroid() {
	radius = radius_Asteroid;
}


void Asteroid::Init(glm::vec2 pos, glm::vec2 speedDirection) {
	shader = Shader("./resources/shaders/shader.vs", "./resources/shaders/shader.fs");

	this->pos = pos;
	this->speed = scaleVector(speed_Asteroid * scaleVectorReverse(glm::normalize(speedDirection)));
	angle = -angleBetweenVerticalDir(speed);

	// clang-format off
	float tmpPoints[NumTrianglesAsteroid * 3 * 2] = {
		(float) radius * root2div2,		(float) radius * root2div2,
		(float) -radius * root2div2,	(float) radius * root2div2,
		(float) radius * root2div2,		(float) -radius * root2div2,

		(float) -radius * root2div2,	(float) -radius * root2div2,
		(float) -radius * root2div2,	(float) radius * root2div2,
		(float) radius * root2div2,		(float) -radius * root2div2,
	};
	// clang-format on

	memcpy(points, tmpPoints, NumTrianglesAsteroid * 3 * 2 * sizeof(float));

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	updateTransform();
}

void Asteroid::Draw() const {
	shader.use();
	shader.setMat4("model", transform);
	shader.setVec3("objectColor", 1, 0, 0);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 9);
}

void Asteroid::Spawn() {
	float firstPos1D = (float) rand() / RAND_MAX * 2 - 1;
	float otherCoord = 1 + radius;
	glm::vec2 firstPos, speedDir;

	direction side = (direction)(rand() % 4);

	float angleOffset = glm::radians((((float) rand() / RAND_MAX) * 2 - 1) * asteroidAngleRandomness);
	float angle;

	switch(side) {
		case up: firstPos = glm::vec2(firstPos1D, otherCoord); break;
		case down: firstPos = glm::vec2(firstPos1D, -otherCoord); break;
		case right: firstPos = glm::vec2(otherCoord, firstPos1D); break;
		case left: firstPos = glm::vec2(-otherCoord, firstPos1D); break;
	}

	angle = angleBetweenVerticalDir(firstPos);
	angle = angleOffset + angle;
	speedDir = glm::vec2(sin(angle), cos(angle));
	Init(firstPos, scaleVector(speedDir));
}


bool Asteroid::ShouldSpawn() {
	return rand() % weightOfSpawningAsteroid == 0;
}
