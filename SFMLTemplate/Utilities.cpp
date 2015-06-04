#include "Engine.h"

GLuint loadTexture( const char* filename, bool clamp)
{
	GLuint texture = 0;

	sf::Image texImg;
	if(texImg.loadFromFile(filename))
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, texImg.getSize().x, texImg.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, texImg.getPixelsPtr());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		
		if (clamp)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		}
	}

	return texture;
}


bool detectColiding(Object* obj1, Object* obj2)
{
	// check for distance between the two on X axis
	float distanceX = abs((obj1->pos.x + obj1->originOffsetPos.x) 
					      - (obj2->pos.x + obj2->originOffsetPos.x));

	if (distanceX > obj1->boundingBox.x + obj2->boundingBox.x)
	{
		return false;
	}

	// check for distance between the two on X axis
	float distanceZ = abs((obj1->pos.z + obj1->originOffsetPos.z) 
						  - (obj2->pos.z + obj2->originOffsetPos.z));

	if (distanceZ > obj1->boundingBox.z + obj2->boundingBox.z)
	{
		return false;
	}

	return true;
}

bool detectColidingY(Object* obj1, Object* obj2)
{
	// check for distance between the two on Y axis
	float distanceY = abs((obj1->pos.y + obj1->originOffsetPos.y) 
						  - (obj2->pos.y + obj2->originOffsetPos.y));

	if (distanceY > obj1->scale.y + obj2->scale.y)
	{
		return false;
	}

	return true;
}

Path loadPaths(const char* filename)
{
	Path path;
	float x, y, z;

	int curSegment = 0;
	//char header[1];
	char line[255];

	FILE* file = fopen(filename, "r");
	if (file == nullptr)
		return path;

	while (!feof(file))
	{
		//read line
		do
		{
			fgets(line, 255, file);

		} while (line[0] == '\n');

		sscanf(line, "%f %f %f", &x, &y, &z);

		path.AddWaypointToEnd(Vec3(x, y, z));
	}
	fclose(file);

	return path;
}

bmath::vec::vec3 toBMathVec3f (Vec3 v)
{
	return bmath::vec::vec3(v.x, v.y, v.z);
}

Vec3 toVec3f (bmath::vec::vec3 v)
{
	return Vec3(v.x, v.y, v.z);
}

// Moller-Trumbore intersection algorimth implemented
//based off of http://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
bool rayTriangleIntersection( Vec3 v1, Vec3 v2, Vec3 v3, Vec3 origin, Vec3 direction )
{
	Vec3 edge1, edge2;
	Vec3 P, Q, T;

	float det, inv_det, u, v;
	float t;

	edge1 = v2-v1;
	edge2 = v3-v1;

	P = direction.Cross(edge2);
	det = edge1.Dot(P);
	if (det > -EPSILON && det < EPSILON)
		return 0;
		
	inv_det = 1.0f/det;

	T = origin - v1;
	u = T.Dot(P) * inv_det;
	if (u < 0.0 || u > 1.0)
		return 0;

	Q = T.Cross(edge1);
	v = direction.Dot(Q) * inv_det;
	if (v < 0.0 || u + v > 1.0)
		return 0;

	t = edge2.Dot(Q) * inv_det;
	if (t > EPSILON)
		return 1;

	return 0;
}

float Random( float min, float max )
{
	return (float(rand()%3001)/3000.0f) * (max-min) + min;
}