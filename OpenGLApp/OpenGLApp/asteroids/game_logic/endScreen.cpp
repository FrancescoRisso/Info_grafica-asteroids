#include "endScreen.hpp"


using namespace Asteroids;


DisplayString endGameStrings[endScreen_NUM_STRINGS];

int highScore = -1;
bool isNewBest = false;

extern gamePhases currentPhase;


void prepareEndScreen() {
	endGameStrings[gmOver].Init(glm::vec2(0, 0.65), "GAME OVER", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.25f);
	endGameStrings[yourScore].Init(glm::vec2(0, 0.3), "", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.10f);
	endGameStrings[hiScore].Init(glm::vec2(0, 0.15), "", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.10f);
	endGameStrings[newBest].Init(glm::vec2(0, 0.05), "New high score!", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.06f);
	endGameStrings[restart].Init(glm::vec2(0, -0.25), "Press R to restart", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.10f);
	endGameStrings[goHome1].Init(glm::vec2(0, -0.53), "Press M to return", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.10f);
	endGameStrings[goHome2].Init(glm::vec2(0, -0.66), "to the main menu", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.10f);
}


void renderEndScreen() {
	for(int i = 0; i < endScreen_NUM_STRINGS; i++)
		if(i != newBest || isNewBest) endGameStrings[i].Draw();
}


void updateTransformEndScreen() {
	for(int i = 0; i < endScreen_NUM_STRINGS; i++) endGameStrings[i].updateTransform();
}


void processKeyboardEndScreen(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		stopMusic();
		prepareGame();
		currentPhase = game;
	}
	if(glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		prepareHomePage();
		currentPhase = mainMenu;
	}
}


void processMouseEndScreen(GLFWwindow* window, double xposIn, double yposIn) {}


void setScoresEndScreen(int score) {
	char buf[100];

	sprintf_s(buf, "You destroyed %d asteroids", score);
	endGameStrings[yourScore].changeString(buf);
	loadRecord();
	sprintf_s(buf, "Best score: %d", highScore);
	if(highScore < score) {
		highScore = score;
		isNewBest = true;
		sprintf_s(buf, "Best score: %d", highScore);
		saveRecord();
	} else
		isNewBest = false;
	endGameStrings[hiScore].changeString(buf);
}

int getHighScore() {
	return highScore;
};

void resetHighScore() {
	highScore = -1;
}

void setHighScore(int a) {
	highScore = a;
}
