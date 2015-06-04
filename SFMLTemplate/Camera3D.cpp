#include "Engine.h"

Camera3D::Camera3D(sf::Window* window)
{
	this->window = window;

	//Set some default values
	azemuth   = 0.0f;
	elevation = 0.0f;
}

void Camera3D::Activate()
{
	////Setup a perspective projection
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	////TODO: remove hard coded values
	//gluPerspective(
	//	FOV_DEGREE, //Field of view
	//	float(window->getSize().x) / float(window->getSize().y),  //Aspect ratio
	//	FOV_NEAR,  //Near clipping plane
	//	FOV_FAR); //Far clipping plane

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//azemuth   = 0.0f;
	//elevation = 0.0f;

	//Rotate and place the camera in the scene
	//Convert angle to vector
	forward.PolarToVector(azemuth, elevation, 1.0f);
	strafe.PolarToVector(azemuth+90.0f, 0.0f, 1.0f);
	up = strafe.Cross(forward);

	//Rotate the camera
	//glRotatef(elevation, 1.0f, 0.0f, 0.0f);
	//glRotatef(azemuth, 0.0f, 1.0f, 0.0f);	
	//glTranslatef(-pos.x, -pos.y, -pos.z);

}