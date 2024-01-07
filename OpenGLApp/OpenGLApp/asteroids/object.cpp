#include "object.hpp"

using namespace Asteroids;

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;

Object::Object() : shader(), pos(0), speed(0), transform(0) {}

void Object::updateTransform() {
	transform = glm::mat4((float) 1);

	glm::vec2 scale(1);

	if(SCR_WIDTH > SCR_HEIGHT)
		scale.x = (float) SCR_HEIGHT / (float) SCR_WIDTH;
	else
		scale.y = (float) SCR_WIDTH / (float) SCR_HEIGHT;

	transform = glm::scale(transform, glm::vec3(scale, 1));

	transform = glm::translate(transform, glm::vec3(pos / scale, 0));
	transform = glm::rotate(transform, angle, glm::vec3(0, 0, 1));
}

void Object::Move() {}
