#ifndef _LETTER_H
#define _LETTER_H

#include <map>

#include "object.hpp"

/*
	LETTER
	---------------------------------------------------------------------
	This is the class that describes a star
*/

namespace Asteroids {

class Letter : public Object {
   public:
	Letter();


	/*
		Spawn
		---------------------------------------------------------------------
		Spawns a star in a random location, rotated at a random angle
	*/
	void Spawn();


	// Init: implemented as required by class Object
	void Init(glm::vec2 pos, float angle) override;


	staticVariablesAndFunctionDefinitions_hpp(Letter);


	/*
		setCharacter
		---------------------------------------------------------------------
		Tells a letter to print a given character
		---------------------------------------------------------------------
		PARAMETERS:
			- c: the character to be printed
		---------------------------------------------------------------------
		OUTPUT:
			-
	*/
	void setCharacter(char c);


   protected:
	// projectile can exit the screen: the default "false" is overwritten here
	bool canExitTheScreen() const override {
		return true;
	};

	// set number of triangles to be rendered
	int numTriangles() const override {
		return numTriangles_Letter;
	};

	availableShaders shaderChoice() const override {
		return shader_textureTransparency;
	}

	float radius() const override {
		return 0.5;
	}

	glm::vec3 color() const override {
		return glm::vec3(1, 1, 1);
	}

   private:
	/*
		addCharacterTexture
		---------------------------------------------------------------------
		Creates a new texture and inserts the id in the correct character of
		the mapping
		---------------------------------------------------------------------
		PARAMETERS:
			- c: the character to be added
			- path: the path to its texture
			- the width (in pixels) of the character texture
	*/
	void addCharacterTexture(char c, const char* path, unsigned char width);


	static std::map<char, unsigned int> charToId;
	static std::map<char, unsigned char> letterWidth;
};

}  // namespace Asteroids

#endif
