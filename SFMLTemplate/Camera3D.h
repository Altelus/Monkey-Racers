#ifndef _CAMERA3D_
#define _CAMERA3D_

#include "Vec3.h"

class Camera3D
{
public:
	Camera3D(sf::Window* window);
	void Activate();

	Vec3 pos;
	Vec3 forward;
	Vec3 strafe;
	Vec3 up;
	float azemuth;
	float elevation;

	sf::Window* window;
};

#endif