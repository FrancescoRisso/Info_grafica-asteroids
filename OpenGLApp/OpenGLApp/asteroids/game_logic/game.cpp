#include "game.hpp"

using namespace Asteroids;

Spaceship spaceship;
std::list<Projectile> projectiles;
std::list<Asteroid> asteroids;
DisplayString scoreDisplay;

int destroyedAsteroids = 0;

float timeFromLastSpawn = 0;
float timeFromLastShot = 0;

Heart hearts[numHearts];
int heartsLeft = numHearts;

float invulnerabilityCount = 0;
float blinkCount = 0;
bool isInvulnerable = false;
bool blinkIsOn = false;

bool powerupPresent;
Powerup powerup;

extern gamePhases currentPhase;

float explosionTimer;
explosionLevel_t explosionLevel;

bool paused = false;
bool PkeyPressed = false;

glm::vec2 spaceshipPointTo;

//pause new

enum pauseMenuKeys { keyDown, keyUp, enter, keys_NUM };
bool static pressed[keys_NUM] = {false};

enum pauseStrings { resume, restartP, menu, quitP, pause_NUM_STRINGS, pause };

DisplayString pauseStrings[pause_NUM_STRINGS];

enum pauseMenuOptions { resumeGame, restartGame, backToMenu, quitOption };

static pauseMenuOptions selectedOption = resumeGame;


/*gestione alternativa pausa*/


void renderPause() {
	if(!paused) return;
	for(int i = 0; i < pause_NUM_STRINGS; i++) pauseStrings[i].Draw();
	pauseStrings[pause].Draw();
}

void pauseScreen() {
	if(!paused) return;
	renderPause();
}

void updateColorsP() {
	if(!paused) return;
	for(int i = 0; i < pause_NUM_STRINGS; i++) {
		if(i == selectedOption)
			pauseStrings[i].setColor(glm::vec3(1));
		else
			pauseStrings[i].setColor(glm::vec3(0.5));
	}
}

void processKeyboardPause(GLFWwindow* window) {
	if(!paused) return;
	if(!pressed[keyDown] && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		selectedOption = (pauseMenuOptions) ((selectedOption + 1) % 4);
		updateColorsP();
		pressed[keyDown] = true;
	}

	if(!pressed[keyUp] && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		selectedOption = (pauseMenuOptions) ((selectedOption - 1 + 4) % 4);
		updateColorsP();
		pressed[keyUp] = true;
	}

	if(!pressed[enter] && glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
		switch(selectedOption) {
			case resumeGame:
				paused = !paused;
				spaceship.PointTo(spaceshipPointTo);
				break;
			case restartGame:
				paused = !paused;
				prepareGame();
				currentPhase = game;
				break;
			case backToMenu:
				paused = !paused;
				prepareHomePage();
				enterSet();
				currentPhase = mainMenu;
				break;
			case quitOption:
				saveRecord();
				glfwSetWindowShouldClose(window, true);
				break;
		}
	}

	if(pressed[keyDown] && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE) pressed[keyDown] = false;
	if(pressed[keyUp] && glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE) pressed[keyUp] = false;
	if(pressed[enter] && glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_RELEASE) pressed[enter] = false;
}


/*fine gestione alternativa pausa*/


//end pause new

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

bool gameBubble = false;
bool flashIncrease = false;
bool flashDecrease = false;
float iFlash = 0;

float getiFlash(){
	return iFlash;
}

void preparePause(){
	selectedOption = resumeGame;
	// pause new
	pauseStrings[pause].Init(glm::vec2(0, 0.35), "PAUSE", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.15);
	pauseStrings[resume].Init(
		glm::vec2(0, 0.15), "Resume game", alignCenterHoriz, alignCenterVert, glm::vec3(selectedOption == resumeGame ? 1 : 0.5), 0.10);
	pauseStrings[restartP].Init(
		glm::vec2(0, 0.0), "Restart game", alignCenterHoriz, alignCenterVert, glm::vec3(selectedOption == restartGame ? 1 : 0.5), 0.10);
	pauseStrings[menu].Init(
		glm::vec2(0, -0.15), "Back to menu", alignCenterHoriz, alignCenterVert, glm::vec3(selectedOption == backToMenu ? 1 : 0.5), 0.10);
	pauseStrings[quitP].Init(glm::vec2(0, -0.30), "Quit", alignCenterHoriz, alignCenterVert, glm::vec3(selectedOption == quitOption ? 1 : 0.5), 0.10);
	// end pause new
}

