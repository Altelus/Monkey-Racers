#ifndef _PARTICLE_ASH_
#define _PARTICLE_ASH_

#include "ParticleSystem.h"

class ParticleAsh : public ParticleSystem
{
public:
	virtual void Update (float dt, Vec3 pos);
protected:
	virtual void UpdateParticle(float dt, Particle *particle);
	virtual void SpawnParticle(Particle *particle);
};

#endif