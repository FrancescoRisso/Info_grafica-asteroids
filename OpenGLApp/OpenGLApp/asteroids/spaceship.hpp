#ifndef _SPACESHIP_H
#define _SPACESHIP_H

#include "_debugOpts.hpp"
#include "object.hpp"
#include "projectile.hpp"


/*
	SPACESHIP
	---------------------------------------------------------------------
	This is the class that describes the spaceship
*/

namespace Asteroids {

enum explosionLevel_t { bubbled, explosion_none, explosion_1, explosion_2, explosion_3, explosion_NUM };



class Spaceship : public Object {
   public:
	Spaceship();


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
	void changeBubble();

	// Init: implemented as required by class Object.
	// Since speed is fixed (assigned by Init), there is no need to pass an
	// initial one to the function, therefore an extra Init method is defined,
	// without the speed parameter
	void Init(glm::vec2 pos, float angle) override;  // speed is ignored, since spaceship does not move autonomously
	void Init(glm::vec2 pos) {
		Init(pos, 0);
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

	staticVariablesAndFunctionDefinitions_hpp(Spaceship);


	/*
		setExplosionLevel
		---------------------------------------------------------------------
		Sets the spaceship to use a certain explosion level texture
		---------------------------------------------------------------------
		PARAMETERS:
			- explosionLevel: how much the spaceship is exploding
	*/
	void setExplosionLevel(explosionLevel_t explosionLevel);

   private:
	// lastMousePos: the last recorded target of PointTo()
	glm::vec2 lastMousePos;

	// set number of triangles to be rendered
	int numTriangles() const override {
		return numTriangles_Spaceship;
	};

	availableShaders shaderChoice() const override {
		return shader_withTexture;
	}

	float radius() const override {
		return radius_Spaceship;
	}

	static unsigned int explosionLevelTextures[explosion_NUM];


	/*
		addExplosionLevelTexture
		---------------------------------------------------------------------
		Creates a new texture and inserts the explosion_level-texture
		association in the vector
		---------------------------------------------------------------------
		PARAMETERS:
			- type: the type of powerup
			- path: the path to its texture
	*/
	void addExplosionLevelTexture(explosionLevel_t level, const char* path);
};

}  // namespace Asteroids

#endif
