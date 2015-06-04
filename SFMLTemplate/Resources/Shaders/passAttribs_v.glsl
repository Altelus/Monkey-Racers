
#version 330 core

layout (location=0) in vec4 position;	// location
layout (location=2) in vec3 normal;		// normal
layout (location=8) in vec2 texcoord;	// texture

uniform mat4 mvp;						// model-view-projection matrix

// We will output data as structure
out vertex
{
	vec3 positionObj;
	vec3 normalObj;
	vec2 texcoordObj;
} data;

void main()
{
	// Copy data to structure
	data.positionObj = position.xyz;
	data.normalObj = normal;
	data.texcoordObj = texcoord;

	// Multiply tranformation matrix with vertex position

	gl_Position = mvp * position;
}