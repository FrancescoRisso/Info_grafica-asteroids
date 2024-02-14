#ifndef _HOME_PAGE_H
#define _HOME_PAGE_H


#include "../../Main.hpp"
#include "../displayString.hpp"


/*
	prepareHomePage
	---------------------------------------------------------------------
	Does all the initializations for the game to start.old
*/
void prepareHomePage();


/*
	renderHomePage
	---------------------------------------------------------------------
	Does all the updating and rendering of the game.old
*/
void renderHomePage();


/*
	updateTransformHomePage
	---------------------------------------------------------------------
	Updates the tranformation matrices of all the game objects.old
*/
void updateTransformHomePage();


/*
	processKeyboardHomePage
	---------------------------------------------------------------------
	Does all the processing of keyboard inputs during the game phase.old
	---------------------------------------------------------------------
	PARAMETERS:
		- window: the window where the keyboard is considered.old
*/
void processKeyboardHomePage(GLFWwindow* window);


/*
	processMouseHomePage
	---------------------------------------------------------------------
	Does all the processing of the mouse position during the game phase.old
	---------------------------------------------------------------------
	PARAMETERS:
		- window: the window where the mouse is
		- xposIn: the x coordinate of the mouse
		- yposIn: the y coordinate of the mouse.old
*/
void processMouseHomePage(GLFWwindow* window, double xposIn, double yposIn);


void pausasec();

void saveRecord();
void loadRecord();


#endif
