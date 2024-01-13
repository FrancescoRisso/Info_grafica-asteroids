#ifndef _OBJECT_H
#define _OBJECT_H

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../shader_s.h"
#include "../utils.hpp"

/*
	OBJECT
	---------------------------------------------------------------------
	This is an abstract class that contains the common attributes and
	methods of any object that is on the screen.
	---------------------------------------------------------------------
	UNITS OF MEASURE:
		- all lenghts are measured in OpenGL units (the screen is 2 units
			wide and 2 units high, with coordinates ranging from (-1, -1)
			to (1, 1))
		- time is measured in real-life seconds (eg speed = 2 means that
			the object needs 1 real-life second to traverse the screen,
			independently from the framerate)
	---------------------------------------------------------------------
	PARAMETERS (that must be present as variables in another file):
		- deltaTime: the time elapsed from the last render (used to
			correctly compute the amount of movement from a frame to the
			next one)
*/

extern float deltaTime;

namespace Asteroids {

/*
	enum direction
	---------------------------------------------------------------------
	Provides an easy way to describe a direction
*/
enum direction { up, down, left, right };

class Object {
   public:
	/*
		constructor
		---------------------------------------------------------------------
		It must be empty, since in can be called when not all things are
		already defined.
		All the initialization must be done inside Init
	*/
	Object();


	/*
		Init (abstract)
		---------------------------------------------------------------------
		Initializes all the attributes needed for the object.
		It MUST be implemented by classes that derive from Object
		---------------------------------------------------------------------
		PARAMETERS:
			- pos: the initial position of the object
			- speed: the speed the object has
	*/
	virtual void Init(glm::vec2 pos, glm::vec2 speed) = 0;


	/*
		Draw (abstract)
		---------------------------------------------------------------------
		Binds all the required things (shaders, VAO, VBO, transformation
		matrix as a uniform), and then renders the object.
		The object MUST be rendered as centered in the origin, then it will
		be the transformation matrix that handles the position and rotation
		of the object
		It MUST be implemented by classes that derive from Object
	*/
	virtual void Draw() const = 0;


	/*
		Move
		---------------------------------------------------------------------
		Updates the position of the object, based on the speed
		It CAN be overwritten by classes that derive from Object
	*/
	virtual void Move();


	/*
		updateTransform
		---------------------------------------------------------------------
		Updates the transform matrix based on the current position and
		rotation angle
		It CAN be overwritten by classes that derive from Object
		It MUST be invoked every time position and angle (and eventually more
		parameters, if needed by the class) change
	*/
	virtual void updateTransform();


	/*
		isOutOfScreen
		---------------------------------------------------------------------
		Tells if an object is totally out of screen
		It CAN be overwritten by classes that derive from Object
		---------------------------------------------------------------------
		OUTPUT:
			- true: the object is totally out of the screen
			- false: at least part of the object is on screen
	*/
	virtual bool isOutOfScreen();

   protected:
	glm::vec2 pos;
	glm::vec2 speed;

	float angle = 0;

	glm::mat4 transform;

	Shader shader;
	unsigned int VBO = 0, VAO = 0;

	float radius = 0;

	virtual bool canExitTheScreen() const {
		return false;
	};

	void limitMovementToScreen();
};

}  // namespace Asteroids

#endif
