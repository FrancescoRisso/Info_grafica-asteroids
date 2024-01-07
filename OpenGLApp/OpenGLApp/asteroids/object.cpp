#include "object.hpp"

using namespace Asteroids;

Object::Object() : shader() {}

void Object::updateTransform() {
	transform = glm::mat4((float) 1);
	transform = glm::translate(transform, glm::vec3(pos, 0));
	transform = glm::rotate(transform, angle, glm::vec3(0, 0, 1));
}

void Object::Move() {}
