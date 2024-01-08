#ifndef _SPACESHIP_H
#define _SPACESHIP_H

#include "object.hpp"

#define NumTrianglesSpaceship 3

namespace Asteroids {

class Spaceship : public Object {
   public:
	Spaceship();

	void Draw() const override;
	void Move() override {};
	void MoveDir(direction dir) override;
	void Init(glm::vec2 pos, glm::vec2 speed) override;  // speed is ignored, since spaceship does not move autonomously
	void Init(glm::vec2 pos) {
		Init(pos, glm::vec2(0));
	}
	void PointTo(glm::vec2 mousePos);

   private:
	float points[NumTrianglesSpaceship * 3 * 2] = {0};
};

}  // namespace Asteroids

#endif
