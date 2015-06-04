#include "Engine.h"

void ParticleAsh::Update( float dt, Vec3 pos )
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

void ParticleAsh::UpdateParticle(float dt, Particle *particle)
{
	particle->lifespan -= dt;
	particle->pos += particle->velocity * (dt + 0.5f*dt*dt);
	particle->velocity += particle->acceleration * dt;

	particle->dist2cam = (particle->pos - camPos).GetLength();
}

void ParticleAsh::SpawnParticle(Particle *particle)
{
	float randomX = (100 * (rand() % 100 - 50)/100);
	float randomY = (initPos.y * (rand() % 100 - 50)/100);
	float randomZ = (100 * (rand() % 100 - 50)/100);

	particle->pos = initPos + Vec3(randomX*10, randomY, randomZ*10);
	particle->velocity = Vec3(randomZ, randomX, randomY);
	particle->acceleration = initForce * (1.f / initMass);

	particle->lifespan = initLife + ((float)rand() / (float)RAND_MAX);

	if (initRespawn > 0)
		particle->numlives -= 1;
}