/*
	CB Mini GLSL Shader
	By Dan Buckstein... and YOU!

	Utility that loads and appropriately sets up GLSL shaders and programs.
*/

#ifndef __CBMINI_FW_GLSLSHADER_H
#define __CBMINI_FW_GLSLSHADER_H


namespace cbmini
{
namespace cbfw
{


enum ShaderType
{
	GLSL_VERTEX_SHADER, 
	GLSL_FRAGMENT_SHADER, 
	GLSL_GEOMETRY_SHADER
	// others
};


// shader class
class GLSLShader
{
private: 

	// type from enumerator above
	ShaderType type;

	// handle in OpenGL
	unsigned int handle;

public: 

	// getters
	inline ShaderType GetType() const
	{
		return type;
	}

	inline unsigned int GetHandle() const
	{
		return handle;
	}

public: 

	// default ctor
	GLSLShader();

	// dtor
	~GLSLShader();

	// release shader from graphics memory
	void Release();

	// create a shader either by loading a file or 
	//	providing direct source
	// returns 0 if failure, returns new handle if success
	int CreateFromSource(ShaderType newType, const char *source);
	int CreateFromFile(ShaderType newType, const char *filePath);

};


// program class
class GLSLProgram
{
private: 

	// handle in OpenGL
	unsigned int handle;

public: 

	// getters
	inline unsigned int GetHandle() const
	{
		return handle;
	}

public: 

	// default ctor
	GLSLProgram();

	// dtor
	~GLSLProgram();

	// release program from graphics memory
	void Release();

	// attach an existing shader
	// returns 0 if not attached, 1 if attached
	int AttachShader(const GLSLShader *shader);

	// link the shader
	// ultimately this is the finalization
	// returns 0 if failure, returns 1 if success
	int LinkProgram();

	// make sure everything's okay
	int ValidateProgram();

	// activate this program for use in your application
	// to simply use another program, call this from the other instance
	void Activate() const;

	// deactivate all programs
	static void Deactivate();

	// get the location of a uniform
	// returns -1 if the uniform was not found or is not in use
	// returns 0 or higher if location is found
	int GetUniformLocation(const char *uniformName);

	// should have function to send individual uniforms
	// this operates on the currently active program!
	// DO THIS YOURSELF AS NECESSARY, but here's a few examples: 
	static void UniformFloat(int location, const float value);
//	static void UniformMat4(int location, bool transpose, const bmath::mat::mat4 value);
//	static void UniformVec3List(int location, unsigned int numValues, const bmath::vec::vec3 *valueList);

};


}
}


#endif	// __CBMINI_FW_GLSLSHADER_H