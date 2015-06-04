
#version 330 core

in vec2 passTexcoord;

uniform sampler2D sceneImg;

layout (location=0) out vec4 fragColour;

void main()
{
	fragColour.rgb = texture(sceneImg, passTexcoord).rgb;
}