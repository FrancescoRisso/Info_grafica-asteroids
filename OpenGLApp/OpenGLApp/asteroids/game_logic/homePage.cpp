#include "homePage.hpp"
#include "../logo.hpp"
#include "stdio.h"
#include <chrono> // Include per la gestione del tempo
#pragma warning(disable : 4996)

// Funzione per mettere in pausa il programma per 1 secondo
void pausasec() {
	// Ottieni l'istante di tempo corrente
	auto oraCorrente = std::chrono::high_resolution_clock::now();

	// Calcola l'istante di tempo futura (mezzo secondo dopo l'istante corrente)
	auto istanteFutura = oraCorrente + std::chrono::milliseconds(300);

	// Attendi finché l'istante di tempo futura non viene raggiunto
	while(std::chrono::high_resolution_clock::now() < istanteFutura) {
		// Attendi...
	}
}


using namespace Asteroids;


enum homepageStrings {explore, instruct, highscore, quit, home_NUM_STRINGS };

DisplayString homeStrings[home_NUM_STRINGS];

extern gamePhases currentPhase;

static int state = 0;

void saveRecord() {
    FILE *file;
	int variabile = getHighScore();  // Inizializza la variabile

    file = fopen("./resources/record", "w");  // Apri o crea il file
    if (file == NULL) {
        printf("Impossibile aprire il file.\n");
        return;
    }

    fprintf(file, "%d", variabile);  // Scrivi la variabile sul file
    fclose(file);  // Chiudi il file
}

void loadRecord() {
	FILE* file;
	int variabile;

	file = fopen("./resources/record", "r");  // Apri il file
	if(file == NULL) {
		printf("Impossibile aprire il file.\n");
		return;
	}

	fscanf(file, "%d", &variabile);  // Leggi il dato dal file e inseriscilo nella variabile
	fclose(file);                    // Chiudi il file

	setHighScore(variabile);
}

void prepareHomePage() {
	char buf[100];
	int highScore = getHighScore();
	if(highScore == -1) highScore++;
	saveRecord();
	sprintf_s(buf, "Best score: %d", highScore);
	switch(state) {
		case 0: 
		//homeStrings[spacevoid].Init(glm::vec2(0, 0.65), " SPACEVOID", alignCenterHoriz, alignCenterVert, glm::vec3(0), 0.25);
		homeStrings[explore].Init(glm::vec2(0, 0.15), "Start Exploring", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.10);
		homeStrings[instruct].Init(glm::vec2(0, 0.0), "Instructions", alignCenterHoriz, alignCenterVert, glm::vec3(0.5), 0.10);
		homeStrings[highscore].Init(glm::vec2(0, -0.15), buf, alignCenterHoriz, alignCenterVert, glm::vec3(0.5), 0.10);
		homeStrings[quit].Init(glm::vec2(0, -0.30), "Quit", alignCenterHoriz, alignCenterVert, glm::vec3(0.5), 0.10);
		break;
		case 1:
		//homeStrings[spacevoid].Init(glm::vec2(0, 0.65), " SPACEVOID", alignCenterHoriz, alignCenterVert, glm::vec3(0), 0.25);
		homeStrings[explore].Init(glm::vec2(0, 0.15), "Start Exploring", alignCenterHoriz, alignCenterVert, glm::vec3(0.5), 0.10);
		homeStrings[instruct].Init(glm::vec2(0, 0.0), "Instructions", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.10);
		homeStrings[highscore].Init(glm::vec2(0, -0.15), buf, alignCenterHoriz, alignCenterVert, glm::vec3(0.5), 0.10);
		homeStrings[quit].Init(glm::vec2(0, -0.30), "Quit", alignCenterHoriz, alignCenterVert, glm::vec3(0.5), 0.10);
		break;
		case 2:
		//homeStrings[spacevoid].Init(glm::vec2(0, 0.65), " SPACEVOID", alignCenterHoriz, alignCenterVert, glm::vec3(0), 0.25);
		homeStrings[explore].Init(glm::vec2(0, 0.15), "Start Exploring", alignCenterHoriz, alignCenterVert, glm::vec3(0.5), 0.10);
		homeStrings[instruct].Init(glm::vec2(0, 0.0), "Instructions", alignCenterHoriz, alignCenterVert, glm::vec3(0.5), 0.10);
		homeStrings[highscore].Init(glm::vec2(0, -0.15), "Reset Highscores", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.10);
		homeStrings[quit].Init(glm::vec2(0, -0.30), "Quit", alignCenterHoriz, alignCenterVert, glm::vec3(0.5), 0.10);
		break;
		default:
		//homeStrings[spacevoid].Init(glm::vec2(0, 0.65), " SPACEVOID", alignCenterHoriz, alignCenterVert, glm::vec3(0), 0.25);
		homeStrings[explore].Init(glm::vec2(0, 0.15), "Start Exploring", alignCenterHoriz, alignCenterVert, glm::vec3(0.5), 0.10);
		homeStrings[instruct].Init(glm::vec2(0, 0.0), "Instructions", alignCenterHoriz, alignCenterVert, glm::vec3(0.5), 0.10);
		homeStrings[highscore].Init(glm::vec2(0, -0.15), buf, alignCenterHoriz, alignCenterVert, glm::vec3(0.5), 0.10);
		homeStrings[quit].Init(glm::vec2(0, -0.30), "Quit", alignCenterHoriz, alignCenterVert, glm::vec3(1), 0.10);
		break;
	}
	/* instrStrings[shoot].Init(glm::vec2(-0.90, -0.3), " - shoot with SPACE", alignLeft, alignCenterVert, glm::vec3(1), 0.10);
	instrStrings[move].Init(glm::vec2(-0.90, -0.45), " - move with WASD", alignLeft, alignCenterVert, glm::vec3(1), 0.10);
	instrStrings[lives].Init(glm::vec2(-0.90, -0.6), "Once you finish your 3 lives, the game ends.", alignLeft, alignCenterVert, glm::vec3(1), 0.10);
	instrStrings[returnMain].Init(glm::vec2(0.90, -0.8), "Press M to return to main menu.", alignRight, alignCenterVert, glm::vec3(1), 0.06);
*/
}

void logoPrint() {
	Spacevoid spacevoid;
	spacevoid.Init(glm::vec2(0));
	spacevoid.Draw();
}


void renderHomePage() {
	for(int i = 0; i < home_NUM_STRINGS; i++) { homeStrings[i].Draw(); }
	logoPrint();
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
			if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			saveRecord();
			glfwSetWindowShouldClose(window, true);
			}
			break;
	}
}


void processMouseHomePage(GLFWwindow* window, double xposIn, double yposIn) {}
