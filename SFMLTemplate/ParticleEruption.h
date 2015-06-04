#ifndef _PARTICLE_ERUPTION_
#define _PARTICLE_ERUPTION_

#include "ParticleSystem.h"

class ParticleEruption : public ParticleSystem
{
public:
	virtual void Update (float dt, Vec3 pos);
protected:
	virtual void UpdateParticle(float dt, Particle *particle);
	virtual void SpawnParticle(Particle *particle);
};

#endif