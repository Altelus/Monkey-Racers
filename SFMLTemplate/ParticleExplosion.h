#ifndef _PARTICLE_EXPLOSION_
#define _PARTICLE_EXPLOSION_

#include "ParticleSystem.h"

class ParticleExplosion : public ParticleSystem
{
public:
	virtual void Update (float dt, Vec3 pos);
protected:
	virtual void UpdateParticle(float dt, Particle *particle);
	virtual void SpawnParticle(Particle *particle);
};

#endif