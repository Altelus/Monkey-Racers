#include "Engine.h"

void ParticleImpactCloud::Update( float dt, Vec3 pos )
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
void ParticleImpactCloud::UpdateParticle(float dt, Particle *particle)
{
	particle->lifespan -= dt;
	particle->pos += particle->velocity * (dt + 0.5f*dt*dt);
	particle->velocity += particle->acceleration * dt;

	particle->dist2cam = (particle->pos - camPos).GetLength();
}

void ParticleImpactCloud::SpawnParticle(Particle *particle)
{
	float randomX = (initVelocity.x * (rand() % 50 - 25)/100);
	float randomY = (initVelocity.y * (rand() % 25 - 12)/100);
	float randomZ = (initVelocity.z * (rand() % 50 - 25)/100);

	//float randomXD = rand() % 2 - 1;
	//float randomZD = rand() % 2 - 1;

	particle->pos = initPos+(Vec3(randomX, randomY, randomZ)*0.1);
	particle->velocity = Vec3(randomX, randomY, randomZ);
	particle->acceleration = initForce * (1.f / initMass) -(Vec3(randomX, 0.0, randomZ)*.5);

	particle->lifespan = initLife + ((float)rand() / (float)RAND_MAX);

	if (initRespawn > 0)
		particle->numlives -= 1;
}