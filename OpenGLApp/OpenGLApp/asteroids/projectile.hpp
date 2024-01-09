#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "object.hpp"

#define NumTrianglesProjectile 2

namespace Asteroids {

class Projectile : public Object {
   public:
	Projectile();

	void Draw() const override;
	void Init(glm::vec2 pos, glm::vec2 speed) override;

   private:
	float points[NumTrianglesProjectile * 3 * 2] = {0};

   protected:
	bool canExitTheScreen() const override {
		return true;
	};
};

}  // namespace Asteroids

#endif
