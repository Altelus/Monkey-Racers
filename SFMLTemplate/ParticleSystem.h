#ifndef _PARTICLE_SYSTEM_H
#define _PARTICLE_SYSTEM_H

#include "Particle.h"
#include "Vec3.h"
#include "BMath\mat.h"

bool CompareParticles( Particle p1, Particle p2 );

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void Initialize(GLuint tex, int numParticles, int size, int life, int respawn, Vec3 pos, Vec3 velocity, Vec3 force);
	inline void Start()	{running = true;}
	inline void Stop()	{running = false;}
	void Reset();
	void Draw(bmath::mat::mat4 view, bmath::mat::mat4 proj, int mv, int p, int sz);

	virtual void Update( float dt, Vec3 pos);
	bool IsSystemAlive();
	void ResetRespawns();

	unsigned int blendDest;
	unsigned int blendSource;

	GLuint texture;

	float initSize;
	Vec3 initPos;
	Vec3 initVelocity;
	Vec3 initForce;
	float initMass;
	float initLife;
	float initRespawn;
	bool running;
	bool spriteMode;
	int numDead;

	Vec3 camPos;
	bmath::mat::mat4 modelMat;
	bmath::mat::mat4 modelViewMat;
	bmath::mat::mat4 viewMat;
	bmath::mat::mat4 modelViewProjectionMat;
	bmath::mat::mat4 projectionMat;
	bmath::mat::mat4 worldToObject;

	std::list<Particle> particles;

protected:
	virtual void UpdateParticle(float dt, Particle *particle);
	virtual void SpawnParticle(Particle *particle);
	void updateParticleMatrices(Vec3 pos);
};

#endif