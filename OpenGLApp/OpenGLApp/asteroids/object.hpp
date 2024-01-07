#ifndef _OBJECT_H
#define _OBJECT_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../shader_s.h"
#include "../utils.h"

namespace Asteroids {

enum direction { up, down, left, right };

class Object {
   public:
	Object();

	virtual void Draw() const = 0;
	virtual void Move();
	virtual void Move(direction dir) {};
	virtual void Init() = 0;

   protected:
	glm::vec2 pos;
	glm::vec2 speed;

	float angle = 0;

	glm::mat4 transform;

	Shader shader;
	unsigned int VBO = 0, VAO = 0;

	float radius = 0;

	virtual void updateTransform();
};

}  // namespace Asteroids

#endif
