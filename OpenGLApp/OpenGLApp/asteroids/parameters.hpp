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
#define radius_Heart 0.05f
#define radius_Spacevoid 0.8


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
#define numTriangles_Letter 2
#define numTriangles_Heart 2
#define numTriangles_Spacevoid 2


/*	---------------------------------------------------------------------
	Mass of the medium and big asteroid, where 1 is the mass of the small
	asteroid
-----------------------------------------------------------------------*/

#define mass_mediumAsteroid 2
#define mass_largeAsteroid 4  // MUST be greater than the medium


/*	---------------------------------------------------------------------
	Time between two asteroids spawning. It is determined by two factors:
	- the "base line" is a decreasing exponential based on the current
		score: the further in the game, the faster asteroids spawn
	- a "slow-down" is added at every 10% increase of weight of big
		asteroids: the game already becomes more difficult as more
		asteroids will be in the scene, so the spawn rate decreases
-----------------------------------------------------------------------*/

// the time that should pass from an asteroid spawn to the next
float timeBetweenSpawns();

// the number of "slow-down" steps to be applied at this moment
#define numSteps weight_largeAsteroid() / 10

// the amount of each "slow-down" step
#define stepSize 0.08

// the how fast the score makes the exponential decrease
#define scalingSpeed 1 / 150

// the time at score = 0, which also scales the whole exponential
#define scalingMagnitude 2

/*	---------------------------------------------------------------------
	Randomness parameters
-----------------------------------------------------------------------*/

// A freshly spawned asteroid's speed points to the center of the screen
// plus or minus a random value <= asteroidAngleRandomness (in deg)
#define asteroidAngleRandomness 30

// the weights of an asteroid to be small, medium or large
// chance is weight / (sum of the three weights)
int weight_smallAsteroid();
int weight_mediumAsteroid();
int weight_largeAsteroid();

// the percentage of momentum that is transferred from an asteroid to its
// children
#define conservedMomentum_Asteroid 0.65f


/*	---------------------------------------------------------------------
	Number of scene items
-----------------------------------------------------------------------*/

#define numStars 200


/*	---------------------------------------------------------------------
	Speed of auto-shoot
-----------------------------------------------------------------------*/

#define speed_autoShoot 5  // number of shots per second


/*	---------------------------------------------------------------------
	Lives and death settings
-----------------------------------------------------------------------*/

#define numHearts 3
#define invulnerabilityTime 2.0f
#define blinkOn_time 0.25f
#define blinkOff_time 0.1f


#endif
