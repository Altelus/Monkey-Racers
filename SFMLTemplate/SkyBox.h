#ifndef _SKYBOX_H
#define _SKYBOX_H

class SkyBox : public Object
{
public:
	SkyBox();
	SkyBox(float size);
	
	void loadTextures( const char* top, const char* down, const char* left, const char* right, const char* front, const char* back );
	virtual void draw();

private:
	void setup(float size);

	GLuint texUp;
	GLuint texDown;
	GLuint texLeft;
	GLuint texRight;
	GLuint texFront;
	GLuint texBack;

	std::vector<float> skyVerts;
	std::vector<float> skyCoords;
	std::vector<unsigned int> skyIndex;
};

#endif