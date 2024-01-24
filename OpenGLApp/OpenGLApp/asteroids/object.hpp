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
			- speedDirection: the direction where the object is moving
	*/
	virtual void Init(glm::vec2 pos, glm::vec2 speedDirection) = 0;



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


	/*
		collidesWith
		---------------------------------------------------------------------
		Checks if the object is colliding with another object
		---------------------------------------------------------------------
		PARAMETERS:
			- o: a pointer to the other object
		---------------------------------------------------------------------
		OUTPUT:
			- whether the two objects' hitboxes collide
	*/
	virtual bool collidesWith(Object* o);

   protected:
	// pos: the position on the screen
	glm::vec2 pos;

	// speed: the speed (vector) at which the object is moving
	// it's what Move() uses to compute the next position
	glm::vec2 speed;

	// angle: the rotation angle of the object around its center
	// angle = 0 points towards up, which is the positive Y direction
	float angle = 0;

	// transform: the matrix that applies the position, the rotation angle,
	// and the scaling factor in order to keep proportions fixed
	// independently from the viewport size
	glm::mat4 transform;

	// shader: the program (fragment sh + vertex sh) used to render the object
	Shader shader;

	// VBO and VAO: the VBO and VAO that contain data about this object
	unsigned int VBO = 0, VAO = 0;

	// radius: the radius of the sphere that approximates the object
	float radius = 0;

	// canExitTheScreen: if the object is allowed to exit the screen
	// It's just an attribute, but implemented as function to be
	// overwritable by child classes
	virtual bool canExitTheScreen() const {
		return false;
	};

	/*
		limitMovementToScreen
		---------------------------------------------------------------------
		Checks if the object is allowed to exit the screen. If not, caps pos
		in order to have the object fully inside the screen
		TODO: fix proportions not working properly with this function
	*/
	void limitMovementToScreen();


	/*
		findDistanceFrom
		---------------------------------------------------------------------
		Computes the distance from this object to a given point
		The distance is considered from the surface, not from the middle
		---------------------------------------------------------------------
		PARAMETERS:
			- p: the point where to compute the distance from (in scaled
				coordinates)
		---------------------------------------------------------------------
		OUTPUT:
			- the distance, if p is outside the radius
			- -1, if p is inside the object
	*/
	virtual float findDistanceFrom(glm::vec2 p);


	/*
		findRadiusTowards
		---------------------------------------------------------------------
		Computes the vector of the (scaled) radius in the direction towards
		a given point
		---------------------------------------------------------------------
		PARAMETERS:
			- p: the point
		---------------------------------------------------------------------
		OUTPUT:
			- the vector from this object's surface to p (in scaled
				coordinates)
	*/
	virtual glm::vec2 findRadiusTowards(glm::vec2 p);
};

}  // namespace Asteroids

#endif
