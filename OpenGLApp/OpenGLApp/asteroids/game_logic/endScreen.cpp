#include "endScreen.hpp"


using namespace Asteroids;


DisplayString endGameStrings[endScreen_NUM_STRINGS];

int highScore = -1;
bool isNewBest = false;

extern gamePhases currentPhase;


void prepareEndScreen() {
	endGameStrings[gmOver].Init(glm::vec2(0, 0.65), "GAME OVER", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.25);
	endGameStrings[yourScore].Init(glm::vec2(0, 0.3), "", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.10);
	endGameStrings[hiScore].Init(glm::vec2(0, 0.15), "", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.10);
	endGameStrings[newBest].Init(glm::vec2(0, 0.05), "New high score!", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.06);
	endGameStrings[restart].Init(glm::vec2(0, -0.25), "Press SPACE to restart", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.10);
	endGameStrings[goHome1].Init(glm::vec2(0, -0.53), "Press M to return", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.10);
	endGameStrings[goHome2].Init(glm::vec2(0, -0.66), "to the main menu", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.10);
}


void renderEndScreen() {
	for(int i = 0; i < endScreen_NUM_STRINGS; i++)
		if(i != newBest || isNewBest) endGameStrings[i].Draw();
}


void updateTransformEndScreen() {
	for(int i = 0; i < endScreen_NUM_STRINGS; i++) endGameStrings[i].updateTransform();
}


void processKeyboardEndScreen(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		prepareGame();
		currentPhase = game;
	}
	if(glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) currentPhase = mainMenu;
}


void processMouseEndScreen(GLFWwindow* window, double xposIn, double yposIn) {}


void setScoresEndScreen(int score) {
	char buf[100];

	sprintf_s(buf, "You destroyed %d asteroids", score);
	endGameStrings[yourScore].changeString(buf);

	if(highScore < score) {
		highScore = score;
		isNewBest = true;
		sprintf_s(buf, "Best score: %d", highScore);
		endGameStrings[hiScore].changeString(buf);
	} else
		isNewBest = false;
}
