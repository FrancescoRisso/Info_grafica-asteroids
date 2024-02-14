#include "homePage.hpp"


using namespace Asteroids;


enum homePageKeys { keyDown, keyUp, enter, keys_NUM };
bool pressed[keys_NUM] = {false};


enum homepageStrings { spaceVoidString, explore, instruct, resetHighScoreStr, curHighScoreStr, quit, home_NUM_STRINGS };

DisplayString homeStrings[home_NUM_STRINGS];

extern gamePhases currentPhase;

enum homeMenuOptions { startGame, showInstructions, resetScore, quitOption };

static homeMenuOptions selectedOption = startGame;

Spacevoid spacevoid;

static int state = 0;

void saveRecord() {
	FILE* file;
	int var = getHighScore();

	fopen_s(&file, "./resources/.record", "w");
	if(file == NULL) { return; }

	fprintf_s(file, "%d", var);
	fclose(file);
}

void loadRecord() {
	FILE* file;
	int var;

	fopen_s(&file, "./resources/.record", "r");
	if(file == NULL) { return; }

	fscanf_s(file, "%d", &var);
	fclose(file);

	setHighScore(var);
}

void prepareHomePage() {
	char buf[100];
	int highScore = getHighScore();
	if(highScore == -1) highScore++;
	sprintf_s(buf, "Reset high score (currently %d)", highScore);

	// homeStrings[spaceVoidString].Init(glm::vec2(0, 0.65), " SPACEVOID", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.25);
	homeStrings[explore].Init(
		glm::vec2(0, 0.15), "Start game", alignCenterHoriz, alignCenterVert, glm::vec3(selectedOption == startGame ? 1 : 0.5), 0.10);
	homeStrings[instruct].Init(
		glm::vec2(0, 0.0), "Instructions", alignCenterHoriz, alignCenterVert, glm::vec3(selectedOption == showInstructions ? 1 : 0.5), 0.10);
	homeStrings[resetHighScoreStr].Init(glm::vec2(0, -0.15), "Reset high score", alignCenterHoriz, alignCenterVert, glm::vec3(0.5), 0.10);
	homeStrings[curHighScoreStr].Init(glm::vec2(0, -0.15), buf, alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.10);
	homeStrings[quit].Init(glm::vec2(0, -0.30), "Quit", alignCenterHoriz, alignCenterVert, glm::vec3(selectedOption == quitOption ? 1 : 0.5), 0.10);

	spacevoid.Init(glm::vec2(0, 0.65));
}


void renderHomePage() {
	for(int i = 1; i < home_NUM_STRINGS; i++)
		if((selectedOption == resetScore && i != resetHighScoreStr) || (selectedOption != resetScore && i != curHighScoreStr)) homeStrings[i].Draw();
	spacevoid.Move();
	spacevoid.Draw();
}


void updateTransformHomePage() {
	for(int i = 0; i < home_NUM_STRINGS; i++) homeStrings[i].updateTransform();
	spacevoid.updateTransform();
}


void updateColors() {
	for(int i = 1; i < home_NUM_STRINGS; i++)
		if(i != 3 && i != 4) homeStrings[i].setColor(glm::vec3(selectedOption == i - (i < 4 ? 1 : 2) ? 1 : 0.5));
}

void enterSet() {
	pressed[enter] = true;
}

void processKeyboardHomePage(GLFWwindow* window) {
	if(!pressed[keyDown] && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		selectedOption = (homeMenuOptions)((selectedOption + 1) % 4);
		updateColors();
		pressed[keyDown] = true;
	}

	if(!pressed[keyUp] && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		selectedOption = (homeMenuOptions)((selectedOption - 1 + 4) % 4);
		updateColors();
		pressed[keyUp] = true;
	}

	if(!pressed[enter] && glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
		switch(selectedOption) {
			case startGame:
				prepareGame();
				currentPhase = game;
				break;
			case showInstructions:
				prepareInstructions();
				currentPhase = instructions;
				break;
			case resetScore:
				resetHighScore();
				homeStrings[curHighScoreStr].changeString("Reset high score (currently 0)");
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


void processMouseHomePage(GLFWwindow* window, double xposIn, double yposIn) {}
