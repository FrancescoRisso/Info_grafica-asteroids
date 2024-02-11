#ifndef _END_SCREEN_H
#define _END_SCREEN_H


#include "../../Main.hpp"
#include "../displayString.hpp"


enum endScreenStrings { gmOver, yourScore, hiScore, newBest, restart, goHome1, goHome2, endScreen_NUM_STRINGS };


/*
	prepareEndScreen
	---------------------------------------------------------------------
	Does all the initializations for the end screen
*/
void prepareEndScreen();


/*
	renderEndScreen
	---------------------------------------------------------------------
	Does all the updating and rendering of the end screen
*/
void renderEndScreen();


/*
	updateTransformEndScreen
	---------------------------------------------------------------------
	Updates the tranformation matrices of all the end screen objects
*/
void updateTransformEndScreen();


/*
	processKeyboardEndScreen
	---------------------------------------------------------------------
	Does all the processing of keyboard inputs during the end screen
	---------------------------------------------------------------------
	PARAMETERS:
		- window: the window where the keyboard is considered
*/
void processKeyboardEndScreen(GLFWwindow* window);


/*
	processMouseEndScreen
	---------------------------------------------------------------------
	Does all the processing of the mouse position during the end screen
	---------------------------------------------------------------------
	PARAMETERS:
		- window: the window where the mouse is
		- xposIn: the x coordinate of the mouse
		- yposIn: the y coordinate of the mouse
*/
void processMouseEndScreen(GLFWwindow* window, double xposIn, double yposIn);


/*
	setScoresEndScreen
	---------------------------------------------------------------------
	Updates the strings to display the current and high score
	---------------------------------------------------------------------
	PARAMETERS:
		- score: this player's score
*/
void setScoresEndScreen(int score);


/*
	getHighScore
	---------------------------------------------------------------------
	Get current highscore to use in other files

*/

int getHighScore();


/*
	resetHighScore
	---------------------------------------------------------------------
	Reet current highscore

*/

void resetHighScore();
void setHighScore(int a);

#endif
