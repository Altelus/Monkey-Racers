#ifndef _UTILITIES_H
#define _UTILITIES_H

#include "Vec3.h"
#include "BMath/mat.h"

#define EPSILON 0.000001

GLuint loadTexture(const char* filename, bool clamp = false);
bool detectColiding(Object* obj1, Object* obj2);
bool detectColidingY(Object* obj1, Object* obj2);
Path loadPaths(const char* filename);

bmath::vec::vec3 toBMathVec3f (Vec3 v);
Vec3 toVec3f (bmath::vec::vec3 v);

bool rayTriangleIntersection( Vec3 v1, Vec3 v2, Vec3 v3, Vec3 origin, Vec3 direction);

float Random( float min, float max );
#endif