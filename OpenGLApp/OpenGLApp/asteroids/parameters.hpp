#ifndef _PARAMETERS_H
#define _PARAMETERS_H


/*	---------------------------------------------------------------------
	Sizes of items
-----------------------------------------------------------------------*/

#define radius_Asteroid 0.1
#define radius_Spaceship 0.1
#define radius_Projectile 0.01


/*	---------------------------------------------------------------------
	Speed of items
-----------------------------------------------------------------------*/

#define speed_Asteroid 0.5f
#define speed_Projectile 1.0f


/*	---------------------------------------------------------------------
	Randomness parameters
-----------------------------------------------------------------------*/

// A freshly spawned asteroid's speed points to the center of the screen
// plus or minus a random value <= asteroidAngleRandomness (in deg)
#define asteroidAngleRandomness 30

// the chance of spawining an asteroid at every tick is 1/weightOfSpawningAsteroid
#define weightOfSpawningAsteroid 5000

#endif
