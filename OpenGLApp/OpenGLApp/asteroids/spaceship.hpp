#ifndef _SPACESHIP_H
#define _SPACESHIP_H

#include "object.hpp"
#include "projectile.hpp"

/*
	SPACESHIP
	---------------------------------------------------------------------
	This is the class that describes the spaceship
*/


// NumTrianglesSpaceship: the number of triangles that compose the render
// of the spaceship
#define NumTrianglesSpaceship 3

namespace Asteroids {

class Spaceship : public Object {
   public:
	Spaceship();


	// Draw: implemented as required by class Object
	void Draw() const override;


	// Move: disabled the automatic movement defined in Object
	void Move() override {};


	/*
		moveDir
		---------------------------------------------------------------------
		Moves the spaceship in a certain direction, based on the time elapsed
		from the last frame
		---------------------------------------------------------------------
		PARAMETERS:
			- dir: the direction where to move
	*/
	void MoveDir(direction dir);


	// Init: implemented as required by class Object.
	// Since speed is fixed (assigned by Init), there is no need to pass an
	// initial one to the function, therefore an extra Init method is defined,
	// without the speed parameter
	void Init(glm::vec2 pos, glm::vec2 speedDirection) override;  // speed is ignored, since spaceship does not move autonomously
	void Init(glm::vec2 pos) {
		Init(pos, glm::vec2(0));
	}

	/*
		PointTo
		---------------------------------------------------------------------
		Changes the spaceship's angle in order to aim for a specific point,
		generally the mouse position
		---------------------------------------------------------------------
		PARAMETERS:
			- mousePos: the point where the spaceship should aim (in units,
				so coordinates should range between -1 and +1)
	*/
	void PointTo(glm::vec2 mousePos);


	/*
		Shoot
		---------------------------------------------------------------------
		Creates a projectile from the current position of the spaceship,
		pointing in the direction the spaceship is currently aiming
		---------------------------------------------------------------------
		OUTPUT:
			- the Projectile object that represents the projectile that was
				shot
	*/
	Projectile Shoot();

   private:

	// points: the array of points defining the triangles of the spaceship
	float points[NumTrianglesSpaceship * 3 * 2] = {0};

	// lastMousePos: the last recorded target of PointTo()
	glm::vec2 lastMousePos;
};

}  // namespace Asteroids

#endif
