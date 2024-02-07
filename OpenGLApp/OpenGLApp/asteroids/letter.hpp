#ifndef _LETTER_H
#define _LETTER_H

#include <map>

#include "object.hpp"

#define letterAspectRatio ((float) 5 / 10)

/*
	LETTER
	---------------------------------------------------------------------
	This is the class that describes a star
*/

namespace Asteroids {

enum horizAligns { alignLeft, alingCenterHoriz, alignRight };
enum vertAligns { alignTop, alignCenterVert, alignBottom };

class Letter : public Object {
   public:
	Letter();


	// Init: deactivated the default signature
	void Init(glm::vec2 pos, float angle) override {};


	/*
		Init
		---------------------------------------------------------------------
		Initializes the letter with all the required data
		---------------------------------------------------------------------
		PARAMETERS:
			- pos: the position of the letter
			- letter: which character should be displayed
			- horizontalAlignment: whether pos refers to the left side, the
				right side, or the center of the letter
			- verticalAlignment: whether pos refers to the top side, the
				bottom side, or the center of the letter
			- color: the color used to display the letter
			- height: the height of the letter, in OpenGL units
	*/
	void Init(glm::vec2 pos, char letter, horizAligns horizontalAlignment, vertAligns verticalAlignment, glm::vec3 color, float height);


	staticVariablesAndFunctionDefinitions_hpp(Letter);


	/*
		setCharacter
		---------------------------------------------------------------------
		Tells a letter to print a given character
		---------------------------------------------------------------------
		PARAMETERS:
			- c: the character to be printed
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
		return thisColor;
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

	glm::vec3 thisColor;
};

}  // namespace Asteroids

#endif
