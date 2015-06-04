#include "Engine.h"

void ParticleEruption::Update( float dt, Vec3 pos )
{
	camPos = pos;

	numDead = 0;
	if (particles.size() && running)
	{
		for (std::list<Particle>::iterator i = particles.begin(); i != particles.end(); i++)
		{
			if (initLife <= 0.0 || i->lifespan > 0.0f)
				UpdateParticle(dt, &*i);
			else if (initRespawn <= 0.0f || i->numlives > 0)
				SpawnParticle(&*i);
			else
			{
				numDead++;
			}
		}
	}
}

void ParticleEruption::UpdateParticle(float dt, Particle *particle)
{
	particle->lifespan -= dt;
	particle->pos += particle->velocity * (dt + 0.5f*dt*dt);
	particle->velocity += particle->acceleration * dt;

	particle->dist2cam = (particle->pos - camPos).GetLength();
}

void ParticleEruption::SpawnParticle(Particle *particle)
{
	float randomX = (5.f * (rand() % 50 - 25)/100);
	float randomY = (initVelocity.y * (rand() % 50 - 25)/100);
	float randomZ = (5.f * (rand() % 50 - 25)/100);

	particle->pos = initPos;
	particle->velocity = initVelocity + (Vec3(randomX * 10, randomY, randomZ * 10));
	particle->acceleration = initForce * (1.f / initMass);

	particle->lifespan = initLife + ((float)rand() / (float)RAND_MAX);

	if (initRespawn > 0)
		particle->numlives -= 1;
}