#ifndef _DISPLAY_STRING_H
#define _DISPLAY_STRING_H

#include "letter.hpp"
#include "object.hpp"


/*
	STRING
	---------------------------------------------------------------------
	This is the class that describes a string, which is a sequence of
	letters
*/

namespace Asteroids {

class DisplayString {
   public:
	DisplayString();


	/*
		Draw
		---------------------------------------------------------------------
		Draws all the letters of this string
	*/
	void Draw() const;


	/*
		updateTransform
		---------------------------------------------------------------------
		Updates the transformation matrices of the letters
	*/
	void updateTransform();

	/*
		Init
		---------------------------------------------------------------------
		Initializes the string with all the required data
		---------------------------------------------------------------------
		PARAMETERS:
			- pos: the position of the letter
			- string: the initial content of the string display
			- horizontalAlignment: whether pos refers to the left side, the
				right side, or the center of the letter
			- verticalAlignment: whether pos refers to the top side, the
				bottom side, or the center of the letter
			- color: the color used to display the letter
			- height: the height of the letter, in OpenGL units
	*/
	void Init(glm::vec2 pos, const char* s, horizAligns horizontalAlignment, vertAligns verticalAlignment, glm::vec3 color, float height);


   private:
	std::vector<char> charSequence;
	std::vector<Letter> letterObjects;

	horizAligns horizontalAlignment;
	vertAligns verticalAlignment;

	glm::vec3 color;

	float height;

	/*
		shiftLetters
		---------------------------------------------------------------------
		Tells the letters the correct shifts to form the string
	*/
	void shiftLetters();
};

}  // namespace Asteroids


#endif
