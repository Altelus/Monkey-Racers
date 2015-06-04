#version 330 core

layout (location=0) in vec4 position;
layout (location=8) in vec2 texcoord;

out vec2 passTexcoord;

void main()
{
	gl_Position = position;

	passTexcoord = texcoord;
}