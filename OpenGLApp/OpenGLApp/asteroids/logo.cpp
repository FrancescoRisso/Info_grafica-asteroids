
#include "logo.hpp"

using namespace Asteroids;


Spacevoid::Spacevoid() {}

staticVariablesInitialize_cpp(Spacevoid);

Model title;

void Spacevoid::Init(glm::vec2 pos) {
	this->pos = pos;
	this->speed = scaleVector(0.0f * scaleVectorReverse(glm::vec2(cos(angle), sin(angle))));
	this->angle = 0;

	title.Init("./resources/objects/3d-title.obj");

	initGL((float*) 0);
}

void Spacevoid::Draw() const {
	title.Draw(shader);
}
