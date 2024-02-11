#ifndef _POWERUP_H
#define _POWERUP_H

#include "object.hpp"

/*
	POWERUP
	---------------------------------------------------------------------
	This is the class that describes a powerup
*/

namespace Asteroids {

enum powerup_t { extraLife, destroyAsteroids, powerup_NUM };

class Powerup : public Object {
   public:
	Powerup();


	/*
		Spawn
		---------------------------------------------------------------------
		Spawns a powerup in a random location, rotated at a random angle
	*/
	void Spawn();


	// Init: implemented as required by class Object
	void Init(glm::vec2 pos, float angle) override;


	staticVariablesAndFunctionDefinitions_hpp(Powerup);


	/*
		getType
		---------------------------------------------------------------------
		Returns the type of powerup
		---------------------------------------------------------------------
		OUTPUT:
			- the type of this powerup
	*/
	powerup_t getType();

	/*
		shouldSpawn
		---------------------------------------------------------------------
		Randomizes if a powerup should spawn now
		---------------------------------------------------------------------
		OUTPUT:
			- whether the powerup should spawn now
	*/
	static bool shouldSpawn();


   protected:
	// projectile can exit the screen: the default "false" is overwritten here
	bool canExitTheScreen() const override {
		return true;
	};

	// set number of triangles to be rendered
	int numTriangles() const override {
		return numTriangles_Powerup;
	};

	availableShaders shaderChoice() const override {
		return shader_withTexture;
	}

	float radius() const override {
		return radius_Powerup;
	}

   private:
	powerup_t type;

	static unsigned int textureIds[powerup_NUM];


	/*
		addTypeTexture
		---------------------------------------------------------------------
		Creates a new texture and inserts the type-texture association in the
		vector
		---------------------------------------------------------------------
		PARAMETERS:
			- type: the type of powerup
			- path: the path to its texture
	*/
	void addTypeTexture(powerup_t type, const char* path);
};

}  // namespace Asteroids

#endif
