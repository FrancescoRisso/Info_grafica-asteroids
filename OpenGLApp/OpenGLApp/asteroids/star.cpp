#include "star.hpp"


using namespace Asteroids;

Star::Star() {}


void Star::Init(glm::vec2 pos, glm::vec2 speedDirection) {
	shader = Shader("./resources/shaders/shader.vs", "./resources/shaders/shader.fs");

	this->pos = pos;
	this->speed = scaleVector(speed_Star * scaleVectorReverse(glm::normalize(speedDirection)));
	angle = angleBetweenVerticalDir(speedDirection);

	radius = radius_Star;

	// clang-format off
	float tmpPoints[numTriangles_Star * 3 * 2] = {
		(float) radius * root2div2,		(float) radius * root2div2,
		(float) -radius * root2div2,	(float) radius * root2div2,
		(float) radius * root2div2,		(float) -radius * root2div2,

		(float) -radius * root2div2,	(float) -radius * root2div2,
		(float) -radius * root2div2,	(float) radius * root2div2,
		(float) radius * root2div2,		(float) -radius * root2div2,
	};
	// clang-format on

	memcpy(points, tmpPoints, numTriangles_Star * 3 * 2 * sizeof(float));

	color = glm::vec3(1, 1, 1);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	updateTransform();
}


void Star::Spawn() {
	float posX = (float) rand() / RAND_MAX * 2 - 1;
	float posY = (float) rand() / RAND_MAX * 2 - 1;

	float angle = glm::radians((float) rand() / RAND_MAX * 360);

	Init(glm::vec2(posX, posY), glm::vec2(sin(angle), cos(angle)));
}
