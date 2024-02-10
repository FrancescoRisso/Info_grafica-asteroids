#include "instructions.hpp"


using namespace Asteroids;


enum instructionsStrings { title, youSpaceship, avoidAsteroids, youCan, aim, shoot, move, lives, returnMain, instr_NUM_STRINGS };

DisplayString instrStrings[instr_NUM_STRINGS];

extern gamePhases currentPhase;


void prepareInstructions() {
	instrStrings[title].Init(glm::vec2(0, 0.65), "INSTRUCTIONS", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.25);
	instrStrings[youSpaceship].Init(
		glm::vec2(-0.90, 0.3), "You are a spaceship in the not-so-void space.", alignLeft, alignCenterVert, glm::vec3(1), 0.10);
	instrStrings[avoidAsteroids].Init(
		glm::vec2(-0.90, 0.15), "You have not to die from the asteroids.", alignLeft, alignCenterVert, glm::vec3(1), 0.10);
	instrStrings[youCan].Init(glm::vec2(-0.90, 0), "You can:", alignLeft, alignCenterVert, glm::vec3(1), 0.10);
	instrStrings[aim].Init(glm::vec2(-0.90, -0.15), " - aim with your MOUSE", alignLeft, alignCenterVert, glm::vec3(1), 0.10);
	instrStrings[shoot].Init(glm::vec2(-0.90, -0.3), " - shoot with SPACE", alignLeft, alignCenterVert, glm::vec3(1), 0.10);
	instrStrings[move].Init(glm::vec2(-0.90, -0.45), " - move with WASD", alignLeft, alignCenterVert, glm::vec3(1), 0.10);
	instrStrings[lives].Init(glm::vec2(-0.90, -0.6), "Once you finish your 3 lives, the game ends.", alignLeft, alignCenterVert, glm::vec3(1), 0.10);
	instrStrings[returnMain].Init(glm::vec2(0.90, -0.8), "Press M to return to main menu.", alignRight, alignCenterVert, glm::vec3(1), 0.06);
}


void renderInstructions() {
	for(int i = 0; i < instr_NUM_STRINGS; i++) instrStrings[i].Draw();
}


void updateTransformInstructions() {
	for(int i = 0; i < instr_NUM_STRINGS; i++) instrStrings[i].updateTransform();
}


void processKeyboardInstructions(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) currentPhase = mainMenu;
}


void processMouseInstructions(GLFWwindow* window, double xposIn, double yposIn) {}
