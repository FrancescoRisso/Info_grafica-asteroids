#include "parameters.hpp"
#include "./game_logic/game.hpp"
#include <cmath>

extern int destroyedAsteroids;


int weight_smallAsteroid() {
	if(destroyedAsteroids <= 5) return 100;
	if(destroyedAsteroids <= 8) return 95;
	if(destroyedAsteroids <= 11) return 90;
	if(destroyedAsteroids <= 14) return 85;
	if(destroyedAsteroids <= 17) return 80;
	if(destroyedAsteroids <= 20) return 75;
	if(destroyedAsteroids <= 23) return 70;
	if(destroyedAsteroids <= 26) return 65;
	if(destroyedAsteroids <= 29) return 60;
	if(destroyedAsteroids <= 32) return 55;
	if(destroyedAsteroids <= 38) return 50;
	if(destroyedAsteroids <= 43) return 45;
	if(destroyedAsteroids <= 48) return 40;
	if(destroyedAsteroids <= 53) return 35;
	if(destroyedAsteroids <= 59) return 30;
	if(destroyedAsteroids <= 65) return 25;
	if(destroyedAsteroids <= 72) return 20;
	if(destroyedAsteroids <= 82) return 15;
	return 10;
}


int weight_mediumAsteroid() {
	if(destroyedAsteroids <= 5) return 0;
	if(destroyedAsteroids <= 8) return 5;
	if(destroyedAsteroids <= 11) return 10;
	if(destroyedAsteroids <= 17) return 15;
	if(destroyedAsteroids <= 20) return 20;
	if(destroyedAsteroids <= 26) return 25;
	if(destroyedAsteroids <= 29) return 30;
	if(destroyedAsteroids <= 37) return 35;
	if(destroyedAsteroids <= 42) return 40;
	if(destroyedAsteroids <= 47) return 45;
	if(destroyedAsteroids <= 58) return 50;
	if(destroyedAsteroids <= 65) return 55;
	if(destroyedAsteroids <= 87) return 60;
	if(destroyedAsteroids <= 95) return 55;
	if(destroyedAsteroids <= 104) return 50;
	if(destroyedAsteroids <= 112) return 45;
	if(destroyedAsteroids <= 120) return 40;
	if(destroyedAsteroids <= 128) return 35;
	if(destroyedAsteroids <= 137) return 30;
	if(destroyedAsteroids <= 148) return 25;
	if(destroyedAsteroids <= 161) return 20;
	if(destroyedAsteroids <= 188) return 15;
	return 10;
}


int weight_largeAsteroid() {
	if(destroyedAsteroids <= 14) return 0;
	if(destroyedAsteroids <= 23) return 5;
	if(destroyedAsteroids <= 32) return 10;
	if(destroyedAsteroids <= 52) return 15;
	if(destroyedAsteroids <= 72) return 20;
	if(destroyedAsteroids <= 82) return 25;
	if(destroyedAsteroids <= 87) return 30;
	if(destroyedAsteroids <= 95) return 35;
	if(destroyedAsteroids <= 104) return 40;
	if(destroyedAsteroids <= 112) return 45;
	if(destroyedAsteroids <= 120) return 50;
	if(destroyedAsteroids <= 128) return 55;
	if(destroyedAsteroids <= 137) return 60;
	if(destroyedAsteroids <= 148) return 65;
	if(destroyedAsteroids <= 161) return 70;
	if(destroyedAsteroids <= 188) return 75;
	return 80;
}


float timeBetweenSpawns() {
	return (float) (scalingMagnitude * exp(-destroyedAsteroids * scalingSpeed) + stepSize * numSteps);
}

float setSpeedDifficulty(float speed, bool isPositive) {
	if(getScore() <= 100) return speed;
	int score = getScore() - 100;
	if(score > 2100) score = 2100;
  
	float deltaSpeed = score * 2*0f;
	deltaSpeed /= 2000;
	deltaSpeed += 1;

	if(isPositive) {
		return speed / deltaSpeed;
	} else
		return speed * deltaSpeed;
}
