#include "homePage.hpp"

#include "logo.hpp"


using namespace Asteroids;


enum homePageKeys { keyDown, keyUp, space, keys_NUM };
bool pressed[keys_NUM] = {false};


enum homepageStrings { spacevoid, explore, instruct, highscore, quit, home_NUM_STRINGS };

DisplayString homeStrings[home_NUM_STRINGS];

extern gamePhases currentPhase;

static int state = 0;

void prepareHomePage() {
	char buf[100];
	int highScore = getHighScore();
	if(highScore == -1) highScore++;
	sprintf_s(buf, "Best score: %d", highScore);

	homeStrings[spacevoid].Init(glm::vec2(0, 0.65), " SPACEVOID", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.25);
	homeStrings[explore].Init(glm::vec2(0, 0.15), "Start Exploring", alignCenterHoriz, alignCenterVert, glm::vec3(state == 0 ? 1 : 0.5), 0.10);
	homeStrings[instruct].Init(glm::vec2(0, 0.0), "Instructions", alignCenterHoriz, alignCenterVert, glm::vec3(state == 1 ? 1 : 0.5), 0.10);
	homeStrings[highscore].Init(glm::vec2(0, -0.15), buf, alignCenterHoriz, alignCenterVert, glm::vec3(state == 2 ? 1 : 0.5), 0.10);
	homeStrings[quit].Init(glm::vec2(0, -0.30), "Quit", alignCenterHoriz, alignCenterVert, glm::vec3(state == 3 ? 1 : 0.5), 0.10);
}

void logoPrint() {
	Spacevoid spacevoid;
	spacevoid.Init(glm::vec2(0, 0.65));
	spacevoid.Draw();
}


void renderHomePage() {
	for(int i = 0; i < home_NUM_STRINGS; i++) homeStrings[i].Draw();
	// logoPrint();
}


void updateTransformHomePage() {
	for(int i = 0; i < home_NUM_STRINGS; i++) homeStrings[i].updateTransform();
}


void updateColors() {
	for(int i = 1; i < home_NUM_STRINGS; i++) homeStrings[i].setColor(glm::vec3(state == i - 1 ? 1 : 0.5));
}


void processKeyboardHomePage(GLFWwindow* window) {
	if(!pressed[keyDown] && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		state = (state + 1) % 4;
		updateColors();
		pressed[keyDown] = true;
	}

	if(!pressed[keyUp] && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		state = (state - 1) % 4;
		updateColors();
		pressed[keyUp] = true;
	}

	if(!pressed[space] && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		switch(state) {
			case 0:
				prepareGame();
				currentPhase = game;
				break;
			case 1:
				prepareInstructions();
				currentPhase = instructions;
				break;
			case 2:
				resetHighScore();
				homeStrings[highscore].changeString("Best score: 0");
				break;
			case 3: glfwSetWindowShouldClose(window, true); break;
		}
	}

	if(pressed[keyDown] && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE) pressed[keyDown] = false;
	if(pressed[keyUp] && glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE) pressed[keyUp] = false;
	if(pressed[space] && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) pressed[space] = false;
}


void processMouseHomePage(GLFWwindow* window, double xposIn, double yposIn) {}
