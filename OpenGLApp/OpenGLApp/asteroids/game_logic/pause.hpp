#ifndef _PAUSE_H
#define _PAUSE_H


#include "../../Main.hpp"
#include "../displayString.hpp"
#include "../heart.hpp"
#include "game.hpp"

/*
	preparePause
	---------------------------------------------------------------------
	Does all the initializations for the game to start
*/
void preparePause();


/*
	renderPause
	---------------------------------------------------------------------
	Does all the updating and rendering of the game
*/
void renderPause();


/*
	updateTransformPause
	---------------------------------------------------------------------
	Updates the tranformation matrices of all the game objects
*/
void updateTransformPause();


/*
	processKeyboardPause
	---------------------------------------------------------------------
	Does all the processing of keyboard inputs during the game phase
	---------------------------------------------------------------------
	PARAMETERS:
		- window: the window where the keyboard is considered
*/
void processKeyboardPause(GLFWwindow* window);


/*
	processMousePause
	---------------------------------------------------------------------
	Does all the processing of the mouse position during the game phase
	---------------------------------------------------------------------
	PARAMETERS:
		- window: the window where the mouse is
		- xposIn: the x coordinate of the mouse
		- yposIn: the y coordinate of the mouse
*/
void processMousePause(GLFWwindow* window, double xposIn, double yposIn);


#endif
