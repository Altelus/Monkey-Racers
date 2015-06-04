#ifndef _OBJECT_H
#define _OBJECT_H

#include "Vec3.h"
#include "Include/SFML/OpenGL.hpp"

class Object
{
public:
	virtual void update();
	virtual void draw() = 0;

	Vec3 pos;
	Vec3 scale;

	//temp
	Vec3 originOffsetPos;
	Vec3 rot;
	Vec3 boundingBox;

	Vec3 forward;
	Vec3 strafe;
	Vec3 up;

	float azemuth;
	float elevation;

	GLuint texture;
};

#endif