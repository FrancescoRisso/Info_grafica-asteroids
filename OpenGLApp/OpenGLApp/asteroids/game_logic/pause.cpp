#include "pause.hpp"


using namespace Asteroids;


enum pauseMenuKeys { keyDown, keyUp, enter, keys_NUM };
bool static pressed[keys_NUM] = {false};

enum pauseStrings { resume, restartP, menu, quitP, pause, pause_NUM_STRINGS };

DisplayString pauseStrings[pause_NUM_STRINGS];

enum pauseMenuOptions { resumeGame, restartGame, backToMenu, quitOption };

static pauseMenuOptions selectedOption = resumeGame;

extern gamePhases currentPhase;
extern Spaceship spaceship;
extern std::list<Asteroid> asteroids;
extern std::list<Projectile> projectiles;
extern Heart hearts[];
extern int heartsLeft;
extern glm::vec2 spaceshipPointTo;
extern DisplayString scoreDisplay;

void renderPause() {
	for(int i = 0; i < pause_NUM_STRINGS; i++) pauseStrings[i].Draw();

	spaceship.Draw();
	for(auto asteroidPtr = asteroids.begin(); asteroidPtr != asteroids.end(); asteroidPtr++) asteroidPtr->Draw();
	for(auto projectilePtr = projectiles.begin(); projectilePtr != projectiles.end(); projectilePtr++) projectilePtr->Draw();
	for(int i = 0; i < heartsLeft; i++) hearts[i].Draw();
	scoreDisplay.Draw();
}


void updateColorsP() {
	for(int i = 0; i < pause_NUM_STRINGS; i++) {
		if(i == selectedOption || i == pause)
			pauseStrings[i].setColor(glm::vec3(1));
		else
			pauseStrings[i].setColor(glm::vec3(0.5));
	}
}

void processKeyboardPause(GLFWwindow* window) {
	if(!pressed[keyDown] && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		selectedOption = (pauseMenuOptions)((selectedOption + 1) % 4);
		updateColorsP();
		pressed[keyDown] = true;
	}

	if(!pressed[keyUp] && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		selectedOption = (pauseMenuOptions)((selectedOption - 1 + 4) % 4);
		updateColorsP();
		pressed[keyUp] = true;
	}

	if(!pressed[enter] && glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
		switch(selectedOption) {
			case resumeGame:
				currentPhase = game;
				spaceship.PointTo(spaceshipPointTo);
				break;
			case restartGame:
				prepareGame();
				currentPhase = game;
				break;
			case backToMenu:
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


void preparePause() {
	selectedOption = resumeGame;

	pauseStrings[pause].Init(glm::vec2(0, 0.35), "PAUSE", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.15);
	pauseStrings[resume].Init(
		glm::vec2(0, 0.15), "Resume game", alignCenterHoriz, alignCenterVert, glm::vec3(selectedOption == resumeGame ? 1 : 0.5), 0.10);
	pauseStrings[restartP].Init(
		glm::vec2(0, 0.0), "Restart game", alignCenterHoriz, alignCenterVert, glm::vec3(selectedOption == restartGame ? 1 : 0.5), 0.10);
	pauseStrings[menu].Init(
		glm::vec2(0, -0.15), "Back to menu", alignCenterHoriz, alignCenterVert, glm::vec3(selectedOption == backToMenu ? 1 : 0.5), 0.10);
	pauseStrings[quitP].Init(glm::vec2(0, -0.30), "Quit", alignCenterHoriz, alignCenterVert, glm::vec3(selectedOption == quitOption ? 1 : 0.5), 0.10);
}


void updateTransformPause() {
	for(int i = 0; i < pause_NUM_STRINGS; i++) pauseStrings[i].updateTransform();
	spaceship.updateTransform();
	for(auto asteroidPtr = asteroids.begin(); asteroidPtr != asteroids.end(); asteroidPtr++) asteroidPtr->updateTransform();
	for(auto projectilePtr = projectiles.begin(); projectilePtr != projectiles.end(); projectilePtr++) projectilePtr->updateTransform();
	for(int i = 0; i < numHearts; i++) hearts[i].updateTransform();
	scoreDisplay.updateTransform();
}

void processMousePause(GLFWwindow* window, double xposIn, double yposIn) {
	processMouseGame(window, xposIn, yposIn);
}
