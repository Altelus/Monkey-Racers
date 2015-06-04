#include "Engine.h"

bool CompareParticles( Particle p1, Particle p2 )
{
	return (p1.dist > p2.dist);
}

void DrawParticle( Camera3D* cam, Vec3 pos, float scale )
{
	static Vec3 tempV;

	//glPushMatrix();

	//Translate the particle on the X, Y and Z axis accordingly
	//glTranslatef(pos.x, pos.y, pos.z);

	//Draw Particle 
	//**too much math, shaders are faster
	glBegin(GL_QUADS);
	tempV = cam->strafe*-scale - cam->up*scale;
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(tempV.x, tempV.y, tempV.z);

	tempV = cam->strafe*scale - cam->up*scale;
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(tempV.x, tempV.y, tempV.z);

	tempV = cam->strafe*scale + cam->up*scale;
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(tempV.x, tempV.y, tempV.z);

	tempV = cam->strafe*-scale + cam->up*scale;
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(tempV.x, tempV.y, tempV.z);
	glEnd();

	//End the changes to the current object
	//glPopMatrix();
}

float Random( float min, float max )
{
	return (float(rand()%3001)/3000.0f) * (max-min) + min;
}

ParticleEngine::ParticleEngine(Camera3D* camera)
{
	cam = camera;
}

void ParticleEngine::addParticle(const GLuint texture, const float x, const float y, const float z)
{
	Particle part;
	part.blendDest = GL_ONE;
	part.blendSource = GL_SRC_ALPHA;
	part.scale = 5.f;
	part.texture = texture;

	part.pos.x = x;
	part.pos.y = y;
	part.pos.z = z;

	//part.col =  Vec3(1.f,0.f,0.f);
	part.col =  (part.col.Random()*0.5f) + Vec3(0.5f,0.5f, 0.5f);
	part.dist = (part.pos - cam->pos).GetLength();

	particles.push_back (part);
}

void ParticleEngine::generateRandom(const GLuint texture, const float x, const float y, const float z)
{
	Particle part;
	part.blendDest = GL_ONE;
	part.blendSource = GL_SRC_ALPHA;
	part.scale = 100.f;
	part.texture = texture;

	for (int i = 0; i < 50; i++)
	{
		part.pos.x = Random(x-500, x+500);
		part.pos.y = Random(y-500, y+500);
		part.pos.z = Random(z+500, z-500);

		part.col = (part.col.Random()*0.5f) + Vec3(0.5f,0.5f, 0.5f);
		part.dist = (part.pos - cam->pos).GetLength();

		particles.push_back (part);
	}
}

void ParticleEngine::draw(bmath::mat::mat4 view, bmath::mat::mat4 proj, int idx)
{
	viewMat = view;
	projectionMat = proj;

	//Disable Depth Testing
	//**prevent overlapping (eg. particles)
	glDepthMask(false);
	//**prevent see-through (eg. hill to particles)
	//glDisable(GL_DEPTH_TEST);

	//Enable blending
	glEnable (GL_BLEND);

	//Render the particle
	glEnable(GL_TEXTURE_2D);

	particles.sort(CompareParticles);
	for (std::list<Particle>::iterator i = particles.begin(); i != particles.end(); i++)
	{
		i->dist = (i->pos - cam->pos).GetLength();
		glColor3f(i->col.x, i->col.y, i->col.z);

		glBindTexture(GL_TEXTURE_2D, i->texture);
		glBlendFunc(i->blendSource, i->blendDest);
		updateParticleMatrices(i->pos);
		glUniformMatrix4fv(idx, 1, 0, modelViewProjectionMat.m);
		DrawParticle(cam, i->pos, i->scale);
	}

	//Re-enable Depth Testing
	glDepthMask(true);
	//glEnable(GL_DEPTH_TEST);

	//glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void ParticleEngine::clear()
{
	particles.clear();
}

void ParticleEngine::updateParticleMatrices(Vec3 pos)
{
	bmath::mat::mat3 r = (
		makeRotationX3(0.0) *
		makeRotationY3(0.0) *
		makeRotationZ3(0.0) *
		makeRotationX3(0.0) *
		makeRotationY3(0.0));

	const bmath::vec::vec3 t = toBMathVec3f(pos);
	const float s = 1;
	modelMat = bmath::mat::makeTransform(r, s, t);

	// compute model-view matrix
	modelViewMat = viewMat * modelMat;

	// compute model-view-projection matrix
	modelViewProjectionMat = projectionMat * modelViewMat;

	// compute object-space matrix
	worldToObject = bmath::mat::transformInverseUniformScale(modelMat);
}

