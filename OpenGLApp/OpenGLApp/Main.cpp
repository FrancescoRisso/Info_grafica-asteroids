#include "Main.hpp"


using namespace Asteroids;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

// mouse
float deltaTime;
float lastFrame = 0;

Star stars[numStars];

gamePhases currentPhase = mainMenu;


int main() {
	// init randomness
	srand(time(NULL));

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SpaceVoid", NULL, NULL);
	if(window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	loadRecord();
	prepareGame();
	prepareEndScreen();
	prepareInstructions();
	prepareHomePage();

	for(int i = 0; i < numStars; i++) stars[i].Spawn();

	glEnable(GL_DEPTH_TEST);

	// render loop
	// -----------
	while(!glfwWindowShouldClose(window)) {
		// if(hasDied) continue;

		// input
		// -----
		processInput(window);

		// timings
#ifdef DEBUG_fixedDeltaTime
		deltaTime = 0.0005;
#else
		float curTime = (float) glfwGetTime();
		deltaTime = curTime - lastFrame;
		lastFrame = curTime;
#endif

		// render
		// ------
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for(int i = 0; i < numStars; i++) {
			stars[i].Draw();
			stars[i].Move();
			if(stars[i].isOutOfScreen()) stars[i].Spawn();
		}

		switch(currentPhase) {
			case mainMenu: renderHomePage(); break;
			case instructions: renderInstructions(); break;
			case game: renderGame(); break;
			case endScreen: renderEndScreen(); break;
		}


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		saveRecord();
		glfwSetWindowShouldClose(window, true);
	}

	switch(currentPhase) {
		case instructions: processKeyboardInstructions(window); break;
		case game: processKeyboardGame(window); break;
		case endScreen: processKeyboardEndScreen(window); break;
		case mainMenu: processKeyboardHomePage(window); break;
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;

	for(int i = 0; i < numStars; i++) stars[i].updateTransform();
	updateTransformGame();
	updateTransformEndScreen();
	updateTransformInstructions();
	updateTransformHomePage();
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	switch(currentPhase) {
		case instructions: processMouseInstructions(window, xposIn, yposIn); break;
		case game: processMouseGame(window, xposIn, yposIn); break;
		case endScreen: processMouseEndScreen(window, xposIn, yposIn); break;
	}
}
