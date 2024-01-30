#include "asteroid.hpp"


using namespace Asteroids;

Asteroid::Asteroid() {}


unsigned int Asteroid::VAO_small, Asteroid::VAO_medium, Asteroid::VAO_large;
unsigned int Asteroid::VBO_small, Asteroid::VBO_medium, Asteroid::VBO_large;
bool Asteroid::VAOset_small, Asteroid::VAOset_medium, Asteroid::VAOset_large;
Shader Asteroid::shader;
std::vector<unsigned int> Asteroid::textures;
std::vector<const char*> Asteroid::textureFiles;
bool Asteroid::shaderSet;


void Asteroid::Init(glm::vec2 pos, float angle) {
	this->pos = pos;
	this->speed = scaleVector(speed_Asteroid * scaleVectorReverse(glm::vec2(sin(angle), cos(angle))));
	this->angle = angle;

	// clang-format off
	float tmpPoints[numTriangles_Asteroid * 3 * 2 * 2] = {
		(float) radius(),		(float) radius(),		1,	1,
		(float) -radius(),		(float) radius(), 		0,	1,
		(float) radius(),		(float) -radius(),		1,	0,

		(float) -radius(),		(float) -radius(),		0,	0,
		(float) -radius(),		(float) radius(),		0,	1,
		(float) radius(),		(float) -radius(),		1,	0,
	};
	// clang-format on

#ifdef DEBUG_texturesWithShadow
	addTexture("./resources/textures/asteroid-0.png");
#else
	addTexture("./resources/textures/asteroid-grey.png");
#endif

	initGL(tmpPoints);
}

void Asteroid::Spawn() {
	float firstPos1D = (float) rand() / RAND_MAX * 2 - 1;
	float otherCoord;
	glm::vec2 firstPos(0), speedDir;

	randomizeSize();

	otherCoord = 1 + radius();

	direction side = (direction)(rand() % 4);

	float angleOffset = glm::radians((((float) rand() / RAND_MAX) * 2 - 1) * asteroidAngleRandomness);
	float angle;

	switch(side) {
		case up: firstPos = glm::vec2(firstPos1D, otherCoord); break;
		case down: firstPos = glm::vec2(firstPos1D, -otherCoord); break;
		case right: firstPos = glm::vec2(otherCoord, firstPos1D); break;
		case left: firstPos = glm::vec2(-otherCoord, firstPos1D); break;
	}

	angle = angleBetweenVerticalDir(firstPos);
	angle = angleOffset + angle;
	speedDir = glm::vec2(sin(angle), cos(angle));
	Init(firstPos, angle);
}


bool Asteroid::ShouldSpawn() {
	return rand() % weightOfSpawningAsteroid == 0;
}


void Asteroid::randomizeSize() {
	int mass, sizeRand;
	int massLeft = 0;

	sizeRand = weight_smallAsteroid + weight_mediumAsteroid + weight_largeAsteroid;
	sizeRand = rand() % sizeRand;

	if(sizeRand >= 0 && sizeRand < weight_smallAsteroid) {
		size = small;
		mass = 1;
		return;
	}
	sizeRand -= weight_smallAsteroid;

	if(sizeRand >= 0 && sizeRand < weight_mediumAsteroid) {
		size = medium;
		mass = mass_mediumAsteroid;
	}
	sizeRand -= weight_mediumAsteroid;

	if(sizeRand >= 0) {
		size = large;
		mass = mass_largeAsteroid;
	}

	massLeft = mass;

	while(massLeft > 0) {
		if(massLeft > mass_mediumAsteroid && rand() % 2 == 0) {
			children.push_back(medium);
			massLeft -= mass_mediumAsteroid;
		} else {
			children.push_back(small);
			massLeft--;
		}
	}
}
