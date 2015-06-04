#include "VertexBuffer.h"
using namespace cbmini;
using namespace cbfw;


#include "GL/glew.h"


//-----------------------------------------------------------------------------
// vertex buffer object class

// ctor and dtor (done)
VertexBuffer::VertexBuffer()
{
	vertexHandle = 0;
	normalHandle = 0;
	texcoordHandle = 0;

	vaoHandle = 0;

	numVertices = 0;
}

VertexBuffer::~VertexBuffer()
{
	// auto-release
	Release();
}


// release
// IMPLEMENT!
// ******** 
void VertexBuffer::Release()
{
	if (vaoHandle)
	{
		// delete VAO
		// **** 
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vaoHandle);

		// delete buffers
		// **** 
		glDeleteBuffers(1, &vertexHandle);

		if (normalHandle)
			glDeleteBuffers(1, &normalHandle);

		if (texcoordHandle)
			glDeleteBuffers(1, &texcoordHandle);

		// reset handles
		vertexHandle = 0;
		normalHandle = 0;
		texcoordHandle = 0;
		vaoHandle = 0;
		numVertices = 0;
	}
}


// initialization
// IMPLEMENT!
// ******** 
int VertexBuffer::Initialize(unsigned int numVerts, bool useNormals, bool useTexcoords)
{
	if (!vaoHandle)
	{
		// set number of renderable vertices
		numVertices = numVerts;

		// generate vertex array object (states)
		// **** 
		glGenVertexArrays(1, &vaoHandle);
		glBindVertexArray(vaoHandle);

		// generate empty buffer for each attribute
		// **** 
		glGenBuffers(1, &vertexHandle);
		glBindBuffer(GL_ARRAY_BUFFER, vertexHandle);

		const unsigned int vertexBufferSize = numVertices * sizeof(float) * 3;
		//    called once per buffer, allocates space, 
		glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, 0, GL_STATIC_DRAW);
		//    turn on one of the 16 attribute slots,  case 0 = vertex, 2 = normal, 8 = texcoord
		glEnableVertexAttribArray(0);
		//    normalized: as passed in to false
		//    stride: distance from elements in buffer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		if (useNormals)
		{
			glGenBuffers(1, &normalHandle);
			glBindBuffer(GL_ARRAY_BUFFER, normalHandle);

			const unsigned int normalBufferSize = vertexBufferSize;
			glBufferData(GL_ARRAY_BUFFER, normalBufferSize, 0, GL_STATIC_DRAW);

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}
		if (useTexcoords)
		{
			glGenBuffers(1, &texcoordHandle);
			glBindBuffer(GL_ARRAY_BUFFER, texcoordHandle);

			const unsigned int texcoordBufferSize = numVertices * sizeof(float) * 2;
			glBufferData(GL_ARRAY_BUFFER, texcoordBufferSize, 0, GL_STATIC_DRAW);

			glEnableVertexAttribArray(8);
			glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}

		// unbind VAO and VBO
		// **** 
		//    turn off states (VAO) first
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// done
		return 1;
	}
	return 0;
}


// add raw attribute data
// IMPLEMENT!
// ******** 
int VertexBuffer::AddVertices(const float *rawVertices)
{
	// make sure handle has been initialized and there is valid data
	if (vertexHandle && rawVertices)
	{
		// fill buffer with appropriately sized data
		// **** 
		const unsigned int bufferSize = numVertices * sizeof(float) * 3;
		glBindBuffer(GL_ARRAY_BUFFER, vertexHandle);
		//glBufferData allocates, glBufferSubData assigns data
		glBufferSubData(GL_ARRAY_BUFFER, 0, bufferSize, rawVertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		return 1;
	}
	return 0;
}

int VertexBuffer::AddNormals(const float *rawNormals)
{
	if (normalHandle && rawNormals)
	{
		//might be good to make sure vao not active
		const unsigned int bufferSize = numVertices * sizeof(float) * 3;
		glBindBuffer(GL_ARRAY_BUFFER, normalHandle);
		glBufferSubData(GL_ARRAY_BUFFER, 0, bufferSize, rawNormals);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return 1;
	}
	return 0;
}

int VertexBuffer::AddTexcoords(const float *rawTexcoords)
{
	if (texcoordHandle && rawTexcoords)
	{
		const unsigned int bufferSize = numVertices * sizeof(float) * 2;
		glBindBuffer(GL_ARRAY_BUFFER, texcoordHandle);
		glBufferSubData(GL_ARRAY_BUFFER, 0, bufferSize, rawTexcoords);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return 1;
	}
	return 0;
}


// activation and deactivation (done)
void VertexBuffer::Activate() const
{
	glBindVertexArray(vaoHandle);
}

void VertexBuffer::Deactivate()
{
	glBindVertexArray(0);
}


// rendering
// IMPLEMENT!
// ******** 
void VertexBuffer::Render() const
{
	if (vaoHandle)
	{
		// non-indexed draw call
		// **** 
		glDrawArrays(GL_TRIANGLES, 0, numVertices);
	}
}

// activate and render combo (done)
void VertexBuffer::ActivateAndRender() const
{
	Activate();
	Render();
}
