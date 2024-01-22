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

extern float deltaTime;

namespace Asteroids {

enum direction { up, down, left, right };

class Object {
   public:
	Object();

	virtual void Init(glm::vec2 pos, glm::vec2 speedDirection) = 0;

	virtual void Draw() const = 0;

	virtual void Move();

	virtual void updateTransform();

	virtual bool isOutOfScreen();

   protected:
	glm::vec2 pos;
	glm::vec2 speed;

	float angle = 0;

	glm::mat4 transform;

	Shader shader;
	unsigned int VBO = 0, VAO = 0;

	float radius = 0;

	float lastFrame = 0;

	virtual bool canExitTheScreen() const {
		return false;
	};

	void limitMovementToScreen();


	/*
		findDistanceFrom
		---------------------------------------------------------------------
		Computes the distance from this object to a given point
		The distance is considered from the surface, not from the middle
		---------------------------------------------------------------------
		PARAMETERS:
			- p: the point where to compute the distance from (in real OpenGL
				coordinates)
		---------------------------------------------------------------------
		OUTPUT:
			- the distance
	*/
	float findDistanceFrom(glm::vec2 p);


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
	glm::vec2 findRadiusTowards(glm::vec2 p);
};

}  // namespace Asteroids

#endif
