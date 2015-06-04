#include "Engine.h"
#include <exception>

Model::Model()
{
	isLoaded = false;

	scale = Vec3 (1,1,1);
	originOffsetPos = Vec3 (0,0,0);

	forward = Vec3 (0,0,-1);
	strafe = Vec3 (1,0,0);
	up = Vec3 (0,1,0);

	azemuth = elevation = 0;

	vbo = new cbmini::cbfw::VertexBuffer;

	SetModelType(MODEL_TYPE_VTN);
}

Model::Model(const char* filename, const int type, bool compCollision)
{
	isLoaded = false;

	scale = Vec3 (1,1,1);
	originOffsetPos = Vec3 (0,0,0);

	forward = Vec3 (0,0,-1);
	strafe = Vec3 (1,0,0);
	up = Vec3 (0,1,0);

	azemuth = elevation = 0;

	vbo = new cbmini::cbfw::VertexBuffer;

	SetModelType(type);
	loadObj(filename);

	if (compCollision)
		generateBoundingBox();
}

void Model::SetModelType(int type)
{
	if (0 <= type && type <= MODEL_TYPE_VTN)
		modelType = type;
}

bool Model::loadObj(const char* filename)
{
	float tempSize = 3;
	bool result = false;

	float vertA, uvA, normA, vertB, uvB, normB, vertC, uvC, normC;
	vertA = uvA = normA = vertB = uvB = normB = vertC = uvC = normC = 0;

	float x, y, z, u, v, a, b, c;

	char line[255];
	char header[3];

	FILE* file = fopen(filename, "r");
	if (file == nullptr)
		return false;
	try
	{
		while (!feof(file))
		{
			readLine(file, line);

			sscanf (line, "%s", &header);
			if (strcmp(header, "v") == 0)
			{
				sscanf(line, "%*s %f %f %f", &x, &y, &z);
				tempVertices.push_back(x);
				tempVertices.push_back(y);
				tempVertices.push_back(z);
			}
			else if (strcmp(header, "vt") == 0)
			{
				sscanf(line, "%*s %f %f", &u, &v);
				tempUVs.push_back(u);
				tempUVs.push_back(v);
			}
			else if (strcmp(header, "vn") == 0)
			{
				sscanf(line, "%*s %f %f %f", &a, &b, &c);
				tempNormals.push_back(a);
				tempNormals.push_back(b);
				tempNormals.push_back(c);
			}
			else if(strcmp(header, "f") == 0)
			{
				if (modelType == MODEL_TYPE_V)
				{
					sscanf(line, "%*s %f %f %f", &vertA, &vertB, &vertC);
				}
				else if (modelType == MODEL_TYPE_VT)
				{
					sscanf(line, "%*s %f/%f %f/%f %f/%f", &vertA, &uvA, &vertB, &uvB, &vertC, &uvC);
				}
				else if (modelType == MODEL_TYPE_VTN)
				{
					sscanf(line, "%*s %f/%f/%f %f/%f/%f %f/%f/%f", &vertA, &uvA, &normA, &vertB, &uvB, &normB, &vertC, &uvC, &normC);
				}
				tempIndices.push_back(vertA);
				tempIndices.push_back(uvA);
				tempIndices.push_back(normA);
				tempIndices.push_back(vertB);
				tempIndices.push_back(uvB);
				tempIndices.push_back(normB);
				tempIndices.push_back(vertC);
				tempIndices.push_back(uvC);
				tempIndices.push_back(normC);
			}
		}
		fclose(file);

		setupVAO();
		setupVBO();

		isLoaded = result = true;
	}
	catch(...)
	{
		tempVertices.clear();
		tempUVs.clear();
		tempNormals.clear();
		tempIndices.clear();

		vertices.clear();
		uvs.clear();
		normals.clear();
	}

	return result;
}

void Model::draw()
{
	if (isLoaded)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glEnable(GL_RESCALE_NORMAL);

		vbo->ActivateAndRender();

		glDisable(GL_RESCALE_NORMAL);
		glDisable(GL_TEXTURE_2D);
	}
}


void Model::drawNoTextures()
{
	if (isLoaded)
	{
		glEnable(GL_RESCALE_NORMAL);

		vbo->ActivateAndRender();

		glDisable(GL_RESCALE_NORMAL);
	}
}

