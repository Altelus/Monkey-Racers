#include "Engine.h"

bool CompareParticles( Particle p1, Particle p2 )
{
	return (p1.dist2cam > p2.dist2cam);
}

ParticleSystem::ParticleSystem()
{
	initSize = 1.0f;
	running = false;
	initMass = 1.f;
	initLife = 1.f;
	initRespawn = 3.f;
	numDead = 0;

	blendSource = GL_SRC_ALPHA;
	blendDest = GL_ONE_MINUS_SRC_ALPHA;
}

ParticleSystem::~ParticleSystem()
{
	particles.clear();
}

void ParticleSystem::Initialize(GLuint tex, int numParticles, int size, int life, int respawn, Vec3 pos, Vec3 velocity, Vec3 force)
{
	texture = tex;
	initSize = size;
	initLife = life;
	initRespawn = respawn;
	initPos = pos;
	initVelocity = velocity;
	initForce = force;

	if (!running)
	{
		particles.clear();

		if (numParticles)
		{
			for (unsigned int i = 0; i < numParticles; i++)
			{
				Particle part;
				part.pos = initPos;
				part.scale = initSize;
				part.numlives = initRespawn;
				part.dist2cam = 0;

				particles.push_back(part);
			}
		}
	}
}

void ParticleSystem::Reset()
{
	running = false;

	if (particles.size())
	{
		ResetRespawns();
	}
}

void ParticleSystem::Draw(bmath::mat::mat4 view, bmath::mat::mat4 proj, int mv, int p, int sz)
{
	viewMat = view;
	projectionMat = proj;

	if (particles.size() && running)
	{
		glDepthMask(false);
		glEnable (GL_BLEND);
		glEnable(GL_TEXTURE_2D);

		particles.sort(CompareParticles);
		for (std::list<Particle>::iterator i = particles.begin(); i != particles.end(); i++)
		{
			if (initLife <= 0.0f || i->lifespan > 0.0f)
			{
				glBindTexture(GL_TEXTURE_2D, texture);
				glBlendFunc(blendSource, blendDest);

				updateParticleMatrices(i->pos);
				glUniformMatrix4fv(mv, 1, 0, modelViewMat.m);
				glUniformMatrix4fv(p, 1, 0, projectionMat.m);
				glUniform1f(sz, i->scale);

				glPointSize(10.f);
				glBegin(GL_POINTS);
					glVertex3f(0.0, 0.0, 0.0);
				glEnd();
			}
		}
		glDepthMask(true);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}
}

void ParticleSystem::Update( float dt, Vec3 pos )
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

void ParticleSystem::ResetRespawns()
{
	if (particles.size())
	{
		for (std::list<Particle>::iterator i = particles.begin(); i != particles.end(); i++)
		{
			i->numlives = initRespawn;
		}
	}
}

void ParticleSystem::UpdateParticle( float dt, Particle *particle )
{
	particle->lifespan -= dt;
	particle->pos += particle->velocity * (dt + 0.5f*dt*dt);
	particle->velocity += particle->acceleration * dt;

	particle->dist2cam = (particle->pos - camPos).GetLength();
}

void ParticleSystem::SpawnParticle( Particle *particle )
{
	float randomX = (initVelocity.x * (rand() % 50 - 25)/100);
	float randomY = (initVelocity.y * (rand() % 50 - 25)/100);
	float randomZ = (initVelocity.z * (rand() % 50 - 25)/100);

	particle->pos = initPos;
	particle->velocity = initVelocity + (Vec3(randomX * 10, randomY, randomZ * 10));
	particle->acceleration = initForce * (1.f / initMass);

	particle->lifespan = initLife + ((float)rand() / (float)RAND_MAX);

	if (initRespawn > 0)
		particle->numlives -= 1;
}

void ParticleSystem::updateParticleMatrices(Vec3 pos)
{
	bmath::mat::mat3 r = (
		makeRotationX3(0.0) *
		makeRotationY3(0.0) *
		makeRotationZ3(0.0) *
		makeRotationX3(0.0) *
		makeRotationY3(0.0));

	const bmath::vec::vec3 t = toBMathVec3f(pos);
	//const float s = particle->scale;
	const float s = 1;
	modelMat = bmath::mat::makeTransform(r, s, t);

	modelViewMat = viewMat * modelMat;
	modelViewProjectionMat = projectionMat * modelViewMat;
	worldToObject = bmath::mat::transformInverseUniformScale(modelMat);
}

bool ParticleSystem::IsSystemAlive()
{
	int size = particles.size();

	bool result = (numDead == size);
	return !(numDead == particles.size());
}
