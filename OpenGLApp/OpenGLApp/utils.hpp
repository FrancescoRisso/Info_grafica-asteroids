#ifndef __UTILS_H
#define __UTILS_H

#include <glm/glm.hpp>

/*
	UTILS
	---------------------------------------------------------------------
	These are some values and functions that can be useful around the
	project
	---------------------------------------------------------------------
	PARAMETERS (that must be present as variables in another file):
		- SCR_WIDTH: the width of the viewport
		- SCR_HEIGHT: the height of the viewport
*/

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;


#define pi_float 3.14159265358979f


// XaxisVersor: a vector of modulus 1 pointing to the positive X axis direction (right)
#define XaxisVersor glm::vec2(1, 0)


// YaxisVersor: a vector of modulus 1 pointing to the negative Y axis direction (up)
#define YaxisVersor glm::vec2(0, -1)


// root2div2: sqrt(2) / 2
#define root2div2 (float) 0.70710678


/*
	angleBetween
	---------------------------------------------------------------------
	Computes the angle between 3 given points
	---------------------------------------------------------------------
	PARAMETERS:
		- a: the first point
		- b: the second point
		- origin: the origin of the angle
	OUTPUT:
		- the angle a-origin-b, in radians
*/
float angleBetween(glm::vec2 a, glm::vec2 b, glm::vec2 origin);


/*
	angleBetweenVerticalDir
	---------------------------------------------------------------------
	Computes the angle between a point, the origin and the upwards
	direction
	Equivalent to angleBetween(a, YaxisVersor, glm::vec2(0))
	---------------------------------------------------------------------
	PARAMETERS:
		- a: the point
	OUTPUT:
		- the angle a-(0,0)-YaxisVersor, in radians
*/
float angleBetweenVerticalDir(glm::vec2 a);


/*
	mouse2GraphicsCoords
	---------------------------------------------------------------------
	Converts the mouse coordinates: (0 to SCR_WIDTH, 0 to SCR_HEIGHT)
	to OpenGL coordinates: (-1 to 1, -1 to 1)
	---------------------------------------------------------------------
	PARAMETERS:
		- mouseCoords: the coordinates in the mouse format
		- screenSize: the width and height of the viewport
	---------------------------------------------------------------------
	OUTPUT:
		- the mouse coordinates converted to OpenGL format
*/
glm::vec2 mouse2graphicCoords(glm::vec2 mouseCoords, glm::vec2 screenSize);


/*
	scaleVector
	---------------------------------------------------------------------
	Scales a vector according to the viewport, to maintain proportions.
	For example, the point (0.5, 0.5) should be at 45° from the origin,
	no matter what the viewport size is.
	This function will therefore scale the point to something like
	(0.5, 0.5 * SCR_WIDTH / SCR_HEIGHT)
	The resultint point is guaranteed to be an OpenGL valid coordinate
	---------------------------------------------------------------------
	PARAMETERS:
		- vector: the original vector to be scaled
	---------------------------------------------------------------------
	OUTPUT:
		- the re-scaled vector
*/
glm::vec2 scaleVector(glm::vec2 vector);


/*
	scaleVectorReverse
	---------------------------------------------------------------------
	Returns from a viewport-scaled vector to the original one
	---------------------------------------------------------------------
	PARAMETERS:
		- vector: the viewport-scaled vector
	---------------------------------------------------------------------
	OUTPUT:
		- the original vector from the input one
*/
glm::vec2 scaleVectorReverse(glm::vec2 vector);

#endif
