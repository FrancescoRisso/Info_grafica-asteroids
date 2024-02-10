#ifndef _INSTRUCTIONS_LOGIC_H
#define _INSTRUCTIONS_LOGIC_H


#include "../../Main.hpp"
#include "../displayString.hpp"
#include "instructions.hpp"


/*
	prepareInstructions
	---------------------------------------------------------------------
	Does all the initializations for the game to start
*/
void prepareInstructions();


/*
	renderInstructions
	---------------------------------------------------------------------
	Does all the updating and rendering of the game
*/
void renderInstructions();


/*
	updateTransformInstructions
	---------------------------------------------------------------------
	Updates the tranformation matrices of all the game objects
*/
void updateTransformInstructions();


/*
	processKeyboardInstructions
	---------------------------------------------------------------------
	Does all the processing of keyboard inputs during the game phase
	---------------------------------------------------------------------
	PARAMETERS:
		- window: the window where the keyboard is considered
*/
void processKeyboardInstructions(GLFWwindow* window);


/*
	processMouseInstructions
	---------------------------------------------------------------------
	Does all the processing of the mouse position during the game phase
	---------------------------------------------------------------------
	PARAMETERS:
		- window: the window where the mouse is
		- xposIn: the x coordinate of the mouse
		- yposIn: the y coordinate of the mouse
*/
void processMouseInstructions(GLFWwindow* window, double xposIn, double yposIn);


#endif
