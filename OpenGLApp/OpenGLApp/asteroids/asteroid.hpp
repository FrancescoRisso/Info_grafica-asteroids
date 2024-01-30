#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "_debugOpts.hpp"
#include "object.hpp"
#include "object_staticVariablesDefs.hpp"
#include "parameters.hpp"


/*
	ASTEROID
	---------------------------------------------------------------------
	This is the class that describes an asteroid
*/

namespace Asteroids {

enum size_t { small, medium, large };

class Asteroid : public Object {
   public:
	Asteroid();


	// Init: implemented as required by class Object
	void Init(glm::vec2 pos, float angle) override;


	/*
		Spawn
		---------------------------------------------------------------------
		Executes the Init(), spawning an asteroid in a random place on the
		border of the screen, with a random initial speed
	*/
	void Spawn();


	/*
		ShouldSpawn
		---------------------------------------------------------------------
		Tells if an asteroid should be spawned right now
		---------------------------------------------------------------------
		OUTPUT:
			- whether the main callee should spawn an asteroid or not
	*/
	static bool ShouldSpawn();


   protected:
	staticShader(Asteroid);
	staticTextures(Asteroid);


	static unsigned int VAO_small, VAO_medium, VAO_large;
	static unsigned int VBO_small, VBO_medium, VBO_large;
	static bool VAOset_small, VAOset_medium, VAOset_large;

	bool VaoVboAreSet() const override {
		switch(size) {
			case small: return Asteroid::VAOset_small;
			case large: return Asteroid::VAOset_large;
			default: return Asteroid::VAOset_medium;
		}
	}

	unsigned int getVAO() const override {
		switch(size) {
			case small: return Asteroid::VAO_small;
			case large: return Asteroid::VAO_large;
			default: return Asteroid::VAO_medium;
		}
	}

	void setVAO(unsigned int VAO) override {
		switch(size) {
			case small:
				VAO_small = VAO;
				VAOset_small = true;
				break;
			case large:
				VAO_large = VAO;
				VAOset_large = true;
				break;
			default:
				VAO_medium = VAO;
				VAOset_medium = true;
				break;
		}
	}

	unsigned int getVBO() const override {
		switch(size) {
			case small: return Asteroid::VBO_small;
			case large: return Asteroid::VBO_large;
			default: return Asteroid::VBO_medium;
		}
	}

	void setVBO(unsigned int VBO) override {
		switch(size) {
			case small:
				VBO_small = VBO;
				VAOset_small = true;
				break;
			case large:
				VBO_large = VBO;
				VAOset_large = true;
				break;
			default:
				VBO_medium = VBO;
				VAOset_medium = true;
				break;
		}
	}

	// Asteroid can exit the screen: the default "false" is overwritten here
	bool canExitTheScreen() const override {
		return true;
	};

	// set number of triangles to be rendered
	int numTriangles() const override {
		return numTriangles_Asteroid;
	};

	availableShaders shaderChoice() const override {
		return shader_withTexture;
	}

	float radius() const override {
		switch(size) {
			case small: return radius_smallAsteroid;
			case medium: return radius_mediumAsteroid;
			case large: return radius_largeAsteroid;
			default: return radius_smallAsteroid;
		}
	}

   private:
	// size: the size of this asteroid
	size_t size;

	// children: the sizes of the children asteroids
	std::vector<size_t> children;

	/*
		randomizeSize
		---------------------------------------------------------------------
		Chooses a random size and updates all the relativive attributes
		(including the ones related to the children)
	*/
	void randomizeSize();
};

}  // namespace Asteroids

#endif