void Model::drawBoundingBox()
{
	if (isLoaded)
	{
		glPushMatrix();

		glTranslatef(pos.x, pos.y, pos.z);
		glScalef(scale.x, scale.y, scale.z);

		//boundingBox.RotateX(rot.x);
		//boundingBox.RotateY(rot.y);
		//boundingBox.RotateZ(rot.z);

		glRotatef(rot.x, 1, 0, 0);
		glRotatef(rot.y, 0, 1, 0);
		glRotatef(rot.z, 0, 0, 1);
		glRotatef(-elevation, 1.0f, 0.0f, 0.0f);
		glRotatef(-azemuth, 0.0f, 1.0f, 0.0f);

		glEnable(GL_RESCALE_NORMAL);
		glBegin(GL_QUADS);
		glVertex3f(-boundingBox.x, -boundingBox.y, boundingBox.z);
		glVertex3f(-boundingBox.x, boundingBox.y, boundingBox.z);
		glVertex3f(boundingBox.x, boundingBox.y, boundingBox.z);
		glVertex3f(boundingBox.x, -boundingBox.y, boundingBox.z);

		glVertex3f(boundingBox.x, -boundingBox.y, -boundingBox.z);
		glVertex3f(boundingBox.x, boundingBox.y, -boundingBox.z);
		glVertex3f(-boundingBox.x, boundingBox.y, -boundingBox.z);
		glVertex3f(-boundingBox.x, -boundingBox.y, -boundingBox.z);

		glVertex3f(-boundingBox.x, boundingBox.y, boundingBox.z);
		glVertex3f(-boundingBox.x, -boundingBox.y, boundingBox.z);
		glVertex3f(-boundingBox.x, -boundingBox.y, -boundingBox.z);
		glVertex3f(-boundingBox.x, boundingBox.y, -boundingBox.z);

		glVertex3f(boundingBox.x, -boundingBox.y, boundingBox.z);
		glVertex3f(boundingBox.x, boundingBox.y, boundingBox.z);
		glVertex3f(boundingBox.x, boundingBox.y, -boundingBox.z);
		glVertex3f(boundingBox.x, -boundingBox.y, -boundingBox.z);

		glVertex3f(-boundingBox.x, -boundingBox.y, -boundingBox.z);
		glVertex3f(-boundingBox.x, -boundingBox.y, boundingBox.z);
		glVertex3f(boundingBox.x, -boundingBox.y, boundingBox.z);
		glVertex3f(boundingBox.x, -boundingBox.y, -boundingBox.z);

		glVertex3f(-boundingBox.x, boundingBox.y, -boundingBox.z);
		glVertex3f(boundingBox.x, boundingBox.y, -boundingBox.z);
		glVertex3f(boundingBox.x, boundingBox.y, boundingBox.z);
		glVertex3f(-boundingBox.x, boundingBox.y, boundingBox.z);

		glEnd();
		glDisable(GL_RESCALE_NORMAL);

		glPopMatrix();
	}
}

void Model::readLine(FILE * fp, char * string)
{
	do
	{
		fgets(string, 255, fp);

	} while (string[0] == '\n');
	return;
}

Model::~Model()
{
	tempVertices.clear();
	tempUVs.clear();
	tempNormals.clear();
	tempIndices.clear();

	vertices.clear();
	uvs.clear();
	normals.clear();
	vbo->Release();
	delete vbo;
}

bool Model::generateBoundingBox()
{
	bool result = false;
	if (isLoaded)
	{
		float minX, maxX; 
		float minY, maxY;
		float minZ, maxZ; 

		minX = maxX = tempVertices[0];
		minY = maxY = tempVertices[1];
		minZ = maxZ = tempVertices[2];

		for(unsigned int i = 0; i < tempVertices.size(); i+=3)
		{
			if (tempVertices[i] < minX)
				minX = tempVertices[i];
			else if (tempVertices[i] > maxX)
				maxX = tempVertices[i];

			if (tempVertices[i+1] < minY)
				minY = tempVertices[i+1];
			else if (tempVertices[i+1] > maxY)
				maxY = tempVertices[i+1];

			if (tempVertices[i+2] < minZ)
				minZ = tempVertices[i+2];
			else if (tempVertices[i+2] > maxZ)
				maxZ = tempVertices[i+2];
		}

		// create bounding box based on min/max values of each axis
		boundingBox.x = ((maxX - minX) / 2)*scale.x;
		boundingBox.y = ((maxY - minY) / 2)*scale.y;
		boundingBox.z = ((maxZ - minZ) / 2)*scale.z;

		// calculate offset of object from origin 0,0,0 (for objs not in the center)
		originOffsetPos.x = minX + boundingBox.x;
		originOffsetPos.y = minY + boundingBox.y;
		originOffsetPos.z = minZ + boundingBox.z;

		result = true;
	}

	return result;
}

// lerp from cur model to target
Model* Model::morph( Model* target, float dt)
{
	Model* result;

	if (tempVertices.size() == target->tempVertices.size())
	{
		result = new Model();
		result->isLoaded = true;
		result->copyAllAttributes(target);

		for (unsigned int i = 0; i < tempVertices.size(); i++)
		{
			result->tempVertices.push_back(LERP(tempVertices[i], target->tempVertices[i], dt));
		}

		result->tempUVs = tempUVs;
		result->tempNormals = tempNormals;
		result->tempIndices = tempIndices;

		result->setupVAO();
		result->setupVBO();
	}

	return result;
}

void Model::copyAllAttributes( Model* target )
{
	texture = target->texture;

	boundingBox = target->boundingBox;
	pos = target->pos;
	rot = target->rot;
	scale = target->scale;

	forward = target->forward;
	up = target->up;
	strafe = target->strafe;

	azemuth = target->azemuth;
	elevation = target->elevation;

	originOffsetPos = target->originOffsetPos;
}

void Model::setupVAO()
{
	vertices.clear();
	uvs.clear();
	normals.clear();

	for (unsigned int i = 0; i < tempIndices.size(); i+=3)
	{
		vertices.push_back(tempVertices[((tempIndices[i]-1)*3)]);
		vertices.push_back(tempVertices[((tempIndices[i]-1)*3)+1]);
		vertices.push_back(tempVertices[((tempIndices[i]-1)*3)+2]);

		uvs.push_back(tempUVs[((tempIndices[i+1]-1)*2)]);
		uvs.push_back(-tempUVs[((tempIndices[i+1]-1)*2)+1]);

		normals.push_back(tempNormals[((tempIndices[i+2]-1)*3)]);
		normals.push_back(tempNormals[((tempIndices[i+2]-1)*3)+1]);
		normals.push_back(tempNormals[((tempIndices[i+2]-1)*3)+2]);
	}
}

void Model::setupVBO()
{
	vbo->Initialize(vertices.size()/3, true, true);
	vbo->AddVertices(&vertices[0]);
	vbo->AddNormals(&normals[0]);
	vbo->AddTexcoords(&uvs[0]);
}

