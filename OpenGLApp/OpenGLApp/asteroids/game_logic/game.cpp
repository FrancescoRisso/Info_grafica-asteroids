#include "game.hpp"

using namespace Asteroids;

Spaceship spaceship;
std::list<Projectile> projectiles;
std::list<Asteroid> asteroids;
DisplayString scoreDisplay;

int destroyedAsteroids = 0;

float timeFromLastSpawn = 0;
float timeFromLastShot = 0;

bool firstMouse = true;
float lastX, lastY;

Heart hearts[numHearts];
int heartsLeft = numHearts;

float invulnerabilityCount = 0;
float blinkCount = 0;
bool isInvulnerable = false;
bool blinkIsOn = false;

bool powerupPresent;
Powerup powerup;

extern gamePhases currentPhase;


/*
	checkAsteroidProjectileCollision
	---------------------------------------------------------------------
	Checks if a given projectile collides with any asteroids.
	If so, the function kills the asteroid, while the callee is in charge
	of killing the projectile
	---------------------------------------------------------------------
	PARAMETERS:
		- proj: an iterator to find a given projectile
	---------------------------------------------------------------------
	OUTPUT:
		- whether a collision occurred (then, the projectile should be
			killed)
*/
bool checkAsteroidProjectileCollision(std::list<Asteroids::Projectile>::iterator proj);


void prepareGame() {
	spaceship.Init(glm::vec2(0));

	for(int i = 0; i < numHearts; i++) hearts[i].Init(glm::vec2(0.95 - radius_Heart, 0.9 - radius_Heart), i);

	scoreDisplay.Init(glm::vec2(-0.95, 0.9), "Score: 0", alignLeft, alignTop, glm::vec3(1), 0.1);

	asteroids.clear();
	projectiles.clear();

	heartsLeft = numHearts;
	destroyedAsteroids = 0;

	timeFromLastShot = 0.0000000001;
	timeFromLastSpawn = 0;

	isInvulnerable = false;
}


bool checkAsteroidProjectileCollision(std::list<Asteroids::Projectile>::iterator proj) {
	auto asteroidPtr = asteroids.begin();

	while(asteroidPtr != asteroids.end()) {
		if(asteroidPtr->collidesWith(&(*proj))) {
			while(asteroidPtr->hasChildren()) asteroids.push_back(asteroidPtr->getChild());
			asteroidPtr = asteroids.erase(asteroidPtr);
			destroyedAsteroids++;
			char buf[20];
			sprintf_s(buf, "Score: %d", destroyedAsteroids);
			scoreDisplay.changeString((const char*) buf);
			return true;
		}
		asteroidPtr++;
	}

	return false;
}


void renderGame() {
	timeFromLastSpawn += deltaTime;

	auto projectilePtr = projectiles.begin();
	auto asteroidPtr = asteroids.begin();
	scoreDisplay.Draw();

	while(projectilePtr != projectiles.end()) {
		if(checkAsteroidProjectileCollision(projectilePtr)) {
			projectilePtr = projectiles.erase(projectilePtr);
			continue;
		}

		if(projectilePtr->isOutOfScreen()) {
			projectilePtr = projectiles.erase(projectilePtr);
			continue;
		}

		projectilePtr->Draw();
		projectilePtr->Move();

		projectilePtr++;
	}

	if(Asteroid::ShouldSpawn()) {
		Asteroid tmpAsteroid;
		tmpAsteroid.Spawn();
		asteroids.push_back(tmpAsteroid);
	}

	if(powerupPresent) {
		powerup.Move();
		powerup.Draw();
		if(powerup.isOutOfScreen()) powerupPresent = false;
		if(powerup.collidesWith(&spaceship)) {
			powerupPresent = false;
			switch(powerup.getType()) {
				case extraLife: heartsLeft = min(heartsLeft + 1, numHearts); break;
			}
		}
	} else {
		if(Powerup::shouldSpawn()) {
			powerupPresent = true;
			powerup.Spawn();
		}
	}

	asteroidPtr = asteroids.begin();
	while(asteroidPtr != asteroids.end()) {
		asteroidPtr->Draw();
		asteroidPtr->Move();
		if(asteroidPtr->isOutOfScreen()) {
			asteroidPtr = asteroids.erase(asteroidPtr);
			continue;
		}

		if(!isInvulnerable && asteroidPtr->collidesWith(&spaceship)) {
			if(--heartsLeft <= 0) {
				currentPhase = endScreen;
				setScoresEndScreen(destroyedAsteroids);
			} else {
				invulnerabilityCount = 0;
				blinkCount = 0;
				isInvulnerable = true;
				blinkIsOn = true;
				spaceship.Init(glm::vec2(0));
			}

			break;
		} else
			asteroidPtr++;
	}

	if(isInvulnerable) {
		invulnerabilityCount += deltaTime;
		blinkCount += deltaTime;

		if(invulnerabilityCount > invulnerabilityTime) isInvulnerable = false;
		if(blinkCount > (blinkIsOn ? blinkOn_time : blinkOff_time)) {
			blinkIsOn = !blinkIsOn;
			blinkCount = 0;
		}
	}

	if(!isInvulnerable || blinkIsOn) spaceship.Draw();

	for(int i = 0; i < heartsLeft; i++) hearts[i].Draw();
}


void updateTransformGame() {
	spaceship.updateTransform();
	scoreDisplay.updateTransform();
	powerup.updateTransform();
	for(int i = 0; i < numHearts; i++) hearts[i].updateTransform();
}


void processKeyboardGame(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) spaceship.MoveDir(up);
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) spaceship.MoveDir(down);
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) spaceship.MoveDir(left);
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) spaceship.MoveDir(right);
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if(timeFromLastShot > 1.0 / speed_autoShoot) timeFromLastShot = 0;
		if(timeFromLastShot == 0) projectiles.push_back(spaceship.Shoot());
		timeFromLastShot += deltaTime;
	}
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) timeFromLastShot = 0;
}


void processMouseGame(GLFWwindow* window, double xposIn, double yposIn) {
	float xpos = (float) xposIn;
	float ypos = (float) yposIn;

	if(firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;  // reversed since y-coordinates go from bottom to top

	spaceship.PointTo(mouse2graphicCoords(glm::vec2(xpos, ypos), glm::vec2(SCR_WIDTH, SCR_HEIGHT)));

	lastX = xpos;
	lastY = ypos;
}
