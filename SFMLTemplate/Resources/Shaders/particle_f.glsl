#version 330 core

layout (location=0) out vec4 fragColour;

in vec2 texCoord;
uniform sampler2D diffuseTex;

void main()
{
	vec4 diffuse = texture(diffuseTex, texCoord);

	fragColour = diffuse;
}