#include "spaceship.hpp"

#include "parameters.hpp"

using namespace Asteroids;

Spaceship::Spaceship() : lastMousePos(0.0f) {}

void Spaceship::Init(glm::vec2 pos, glm::vec2 speedDirection) {
	shader = Shader("./resources/shaders/texture.vs", "./resources/shaders/texture.fs");

	this->pos = pos;
	this->speed = glm::vec2(0.5);
	angle = 0;

	radius = radius_Spaceship;

	// clang-format off
	float tmpPoints[NumTrianglesSpaceship * 3 * 2 * 2] = {
		(float) radius,		(float) radius,		1,	1,
		(float) -radius,	(float) radius, 	0,	1,
		(float) radius,		(float) -radius,	1,	0,

		(float) -radius,	(float) -radius,	0,	0,
		(float) -radius,	(float) radius,		0,	1,
		(float) radius,		(float) -radius,	1,	0,
	};
	// clang-format on

	memcpy(points, tmpPoints, NumTrianglesSpaceship * 3 * 2 * 2 * sizeof(float));

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
	unsigned char* data = stbi_load("./resources/textures/spaceship.png", &width, &height, &nrChannels, 0);
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

void Spaceship::Draw() const {
	shader.use();
	shader.setMat4("model", transform);
	shader.setVec3("objectColor", 1, 0, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

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

Projectile Spaceship::Shoot() {
	Projectile p;
	glm::vec2 dir(-sin(angle), cos(angle));
	p.Init(pos + radius * scaleVector(dir), scaleVector(dir));
	return p;
}
