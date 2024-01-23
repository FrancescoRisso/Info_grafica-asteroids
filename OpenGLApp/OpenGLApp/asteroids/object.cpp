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


glm::vec2 Object::findRadiusTowards(glm::vec2 p) {
	return radius * scaleVector(glm::normalize(scaleVectorReverse(p - pos)));
}


float Object::findDistanceFrom(glm::vec2 p) {
	glm::vec2 radiusTow = findRadiusTowards(p);
	glm::vec2 delta = scaleVectorReverse(pos + radiusTow - p);
	glm::vec2 deltaWithoutRadius = pos - p;

	if(glm::all(glm::isnan(delta))) return -1;

	if(glm::length(deltaWithoutRadius) < glm::length(radiusTow)) return -1;

	return glm::length(delta);
}


bool Object::collidesWith(Object *o) {
	glm::vec2 vecTowardsOther = findRadiusTowards(o->pos);
	float dist = o->findDistanceFrom(pos + vecTowardsOther);
	return dist <= 0;
}
