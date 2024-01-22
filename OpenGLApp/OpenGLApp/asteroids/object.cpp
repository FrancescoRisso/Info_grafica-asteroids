#include "object.hpp"

using namespace Asteroids;

Object::Object() : shader(), pos(0), speed(0), transform(0) {}

void Object::updateTransform() {
	transform = glm::mat4((float) 1);
	glm::vec2 scale = scaleVector(glm::vec2(1));

	transform = glm::scale(transform, glm::vec3(scale, 1));

	transform = glm::translate(transform, glm::vec3(pos / scale, 0));
	transform = glm::rotate(transform, angle, glm::vec3(0, 0, 1));
}

void Object::Move() {
	pos += deltaTime * speed;

	if(!canExitTheScreen()) limitMovementToScreen();
	updateTransform();
}

void Object::limitMovementToScreen() {
	if(pos.x + radius > 1) pos.x = 1 - radius;
	if(pos.x - radius < -1) pos.x = radius - 1;
	if(pos.y + radius > 1) pos.y = 1 - radius;
	if(pos.y - radius < -1) pos.y = radius - 1;
}

bool Object::isOutOfScreen() {
	return (pos.x - radius > 1) || (pos.x + radius < -1) || (pos.y - radius > 1) || (pos.y + radius < -1);
}


float Object::findDistanceFrom(glm::vec2 p) {
	glm::vec2 dirCenterToP = glm::normalize(p - pos);
	glm::vec2 radiusTowardsP = radius * dirCenterToP;
	return glm::length(scaleVectorReverse(pos + radiusTowardsP - p));
}
