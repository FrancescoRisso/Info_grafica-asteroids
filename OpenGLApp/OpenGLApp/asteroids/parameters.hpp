#ifndef _PARAMETERS_H
#define _PARAMETERS_H


/*	---------------------------------------------------------------------
	Sizes of items
-----------------------------------------------------------------------*/

#define radius_Asteroid 0.1
#define radius_Spaceship 0.1
#define radius_Projectile 0.01
#define radius_Star 0.005f


/*	---------------------------------------------------------------------
	Speed of items
-----------------------------------------------------------------------*/

#define speed_Asteroid 0.5f
#define speed_Projectile 1.0f
#define speed_Star 0.005f
#define speed_Spaceship 0.5f


/*	---------------------------------------------------------------------
	Number of triangles per object type
-----------------------------------------------------------------------*/

#define numTriangles_Asteroid 2
#define numTriangles_Spaceship 2
#define numTriangles_Projectile 2
#define numTriangles_Star 2


/*	---------------------------------------------------------------------
	Randomness parameters
-----------------------------------------------------------------------*/

// A freshly spawned asteroid's speed points to the center of the screen
// plus or minus a random value <= asteroidAngleRandomness (in deg)
#define asteroidAngleRandomness 30

// the chance of spawining an asteroid at every tick is 1/weightOfSpawningAsteroid
#define weightOfSpawningAsteroid 250


/*	---------------------------------------------------------------------
	Number of scene items
-----------------------------------------------------------------------*/

#define numStars 200

#endif