void prepareGame() {
	spaceship.Init(glm::vec2(0));
	

	for(int i = 0; i < numHearts; i++) hearts[i].Init(glm::vec2(0.95 - radius_Heart, 0.9 - radius_Heart), i);

	scoreDisplay.Init(glm::vec2(-0.95, 0.9), "Score: 0", alignLeft, alignTop, glm::vec3(1), 0.1);

	asteroids.clear();
	projectiles.clear();
	powerupPresent = false;
	heartsLeft = numHearts;
	destroyedAsteroids = 0;

	timeFromLastShot = 0.0000000001;
	timeFromLastSpawn = 0;

	isInvulnerable = false;

	explosionTimer = 0;
	explosionLevel = explosion_none;

	flashIncrease = false;
	flashDecrease = false;
	iFlash = 0.0;


}


void incrementScoreBy(int n) {
	destroyedAsteroids += n;
	char buf[20];
	sprintf_s(buf, "Score: %d", destroyedAsteroids);
	scoreDisplay.changeString((const char*) buf);
}

bool checkAsteroidProjectileCollision(std::list<Asteroids::Projectile>::iterator proj) {
	auto asteroidPtr = asteroids.begin();

	while(asteroidPtr != asteroids.end()) {
		if(asteroidPtr->collidesWith(&(*proj))) {
			while(asteroidPtr->hasChildren()) asteroids.push_back(asteroidPtr->getChild());
			if(asteroidPtr->goldenFlag) {
				incrementScoreBy(goldenPoints);
				
			} else {
				incrementScoreBy(1);
			
			}
			asteroidPtr = asteroids.erase(asteroidPtr);
			return true;
		}
		asteroidPtr++;
	}

	return false;
}



