#include "Object.h"
void Object::update()
{
	forward.PolarToVector(azemuth, 0, 1.0f);
	strafe.PolarToVector(azemuth+90.0f, 0.0f, 1.0f);
	up = strafe.Cross(forward);
}

