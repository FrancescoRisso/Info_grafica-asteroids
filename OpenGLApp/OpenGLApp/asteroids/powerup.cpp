#include "powerup.hpp"


using namespace Asteroids;

Powerup::Powerup() {}


staticVariablesInitialize_cpp(Powerup);

unsigned int Powerup::textureIds[];


void Powerup::addTypeTexture(powerup_t type, const char* path) {
	if(type == powerup_NUM) return;

	int id = addTexture(path);
	if(id != -1) Powerup::textureIds[type] = id;
}


void Powerup::Init(glm::vec2 pos, float angle) {
	this->pos = pos;
	this->speed = scaleVector(speed_Powerup * scaleVectorReverse(glm::vec2(sin(angle), cos(angle))));
	this->angle = 0;

	// clang-format off
	float tmpPoints[numTriangles_Powerup * 3 * 2 * 2] = {
		(float) radius(),		(float) radius(),		1,	1,
		(float) -radius(),		(float) radius(), 		0,	1,
		(float) radius(),		(float) -radius(),		1,	0,

		(float) -radius(),		(float) -radius(),		0,	0,
		(float) -radius(),		(float) radius(),		0,	1,
		(float) radius(),		(float) -radius(),		1,	0,
	};
	// clang-format on

	addTypeTexture(extraLife, "./resources/textures/powerup_heart.png");

	initGL(tmpPoints);

	useTexture(Powerup::textureIds[type]);
}


void Powerup::Spawn() {
	float firstPos1D = (float) rand() / RAND_MAX * 2 - 1;
	float otherCoord;
	glm::vec2 firstPos(0);

	otherCoord = 1 + radius();

	direction side = (direction)(rand() % 4);

	type = (powerup_t)(rand() % powerup_NUM);

	float angleOffset = glm::radians((((float) rand() / RAND_MAX) * 2 - 1) * powerupAngleRandomness);
	float angle;

	switch(side) {
		case up: firstPos = glm::vec2(firstPos1D, otherCoord); break;
		case down: firstPos = glm::vec2(firstPos1D, -otherCoord); break;
		case right: firstPos = glm::vec2(otherCoord, firstPos1D); break;
		case left: firstPos = glm::vec2(-otherCoord, firstPos1D); break;
	}

	angle = angleBetweenVerticalDir(firstPos);
	angle = angleOffset + angle;
	Init(firstPos, angle);
}


bool Powerup::shouldSpawn() {
	return ((float) rand() / RAND_MAX) * avgTimeBetweenPowerups < deltaTime;
}


powerup_t Powerup::getType() {
	return type;
}
