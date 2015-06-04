#ifndef _PARTICLE_ENG_H
#define _PARTICLE_ENG_H

#include "Vec3.h"
#include "Camera3D.h"

struct Particle
{
	Vec3 pos;
	Vec3 col;
	float scale;
	unsigned int blendSource;
	unsigned int blendDest;
	GLint texture;
	float dist;
};

bool CompareParticles(Particle, Particle);
void DrawParticle(Camera3D*, Vec3, float);
float Random(float, float);

class ParticleEngine
{
public:
	ParticleEngine(Camera3D*);

	void addParticle(const GLuint texture, const float x, const float y, const float z);
	void generateRandom(const GLuint, const float, const float, const float);
	void clear();
	void draw(bmath::mat::mat4 view, bmath::mat::mat4 proj, int idx);

	Camera3D* cam;
	std::list<Particle> particles;
private:
	void updateParticleMatrices(Vec3 pos);

	bmath::mat::mat4 modelMat;
	bmath::mat::mat4 modelViewMat;
	bmath::mat::mat4 viewMat;
	bmath::mat::mat4 modelViewProjectionMat;
	bmath::mat::mat4 projectionMat;
	bmath::mat::mat4 worldToObject;
};

#endif