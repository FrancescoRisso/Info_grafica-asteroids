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

extern float timeFromLastSpawn;

static int goldenCoolDown = minimumAsteroidsBetweenGolden;

unsigned int Asteroid::texturesAsteroidsID[];


void Asteroid::addGoldenTexture(golden_t level, const char* path) {
	if(level == golden_type_NUM) return;

	int id = addTexture(path);
	if(id != -1) Asteroid::texturesAsteroidsID[level] = id;
}


void Asteroid::Init(glm::vec2 pos, float angle) {
	this->pos = pos;
	this->speed = scaleVector((goldenFlag? setSpeedDifficulty(speed_goldenAsteroid, false) : setSpeedDifficulty(speed_Asteroid,false)) * scaleVectorReverse(glm::vec2(sin(angle), cos(angle))));
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

	updateChildren();

	addGoldenTexture(normal, "./resources/textures/asteroid.png");
	addGoldenTexture(golden, "./resources/textures/golden_asteroid.png");

	initGL(tmpPoints);
}

void Asteroid::Spawn() {
	float firstPos1D = (float) rand() / RAND_MAX * 2 - 1;
	float otherCoord;
	glm::vec2 firstPos(0);

	randomizeSize();
	if(goldenCoolDown<=0 && rand() % 100 <= goldenChance) { goldenFlag = true;
		goldenCoolDown = minimumAsteroidsBetweenGolden;
		size = small;
	} else {
		goldenFlag = false;
		goldenCoolDown--;
	}


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
	Init(firstPos, angle);
	if(goldenFlag)
		useTexture(texturesAsteroidsID[golden]);
	else
		useTexture(texturesAsteroidsID[normal]);
}


bool Asteroid::ShouldSpawn() {
	if(timeFromLastSpawn < timeBetweenSpawns()) return false;
	timeFromLastSpawn = 0;
	return true;
}


void Asteroid::randomizeSize() {
	int sizeRand;

	sizeRand = weight_smallAsteroid() + weight_mediumAsteroid() + weight_largeAsteroid();
	sizeRand = rand() % sizeRand;

	if(sizeRand >= 0 && sizeRand < weight_smallAsteroid()) size = small;
	sizeRand -= weight_smallAsteroid();

	if(sizeRand >= 0 && sizeRand < weight_mediumAsteroid()) size = medium;
	sizeRand -= weight_mediumAsteroid();

	if(sizeRand >= 0) size = large;
}

void Asteroid::updateChildren() {
	int mass = 0;

	numChildren = 0;

	if(size == small) return;

	mass = getMass(size);

	while(mass > 0) {
		if(mass >= mass_mediumAsteroid && size != medium && rand() % 2 == 0) {
			children.push_back(medium);
			mass -= mass_mediumAsteroid;
		} else {
			children.push_back(small);
			mass--;
		}
	}
	numChildren = children.size();

	// generate the orientations of the children
	std::vector<float> angles;

	float prevDist;

	int baseAngle = -angleBetweenVerticalDir(speed) * 180 / pi_float;

	int numTries = 0;


	int minDelta = 0;

	while(minDelta < 20 && numTries < 5) {
		angles.clear();

		glm::vec2 sum(-conservedMomentum_Asteroid * speed / setSpeedDifficulty(speed_Asteroid,false) * (float) Asteroid::getMass(size));
		glm::vec2 tmp(0);

		// start with random values
		for(int child = 0; child < numChildren; child++) {
			angles.push_back(baseAngle + rand() % 360);
			glm::vec2 foo = glm::vec2(sin(glm::radians(angles[child])), cos(glm::radians(angles[child])));
			sum += foo;
		}

		prevDist = glm::length(sum);

		int withoutChange = 0;
		int id = 0;

		// tune them in such a way that the momentum is almost conserved
		while(glm::length(sum) > 0.001) {
			sum -= glm::vec2(sin(glm::radians(angles[id])), cos(glm::radians(angles[id])));

			tmp = sum + glm::vec2(sin(glm::radians(angles[id] + 1)), cos(glm::radians(angles[id] + 1)));
			float l = glm::length(tmp);
			if(glm::length(tmp) < prevDist) {
				prevDist = glm::length(tmp);
				angles[id]++;
				sum += glm::vec2(sin(glm::radians(angles[id])), cos(glm::radians(angles[id])));
				withoutChange = 0;
				id = (id + 1) % numChildren;
				continue;
			}

			tmp = sum + glm::vec2(sin(glm::radians(angles[id] - 1)), cos(glm::radians(angles[id] - 1)));
			l = glm::length(tmp);
			if(glm::length(tmp) < prevDist) {
				prevDist = glm::length(tmp);
				angles[id]--;
				sum += glm::vec2(sin(glm::radians(angles[id])), cos(glm::radians(angles[id])));
				withoutChange = 0;
				id = (id + 1) % numChildren;
				continue;
			}

			sum += glm::vec2(sin(glm::radians(angles[id])), cos(glm::radians(angles[id])));
			id = (id + 1) % numChildren;
			withoutChange++;
			if(withoutChange == numChildren + 2) break;
		}


		minDelta = abs(angles[0] - angles[1]);
		for(int i = 0; i < numChildren; i++) {
			for(int j = i; j < numChildren; j++)
				if(abs(angles[i] - angles[j]) < minDelta) minDelta = abs(angles[i] - angles[j]);
		}

		numTries++;
	}

	for(int i = 0; i < numChildren; i++) childrenAngles.push_back(glm::radians(angles[i]));

	useTexture(texturesAsteroidsID[normal]);
}


bool Asteroid::hasChildren() {
	return children.size() != 0;
}


Asteroid Asteroid::getChild() {
	Asteroid tmpAsteroid;

	tmpAsteroid.size = children.back();
	children.pop_back();
	tmpAsteroid.goldenFlag = false;
	tmpAsteroid.Init(pos, childrenAngles.back());
	childrenAngles.pop_back();
	//tmpAsteroid.useSameTextureAs(this);
	tmpAsteroid.useTexture(texturesAsteroidsID[normal]);

	return tmpAsteroid;
}


int Asteroid::getMass(size_t s) {
	switch(s) {
		case small: return 1;
		case medium: return mass_mediumAsteroid;
		case large: return mass_largeAsteroid;
		default: return Asteroid::getMass(medium);
	}
}
