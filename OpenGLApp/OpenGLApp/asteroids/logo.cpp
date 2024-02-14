
#include "logo.hpp"

using namespace Asteroids;


Spacevoid::Spacevoid() {}

staticVariablesInitialize_cpp(Spacevoid);

Model title;

extern unsigned int SCR_HEIGHT, SCR_WIDTH;
extern float lastFrame;

glm::vec3 cameraPos = glm::vec3(0, 0, 3);
glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraPos + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);

void Spacevoid::Init(glm::vec2 pos) {
	this->pos = pos;
	this->speed = scaleVector(0.0f * scaleVectorReverse(glm::vec2(cos(angle), sin(angle))));
	this->angle = 0;

	angleX = glm::radians(90.0f);

	scale = 0.4;

	title.Init("./resources/objects/3d-title.obj");

	initGL((float*) 0);
}

void Spacevoid::Draw() const {
	shader.use();

	shader.setMat4("view", viewMatrix);
	shader.setMat4("projection", projection);
	shader.setMat4("model", transform);

	title.Draw(shader);
}

void Spacevoid::Move() {
	angleY = glm::sin(lastFrame) * ((float) titleRotationAngle / 90.0f);
	updateTransform();
}
