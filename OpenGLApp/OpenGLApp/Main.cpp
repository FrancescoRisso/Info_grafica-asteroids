// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <iostream>
#include <list>

#include "utils.hpp"
#include "shader_s.h"
#include "asteroids/spaceship.hpp"
#include "asteroids/projectile.hpp"
#include "asteroids/asteroid.hpp"
#include "asteroids/star.hpp"
#include "asteroids/displayString.hpp"
#include "asteroids/_debugOpts.hpp"


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
float lastX, lastY;
bool firstMouse = true;

int destroyedAsteroids = 0;

float timeFromLastSpawn = 0;
float timeFromLastShot = 0;

Star stars[numStars];

Spaceship spaceship;
std::list<Projectile> projectiles;
std::list<Asteroid> asteroids;
DisplayString scoreDisplay;

bool hasDied = false;

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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Asteroids", NULL, NULL);
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

	spaceship.Init(glm::vec2(0));

	for(int i = 0; i < numStars; i++) stars[i].Spawn();

	scoreDisplay.Init(glm::vec2(-0.95, 0.9), "Score: 0", alignLeft, alignTop, glm::vec3(1), 0.1);

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
		timeFromLastSpawn += deltaTime;

		// render
		// ------
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		scoreDisplay.Draw();

		for(int i = 0; i < numStars; i++) {
			stars[i].Draw();
			stars[i].Move();
			if(stars[i].isOutOfScreen()) stars[i].Spawn();
		}

		int tmp = Star::VAO;

		auto projectilePtr = projectiles.begin();
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
			projectilePtr->Move();

			projectilePtr++;
		}

		if(Asteroid::ShouldSpawn()) {
			Asteroid tmpAsteroid;
			tmpAsteroid.Spawn();
			asteroids.push_back(tmpAsteroid);
		}

		auto asteroidPtr = asteroids.begin();
		while(asteroidPtr != asteroids.end()) {
			asteroidPtr->Draw();
			asteroidPtr->Move();
			if(asteroidPtr->isOutOfScreen()) {
				asteroidPtr = asteroids.erase(asteroidPtr);
				continue;
			}

			if(asteroidPtr->collidesWith(&spaceship)) hasDied = true;
			asteroidPtr++;
		}

		spaceship.Draw();

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
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) spaceship.MoveDir(up);
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) spaceship.MoveDir(down);
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) spaceship.MoveDir(left);
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) spaceship.MoveDir(right);
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if(timeFromLastShot > 1.0 / speed_autoShoot) timeFromLastShot = 0;
		if(timeFromLastShot == 0) projectiles.push_back(spaceship.Shoot());
		timeFromLastShot += deltaTime;
	}
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) timeFromLastShot = 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;

	spaceship.updateTransform();
	for(int i = 0; i < numStars; i++) stars[i].updateTransform();
	scoreDisplay.updateTransform();
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	float xpos = (float) xposIn;
	float ypos = (float) yposIn;

	if(firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;  // reversed since y-coordinates go from bottom to top

	spaceship.PointTo(mouse2graphicCoords(glm::vec2(xpos, ypos), glm::vec2(SCR_WIDTH, SCR_HEIGHT)));

	lastX = xpos;
	lastY = ypos;
}


bool checkAsteroidProjectileCollision(std::list<Asteroids::Projectile>::iterator proj) {
	auto asteroidPtr = asteroids.begin();

	while(asteroidPtr != asteroids.end()) {
		if(asteroidPtr->collidesWith(&(*proj))) {
			while(asteroidPtr->hasChildren()) asteroids.push_back(asteroidPtr->getChild());
			asteroidPtr = asteroids.erase(asteroidPtr);
			destroyedAsteroids++;
			char buf[20];
			sprintf_s(buf, "Score: %d", destroyedAsteroids);
			scoreDisplay.changeString((const char*) buf);
			return true;
		}
		asteroidPtr++;
	}

	return false;
}
