#ifndef _SPACESHIP_H
#define _SPACESHIP_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../shader_s.h"

#define root2div2 (float) 0.70710678

namespace Asteroids {

enum direction { up, down, left, right };

class Spaceship {
   public:
	Spaceship();

	void Draw();
	void Move(direction dir);
	void Init();

   private:
	glm::vec2 pos;
	float angle;
	Shader shader;
	unsigned int VBO, VAO;
	glm::mat4 transform;

	const float radius = 0.1;
	const float moveBase = 0.0001;

	// clang-format off
	float points[9*2] = {
		(float) radius * root2div2,		(float) radius * root2div2,
		(float) -radius * root2div2,	(float) radius * root2div2,
		(float) radius * root2div2,		(float) -radius * root2div2,

		(float) -radius * root2div2,	(float) -radius * root2div2,
		(float) -radius * root2div2,	(float) radius * root2div2,
		(float) radius * root2div2,		(float) -radius * root2div2,

		(float) radius * root2div2,		(float) radius * root2div2,
		(float) -radius * root2div2,	(float) radius * root2div2,
		(float) 0,						(float) radius,
	};
	// clang-format on

	void updateTransform();
};

}  // namespace Asteroids

#endif
