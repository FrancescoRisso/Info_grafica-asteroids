#include "spaceship.hpp"

#include "parameters.hpp"

using namespace Asteroids;

Spaceship::Spaceship() : lastMousePos(0.0f) {}

staticVariablesInitialize_cpp(Spaceship);

unsigned int Spaceship::explosionLevelTextures[];

bool bubble = false;


void Spaceship::changeBubble() {
	bubble != bubble;
}


void Spaceship::addExplosionLevelTexture(explosionLevel_t level, const char* path) {
	if(level == explosion_NUM) return;

	int id = addTexture(path);
	if(id != -1) Spaceship::explosionLevelTextures[level] = id;
}

void Spaceship::Init(glm::vec2 pos, float angle) {
	this->pos = pos;
	this->speed = glm::vec2(speed_Spaceship);
	angle = 0;

	// clang-format off
	float tmpPoints[numTriangles_Spaceship * 3 * 2 * 2] = {
		(float) radius(),		(float) radius(),		1,	1,
		(float) -radius(),		(float) radius(), 		0,	1,
		(float) radius(),		(float) -radius(),		1,	0,

		(float) -radius(),		(float) -radius(),		0,	0,
		(float) -radius(),		(float) radius(),		0,	1,
		(float) radius(),		(float) -radius(),		1,	0,
	};
	// clang-format on

	addExplosionLevelTexture(explosion_none, "./resources/textures/spaceship.png");
	addExplosionLevelTexture(bubbled, "./resources/textures/spaceshipBubble_LEGACY.png");
	addExplosionLevelTexture(explosion_1, "./resources/textures/spaceship_exploding_1.png");
	addExplosionLevelTexture(explosion_2, "./resources/textures/spaceship_exploding_2.png");
	addExplosionLevelTexture(explosion_3, "./resources/textures/spaceship_exploding_3.png");

	initGL(tmpPoints);

	setExplosionLevel(explosion_none);
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
	p.Init(pos + radius() * scaleVector(dir), pi_float + angleBetweenVerticalDir(scaleVector(scaleVector(dir))));
	return p;
}


void Spaceship::setExplosionLevel(explosionLevel_t explosionLevel) {
	scale = explosionLevel == explosion_none || explosionLevel == bubbled ? 1 : 1.5;
	useTexture(explosionLevelTextures[explosionLevel]);
	updateTransform();
}
