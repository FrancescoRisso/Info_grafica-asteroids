#include "asteroid.hpp"


using namespace Asteroids;

Asteroid::Asteroid() {
	radius = radius_Asteroid;
}


void Asteroid::Init(glm::vec2 pos, glm::vec2 speedDirection) {
	shader = Shader("./resources/shaders/texture.vs", "./resources/shaders/texture.fs");

	this->pos = pos;
	this->speed = scaleVector(speed_Asteroid * scaleVectorReverse(glm::normalize(speedDirection)));
	angle = -angleBetweenVerticalDir(speed);

	// clang-format off
	float tmpPoints[NumTrianglesAsteroid * 3 * 2 * 2] = {
		(float) radius,		(float) radius,		1,	1,
		(float) -radius,	(float) radius, 	0,	1,
		(float) radius,		(float) -radius,	1,	0,

		(float) -radius,	(float) -radius,	0,	0,
		(float) -radius,	(float) radius,		0,	1,
		(float) radius,		(float) -radius,	1,	0,
	};
	// clang-format on

	memcpy(points, tmpPoints, NumTrianglesAsteroid * 3 * 2 * 2 * sizeof(float));

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) (2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture sesttings
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);  // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load("./resources/textures/asteroid-0.png", &width, &height, &nrChannels, 0);
	if(data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	stbi_image_free(data);

	shader.setInt("texture", 0);

	// update transform matrix
	updateTransform();
}

void Asteroid::Draw() const {
	shader.use();
	shader.setMat4("model", transform);
	shader.setVec3("objectColor", 1, 0, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

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
