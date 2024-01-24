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
	glm::vec2 scaledRadius(radius);

	scaledRadius = scaleVector(scaledRadius);

	if(pos.x + scaledRadius.x > 1) pos.x = 1 - scaledRadius.x;
	if(pos.x - scaledRadius.x < -1) pos.x = scaledRadius.x - 1;
	if(pos.y + scaledRadius.y > 1) pos.y = 1 - scaledRadius.y;
	if(pos.y - scaledRadius.y < -1) pos.y = scaledRadius.y - 1;
}

bool Object::isOutOfScreen() {
	glm::vec2 tmpVector(0);

	tmpVector.x = pos.x + radius;
	tmpVector.y = pos.y + radius;
	tmpVector = scaleVector(tmpVector);
	if(tmpVector.x > 1 || tmpVector.y > 1) return true;

	tmpVector.x = pos.x - radius;
	tmpVector.y = pos.y - radius;
	tmpVector = scaleVector(tmpVector);
	if(tmpVector.x < -1 || tmpVector.y < -1) return true;

	return false;
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
