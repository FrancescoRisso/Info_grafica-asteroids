#ifndef _MAIN_H
#define _MAIN_H

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <irrKlang.h>
// clang-format on

#include <iostream>
#include <list>
#include "./utils.hpp"
#include "./shader_s.h"
#include "asteroids/spaceship.hpp"
#include "asteroids/projectile.hpp"
#include "asteroids/asteroid.hpp"
#include "asteroids/star.hpp"
#include "asteroids/displayString.hpp"
#include "asteroids/_debugOpts.hpp"
#include "asteroids/heart.hpp"

#include "asteroids/game_logic/game.hpp"
#include "asteroids/game_logic/endScreen.hpp"
#include "asteroids/game_logic/instructions.hpp"
#include "asteroids/game_logic/homePage.hpp"

enum gamePhases { mainMenu, instructions, game, endScreen };

void startMusic();

void stopMusic();


#endif