void renderGame() {
	if(!paused) timeFromLastSpawn += deltaTime;
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
		if(!paused) projectilePtr->Move();

		projectilePtr++;
	}

	if(Asteroid::ShouldSpawn()) {
		Asteroid tmpAsteroid;
		tmpAsteroid.Spawn();
		asteroids.push_back(tmpAsteroid);
	}

	if(powerupPresent) {
		if(!paused) powerup.Move();
		powerup.Draw();
		if(powerup.isOutOfScreen()) powerupPresent = false;
		if(powerup.collidesWith(&spaceship)) {
			powerupPresent = false;
			switch(powerup.getType()) {
				case extraLife: heartsLeft = min(heartsLeft + 1, numHearts); break;
				case destroyAsteroids: flashIncrease = true;
					break;
				case shieldBubble:
					isInvulnerable = true;
					invulnerabilityCount = -shieldTime+2;
					if(!gameBubble) {
						spaceship.changeBubble();
						gameBubble = !gameBubble;
						spaceship.setExplosionLevel(bubbled);
					}
					break;
			}
		}
	} else {
		if(Powerup::shouldSpawn()) {
			powerupPresent = true;
			powerup.Spawn();
		}
	}

	if(explosionLevel != explosion_none) {
		if(!paused) explosionTimer += deltaTime;
		if(explosionTimer > explosionTimePerLevel) {
			explosionTimer = 0;
			explosionLevel = (explosionLevel_t)(explosionLevel + 1);
			spaceship.setExplosionLevel(explosionLevel);
			if(explosionLevel == explosion_NUM) {
				if(heartsLeft <= 0) {
					currentPhase = endScreen;
					setScoresEndScreen(destroyedAsteroids);
				} else {
					invulnerabilityCount = 0;
					blinkCount = 0;

					isInvulnerable = true;
					blinkIsOn = true;

					spaceship.Init(glm::vec2(0));
				}

				explosionLevel = explosion_none;
				explosionTimer = 0;
			}
		}
	}

	asteroidPtr = asteroids.begin();
	while(asteroidPtr != asteroids.end()) {
		asteroidPtr->Draw();
		if(!paused) asteroidPtr->Move();
		if(asteroidPtr->isOutOfScreen()) {
			asteroidPtr = asteroids.erase(asteroidPtr);
			continue;
		}

		if(explosionLevel == explosion_none && !isInvulnerable && !flashIncrease && asteroidPtr->collidesWith(&spaceship)) {
			explosionLevel = (explosionLevel_t)(explosionLevel + 1);
			explosionTimer = 0;
			--heartsLeft;
			asteroidPtr = asteroids.erase(asteroidPtr);
			spaceship.setExplosionLevel(explosionLevel);
			break;
		} else
			asteroidPtr++;
	}

	if(isInvulnerable && !paused) {
		invulnerabilityCount += deltaTime;
		blinkCount += deltaTime;
		/* if(invulnerabilityCount >= 0 && invulnerabilityCount < invulnerabilityTime) {
			blinkCount = 0;
			blinkIsOn = true;
			//gameBubble = blinkIsOn;
		}*/
		if(invulnerabilityCount > invulnerabilityTime) {
			isInvulnerable = false;
			if(gameBubble == true) {
				spaceship.changeBubble();
				spaceship.setExplosionLevel(explosion_none);
				gameBubble = false;
			}
		}
		if(blinkCount > (blinkIsOn ? blinkOn_time : blinkOff_time)) {
			blinkIsOn = !blinkIsOn;
			blinkCount = 0;
		}
	}

		if(flashIncrease) {
		iFlash += flashSpeed;
		if(iFlash >= flashBrightness) {
			iFlash = flashBrightness;
			flashIncrease = false;
			flashDecrease = true;
			incrementScoreBy(asteroids.size());
			asteroids.clear();
		}
	}

	if(flashDecrease && !flashIncrease) {
		iFlash -= flashSpeed;
		if(iFlash <= 0.0) {
			flashDecrease = false;
			iFlash = 0.0;
		}
	}

	bool powerupFlag = false;
	if(!isInvulnerable || blinkIsOn)
		spaceship.Draw();
	else if(gameBubble)
		powerupFlag = true;
	if(isInvulnerable && invulnerabilityCount < 0 && gameBubble)
		spaceship.Draw();
	else if(powerupFlag) {
		spaceship.setExplosionLevel(explosion_none);
		spaceship.Draw();
		spaceship.setExplosionLevel(bubbled);
	}


	

	updateColorsP();
	pauseScreen();

	for(int i = 0; i < heartsLeft; i++) hearts[i].Draw();
}


void updateTransformGame() {
	spaceship.updateTransform();
	scoreDisplay.updateTransform();

		for(int i = 0; i < pause_NUM_STRINGS; i++) pauseStrings[i].updateTransform();
	pauseStrings[pause].updateTransform();

	powerup.updateTransform();
	for(int i = 0; i < numHearts; i++) hearts[i].updateTransform();
}




void processKeyboardGame(GLFWwindow* window) {
	if(!paused) {
		if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) spaceship.MoveDir(up);
		if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) spaceship.MoveDir(down);
		if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) spaceship.MoveDir(left);
		if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) spaceship.MoveDir(right);
		if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			if(timeFromLastShot > 1.0 / speed_autoShoot) timeFromLastShot = 0;
			if(timeFromLastShot == 0) projectiles.push_back(spaceship.Shoot());
			timeFromLastShot += deltaTime;
		}
	} else
		processKeyboardPause(window);
	if(!PkeyPressed && glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		PkeyPressed = true;
		//selectedOption = resumeGame; 
		if(!paused) {
			paused = !paused;
			spaceship.PointTo(spaceshipPointTo);
		}
		 pauseScreen();
	}

	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) timeFromLastShot = 0;
	if(PkeyPressed && glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE) PkeyPressed = false;
}


void processMouseGame(GLFWwindow* window, double xposIn, double yposIn) {
	float xpos = (float) xposIn;
	float ypos = (float) yposIn;

	spaceshipPointTo = mouse2graphicCoords(glm::vec2(xpos, ypos), glm::vec2(SCR_WIDTH, SCR_HEIGHT));
	if(!paused) spaceship.PointTo(spaceshipPointTo);
}
