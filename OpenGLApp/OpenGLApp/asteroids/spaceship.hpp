#ifndef _SPACESHIP_H
#define _SPACESHIP_H

#include "object.hpp"

#define NumPointsSpaceship 9

namespace Asteroids {

// class Spaceship {
class Spaceship : public Object {
   public:
	Spaceship();

	void Draw() const override;
	void Move() override {};
	void MoveDir(direction dir) override;
	void Init() override;
	void PointTo(glm::vec2 mousePos);

   private:
	const float moveBase = 0.0001;

	float points[NumPointsSpaceship * 2] = {0};
};

}  // namespace Asteroids

#endif
