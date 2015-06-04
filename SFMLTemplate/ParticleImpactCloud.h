#ifndef _PARTICLE_IMPACT_CLOUD_
#define _PARTICLE_IMPACT_CLOUD_

#include "ParticleSystem.h"

class ParticleImpactCloud : public ParticleSystem
{
public:
	virtual void Update (float dt, Vec3 pos);
protected:
	virtual void UpdateParticle(float dt, Particle *particle);
	virtual void SpawnParticle(Particle *particle);
};

#endif