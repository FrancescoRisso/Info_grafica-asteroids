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
};

}  // namespace Asteroids

#endif
