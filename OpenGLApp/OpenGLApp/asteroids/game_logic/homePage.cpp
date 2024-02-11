#include "homePage.hpp"
#include "logo.hpp"

#include <chrono> // Include per la gestione del tempo

// Funzione per mettere in pausa il programma per 1 secondo
void pausasec() {
	// Ottieni l'istante di tempo corrente
	auto oraCorrente = std::chrono::high_resolution_clock::now();

	// Calcola l'istante di tempo futura (mezzo secondo dopo l'istante corrente)
	auto istanteFutura = oraCorrente + std::chrono::milliseconds(300);

	// Attendi finch� l'istante di tempo futura non viene raggiunto
	while(std::chrono::high_resolution_clock::now() < istanteFutura) {
		// Attendi...
	}
}


using namespace Asteroids;


enum homepageStrings { spacevoid, explore, instruct, highscore, quit, home_NUM_STRINGS };

DisplayString homeStrings[home_NUM_STRINGS];

extern gamePhases currentPhase;

static int state = 0;
int hs = 0;
void prepareHS() {
	homeStrings[highscore].Init(glm::vec2(0, -0.15), "Current highscore: "+ hs, alignCenterHoriz, alignCenterVert, glm::vec3(0.5), 0.10);

}

void renderHS(){
	homeStrings[highscore].Draw();
}

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
	for(int i = 0; i < home_NUM_STRINGS; i++) { homeStrings[i].Draw(); }
	//logoPrint();
}


void updateTransformHomePage() {
	for(int i = 0; i < home_NUM_STRINGS; i++) homeStrings[i].updateTransform();
}


void processKeyboardHomePage(GLFWwindow* window) {
	switch(state) {
		case 0:
		if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {

			state = 1;
			prepareHomePage();
			//while(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { pausasec();}
			renderHomePage();
			pausasec();
		}
		if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

			state = 1;
			prepareHomePage();
			//while(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { pausasec(); }
			renderHomePage();
			pausasec();
		}
		if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {

			state = 3;
			prepareHomePage();
			//while(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { pausasec(); }
			renderHomePage();
			pausasec();
		}
		if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

			state = 3;
			prepareHomePage();
			//while(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { pausasec(); }
			renderHomePage();
			pausasec();
		}
		if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			prepareGame();
			currentPhase = game;
		}
		break;
		case 1:
		if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {

			state = 2;
			prepareHomePage();
			//while(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { pausasec(); }
			renderHomePage();
			pausasec();
		}
		if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

			state = 2;
			prepareHomePage();
			//while(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { pausasec(); }
			renderHomePage();
			pausasec();
		}
		if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {

			state = 0;
			prepareHomePage();
			//while(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { pausasec(); }
			renderHomePage();
			pausasec();
		}
		if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

			state = 0;
			prepareHomePage();
			//while(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { pausasec(); }
			renderHomePage();
			pausasec();
		}
		if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			prepareInstructions();
			currentPhase = instructions; }
		break;
		case 2:
		if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {

			state = 3;
			prepareHomePage();
			/*while(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { pausasec(); }*/
			renderHomePage();
			pausasec();
		}
		if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

			state = 3;
			prepareHomePage();
			/*while(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { pausasec(); }*/
			renderHomePage();
			pausasec();
		}
		if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {

			state = 1;
			prepareHomePage();
			/*while(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { pausasec(); }*/
			renderHomePage();
			pausasec();
		}
		if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

			state = 1;
			prepareHomePage();
			/*while(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { pausasec(); }*/
			renderHomePage();
			pausasec();
		}
		if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			resetHighScore();
			//prepareHS();
			//renderHS();
		}
		break;
		default: 
			if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {

			state = 0;
			prepareHomePage();
			/*while(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { pausasec(); }*/
			renderHomePage();
			pausasec();
		}
			if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

			state = 0;
			prepareHomePage();
			/*while(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { pausasec(); }*/
			renderHomePage();
			pausasec();
		}
			if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {

			state = 2;
			prepareHomePage();
			/*while(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { pausasec(); }*/
			renderHomePage();
			pausasec();
		}
			if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

			state = 2;
			prepareHomePage();
			//while(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { pausasec(); }
			renderHomePage();
			pausasec();
		}
			if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }
			break;
	}
}


void processMouseHomePage(GLFWwindow* window, double xposIn, double yposIn) {}
