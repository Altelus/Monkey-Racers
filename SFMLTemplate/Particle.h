#ifndef _PARTICLE_H
#define _PARTICLE_H

#include "Vec3.h"
struct Particle
{
	Vec3 pos;
	Vec3 velocity;
	Vec3 acceleration;

	float scale;

	float lifespan;
	int numlives;

	float dist2cam;
};

#endif
