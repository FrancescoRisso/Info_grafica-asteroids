#ifndef _GAME_LOGIC_H
#define _GAME_LOGIC_H

#include <iostream>
#include <list>

#include "../../Main.hpp"
#include "../../utils.hpp"
#include "../asteroid.hpp"
#include "../displayString.hpp"
#include "../heart.hpp"
#include "../powerup.hpp"
#include "../projectile.hpp"
#include "../spaceship.hpp"
#include "endScreen.hpp"
#include "homePage.hpp"
#include "pause.hpp"

float getiFlash();
	
	/*
	prepareGame
	---------------------------------------------------------------------
	Does all the initializations for the game to start
*/
void prepareGame();


/*
	renderGame
	---------------------------------------------------------------------
	Does all the updating and rendering of the game
*/
void renderGame();


/*
	updateTransformGame
	---------------------------------------------------------------------
	Updates the tranformation matrices of all the game objects
*/
void updateTransformGame();


/*
	processKeyboardGame
	---------------------------------------------------------------------
	Does all the processing of keyboard inputs during the game phase
	---------------------------------------------------------------------
	PARAMETERS:
		- window: the window where the keyboard is considered
*/
void processKeyboardGame(GLFWwindow* window);


/*
	processMouseGame
	---------------------------------------------------------------------
	Does all the processing of the mouse position during the game phase
	---------------------------------------------------------------------
	PARAMETERS:
		- window: the window where the mouse is
		- xposIn: the x coordinate of the mouse
		- yposIn: the y coordinate of the mouse
*/
void processMouseGame(GLFWwindow* window, double xposIn, double yposIn);

int getScore();

void powerupIsPresent();
#endif
