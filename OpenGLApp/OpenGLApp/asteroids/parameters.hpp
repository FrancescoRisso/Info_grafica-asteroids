#ifndef _PARAMETERS_H
#define _PARAMETERS_H


/*	---------------------------------------------------------------------
	Sizes of items
-----------------------------------------------------------------------*/

#define radius_smallAsteroid 0.05
#define radius_mediumAsteroid 0.1
#define radius_largeAsteroid 0.2
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
	Mass of the medium and big asteroid, where 1 is the mass of the small
	asteroid
-----------------------------------------------------------------------*/

#define mass_mediumAsteroid 2
#define mass_largeAsteroid 4  // MUST be greater than the medium


/*	---------------------------------------------------------------------
	Randomness parameters
-----------------------------------------------------------------------*/

// A freshly spawned asteroid's speed points to the center of the screen
// plus or minus a random value <= asteroidAngleRandomness (in deg)
#define asteroidAngleRandomness 30

// the chance of spawining an asteroid at every tick is 1/weightOfSpawningAsteroid
#define weightOfSpawningAsteroid 2500

// the weights of an asteroid to be small, medium or large
// chance is weight / (sum of the three weights)
#define weight_smallAsteroid 1
#define weight_mediumAsteroid 1
#define weight_largeAsteroid 1

// the percentage of momentum that is transferred from an asteroid to its
// children
#define conservedMomentum_Asteroid 0.65f


/*	---------------------------------------------------------------------
	Number of scene items
-----------------------------------------------------------------------*/

#define numStars 200

#endif
