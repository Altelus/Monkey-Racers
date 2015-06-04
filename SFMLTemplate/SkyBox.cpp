#include "Engine.h"

SkyBox::SkyBox()
{
	scale.x = scale.y = scale.z = 1;
	setup(1);
}

SkyBox::SkyBox( float size )
{
	scale.x = scale.y = scale.z = size;
	setup(size);
}

void SkyBox::loadTextures( const char* top, const char* down,
						   const char* left, const char* right,
						   const char* front, const char* back )
{
	texUp = loadTexture(top, true);
	texDown = loadTexture(down, true);
	texLeft = loadTexture(left, true);
	texRight = loadTexture(right, true);
	texFront = loadTexture(front, true);
	texBack = loadTexture(back, true);
}

void SkyBox::setup( float size )
{
	//Up Face
	skyVerts.push_back(-size); // x
	skyVerts.push_back( size); // y
	skyVerts.push_back(-size); // z
	skyCoords.push_back(1.0f); // u
	skyCoords.push_back(0.0f); // v

	skyVerts.push_back( size); // x
	skyVerts.push_back( size); // y
	skyVerts.push_back(-size); // z
	skyCoords.push_back(0.0f); // u
	skyCoords.push_back(0.0f); // v

	skyVerts.push_back( size); // x
	skyVerts.push_back( size); // y
	skyVerts.push_back( size); // z
	skyCoords.push_back(0.0f); // u
	skyCoords.push_back(1.0f); // v

	skyVerts.push_back(-size); // x
	skyVerts.push_back( size); // y
	skyVerts.push_back( size); // z
	skyCoords.push_back(1.0f); // u
	skyCoords.push_back(1.0f); // v

	skyIndex.push_back(0);
	skyIndex.push_back(1);
	skyIndex.push_back(2);

	skyIndex.push_back(0);
	skyIndex.push_back(2);
	skyIndex.push_back(3);

	//Back Face
	skyVerts.push_back(-size); // x
	skyVerts.push_back(-size); // y
	skyVerts.push_back( size); // z
	skyCoords.push_back(1.0f); // u
	skyCoords.push_back(1.0f); // v

	skyVerts.push_back( size); // x
	skyVerts.push_back(-size); // y
	skyVerts.push_back( size); // z
	skyCoords.push_back(0.0f); // u
	skyCoords.push_back(1.0f); // v

	skyVerts.push_back( size); // x
	skyVerts.push_back( size); // y
	skyVerts.push_back( size); // z
	skyCoords.push_back(0.0f); // u
	skyCoords.push_back(0.0f); // v

	skyVerts.push_back(-size); // x
	skyVerts.push_back( size); // y
	skyVerts.push_back( size); // z
	skyCoords.push_back(1.0f); // u
	skyCoords.push_back(0.0f); // v

	skyIndex.push_back(5);
	skyIndex.push_back(4);
	skyIndex.push_back(6);

	skyIndex.push_back(6);
	skyIndex.push_back(4);
	skyIndex.push_back(7);

	//Front Face
	skyVerts.push_back(-size); // x
	skyVerts.push_back(-size); // y
	skyVerts.push_back(-size); // z
	skyCoords.push_back(0.0f); // u
	skyCoords.push_back(1.0f); // v

	skyVerts.push_back( size); // x
	skyVerts.push_back(-size); // y
	skyVerts.push_back(-size); // z
	skyCoords.push_back(1.0f); // u
	skyCoords.push_back(1.0f); // v

	skyVerts.push_back( size); // x
	skyVerts.push_back( size); // y
	skyVerts.push_back(-size); // z
	skyCoords.push_back(1.0f); // u
	skyCoords.push_back(0.0f); // v

	skyVerts.push_back(-size); // x
	skyVerts.push_back( size); // y
	skyVerts.push_back(-size); // z
	skyCoords.push_back(0.0f); // u
	skyCoords.push_back(0.0f); // v

	skyIndex.push_back(8);
	skyIndex.push_back(9);
	skyIndex.push_back(10);

	skyIndex.push_back(8);
	skyIndex.push_back(10);
	skyIndex.push_back(11);	

	//Left Face
	skyVerts.push_back(-size); // x
	skyVerts.push_back(-size); // y
	skyVerts.push_back(-size); // z
	skyCoords.push_back(1.0f); // u
	skyCoords.push_back(1.0f); // v

	skyVerts.push_back(-size); // x
	skyVerts.push_back(-size); // y
	skyVerts.push_back( size); // z
	skyCoords.push_back(0.0f); // u
	skyCoords.push_back(1.0f); // v

	skyVerts.push_back(-size); // x
	skyVerts.push_back( size); // y
	skyVerts.push_back( size); // z
	skyCoords.push_back(0.0f); // u
	skyCoords.push_back(0.0f); // v

	skyVerts.push_back(-size); // x
	skyVerts.push_back( size); // y
	skyVerts.push_back(-size); // z
	skyCoords.push_back(1.0f); // u
	skyCoords.push_back(0.0f); // v

	skyIndex.push_back(13);
	skyIndex.push_back(12);
	skyIndex.push_back(14);

	skyIndex.push_back(14);
	skyIndex.push_back(12);
	skyIndex.push_back(15);

	//Right Face
	skyVerts.push_back( size); // x
	skyVerts.push_back(-size); // y
	skyVerts.push_back(-size); // z
	skyCoords.push_back(0.0f); // u
	skyCoords.push_back(1.0f); // v

	skyVerts.push_back( size); // x
	skyVerts.push_back(-size); // y
	skyVerts.push_back( size); // z
	skyCoords.push_back(1.0f); // u
	skyCoords.push_back(1.0f); // v

	skyVerts.push_back( size); // x
	skyVerts.push_back( size); // y
	skyVerts.push_back( size); // z
	skyCoords.push_back(1.0f); // u
	skyCoords.push_back(0.0f); // v

	skyVerts.push_back( size); // x
	skyVerts.push_back( size); // y
	skyVerts.push_back(-size); // z
	skyCoords.push_back(0.0f); // u
	skyCoords.push_back(0.0f); // v

	skyIndex.push_back(16);
	skyIndex.push_back(17);
	skyIndex.push_back(18);

	skyIndex.push_back(16);
	skyIndex.push_back(18);
	skyIndex.push_back(19);

	//Down Face
	skyVerts.push_back(-size); // x
	skyVerts.push_back(-size); // y
	skyVerts.push_back(-size); // z
	skyCoords.push_back(1.0f); // u
	skyCoords.push_back(1.0f); // v

	skyVerts.push_back( size); // x
	skyVerts.push_back(-size); // y
	skyVerts.push_back(-size); // z
	skyCoords.push_back(0.0f); // v
	skyCoords.push_back(1.0f); // u

	skyVerts.push_back( size); // x
	skyVerts.push_back(-size); // y
	skyVerts.push_back( size); // z
	skyCoords.push_back(0.0f); // u
	skyCoords.push_back(0.0f); // v

	skyVerts.push_back(-size); // x
	skyVerts.push_back(-size); // y
	skyVerts.push_back( size); // z
	skyCoords.push_back(1.0f); // v
	skyCoords.push_back(0.0f); // u

	skyIndex.push_back(22);
	skyIndex.push_back(21);
	skyIndex.push_back(20);

	skyIndex.push_back(23);
	skyIndex.push_back(22);
	skyIndex.push_back(20);
}

void SkyBox::draw()
{
	//glDisable(GL_LIGHTING);
	//glPushMatrix();
	//glTranslatef(pos.x, pos.y, pos.z);

	// Enable position and texture coordinates vertex components
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &skyVerts[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &skyCoords[0]);

	// Disable normal and color vertex components
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glEnable(GL_TEXTURE_2D);

	//Up
	glBindTexture(GL_TEXTURE_2D, texUp);
	glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, &skyIndex[0]);

	//Back
	glBindTexture(GL_TEXTURE_2D, texBack);
	glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, &skyIndex[6]);

	//Front
	glBindTexture(GL_TEXTURE_2D, texFront);
	glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, &skyIndex[12]);

	//Left
	glBindTexture(GL_TEXTURE_2D, texLeft);
	glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, &skyIndex[18]);

	//Right
	glBindTexture(GL_TEXTURE_2D, texRight);
	glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, &skyIndex[24]);

	//Right
	glBindTexture(GL_TEXTURE_2D, texDown);
	glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, &skyIndex[30]);

	glDisable(GL_TEXTURE_2D);

	//glPopMatrix();
	//glEnable(GL_LIGHTING);
}


