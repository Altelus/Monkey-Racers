#include "GLSLShader.h"
using namespace cbmini;
using namespace cbfw;


#include "Utility.h"


#include <stdio.h>
#include "GL/glew.h"


//-----------------------------------------------------------------------------
// GLSL shader class

// ctor and dtor (done)
GLSLShader::GLSLShader()
{
	handle = 0;
}

GLSLShader::~GLSLShader()
{
	// auto-release
	Release();
}


// release (done)
void GLSLShader::Release()
{
	// if loaded, delete shader handle from graphics memory
	if (handle)
	{
		glDeleteShader(handle);
		handle = 0;
	}
}


// create a shader
// IMPLEMENTATION REQUIRED!
// ******** 
int GLSLShader::CreateFromSource(ShaderType newType, const char *source)
{
	// only create a new shader if this instance has not already loaded something
	if (!handle)
	{
		// make sure source exists
		if (source)
		{
			// map user type input to OpenGL type input
			// **** 
			const GLenum internalType[6] = {
				GL_VERTEX_SHADER,
				GL_FRAGMENT_SHADER,
				GL_GEOMETRY_SHADER
			};

			// create the shader in graphics memory
			// **** 
			type = newType;
			handle = glCreateShader(internalType[type]);
			if (handle)
			{
				int status;

				// the handle was created successfully!
				// attach our source to it
				// **** 
				glShaderSource(handle, 1, &source, 0);
				
				// compile the shader and check status
				// **** 
				glCompileShader(handle);
				glGetShaderiv(handle, GL_COMPILE_STATUS, &status);

				if (status)
				{
					printf("\nSHADER COMPILED\n");
					return handle;
				}

				// if there was an error, we can check and print the debug log
				// pretty neat feature!
				// **** 
				int logLength;
				glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLength);
				if(logLength > 0)
				{
					char* log = Utility::AllocString(logLength+1);
					glGetShaderInfoLog(handle, logLength, &logLength, log);
					printf("\nFAILED TO COMPILE SHADER\n %s", log);
					Utility::FreeString(log);
				}

				// free graphics memory and revert... have we seen this?
				// **** 
				Release();
			}
		}
	}
	return 0;
}

// create from file (done)
int GLSLShader::CreateFromFile(ShaderType newType, const char *filePath)
{
	char *source = Utility::LoadFile(filePath);
	int ret = CreateFromSource(newType, source);
	if (source)
		Utility::FreeString(source);
	return ret;
}



//-----------------------------------------------------------------------------
// GLSL program class

// ctor and dtor (done)
GLSLProgram::GLSLProgram()
{
	handle = 0;
}

GLSLProgram::~GLSLProgram()
{
	// auto-release
	Release();
}


// release (done)
void GLSLProgram::Release()
{
	// same idea as above
	if (handle)
	{
		glDeleteProgram(handle);
		handle = 0;
	}
}


// attachment
// IMPLEMENT!
// ******* 
int GLSLProgram::AttachShader(const GLSLShader *shader)
{
	if (shader)
	{
		// if the handle has not been previously allocated, tell 
		//	OpenGL to give us a new program handle
		// **** 
		if (!handle)
			handle = glCreateProgram();

		// if the handle exists, attach the shader and we're done
		// **** 
		if (handle)
		{
			glAttachShader(this->handle, shader->GetHandle());
			return 1;
		}
	}
	return 0;
}


// linking
// IMPLEMENT!
// ******** 
int GLSLProgram::LinkProgram()
{
	if (handle)
	{
		// link and check status
		// **** 
		int status;
		glLinkProgram(handle);
		glGetProgramiv(handle, GL_LINK_STATUS, &status);
		if (status)
		{
			printf("\nPROGRAM LINKED\n");
			return handle;
		}

		// link failed, check log
		// **** 
		int logLength;
		glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &logLength);
		if(logLength > 0)
		{
			char* log = Utility::AllocString(logLength+1);
			glGetProgramInfoLog(handle, logLength, &logLength, log);
			printf("\nPROGRAM LINKAGE FAILED\n %s", log);
			Utility::FreeString(log);
		}
		// free graphics memory... seen this too
		// **** 
		Release();
	}
	return 0;
}


// validation
// IMPLEMENT!
// ******** 
int GLSLProgram::ValidateProgram()
{
	if (handle)
	{
		// very similar to above, however this is an optional step
		// therefore there is no need to free the handle if it fails
		// **** 
		//glValidateProgram(handle);
	}
	return 0;
}


// activation and deactivation (done)
void GLSLProgram::Activate() const
{
	glUseProgram(handle);
}

void GLSLProgram::Deactivate()
{
	glUseProgram(0);
}


// get uniform
// IMPLEMENT!
// ******** 
int GLSLProgram::GetUniformLocation(const char *uniformName)
{
	// wrap OpenGL's uniform finder function
	// **** 
	return glGetUniformLocation(handle, uniformName);
}


// send uniform
// IMPLEMENT!
// ******** 
void GLSLProgram::UniformFloat(int location, float value)
{
	// OpenGL's uniform send function
	// **** 
	 glUniform1f(location, value);
}
/*
void GLSLProgram::UniformMat4(int location, bool transpose, const bmath::mat::mat4 value)
{
	glUniformMatrix4fv(location, 1, transpose, value.m);
}

void GLSLProgram::UniformVec3List(int location, unsigned int, numValues const bmath::vec::vec3 *valueList)
{
	glUniform3fv(location, numValues, (float*)valueList);
}
*/