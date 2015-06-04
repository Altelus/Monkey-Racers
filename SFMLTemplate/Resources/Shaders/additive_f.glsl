#version 330 core

in vec2 passTexcoord;

uniform sampler2D sceneImg;
uniform sampler2D postProcImg;

layout (location=0) out vec4 fragColour;

void main()
{
	//fragColour.rgb = vec3(1.0,0.0,0.0);
	fragColour.rgb = (texture(sceneImg, passTexcoord).rgb) +
					 (texture(postProcImg, passTexcoord).rgb);

	//fragColour.rgb = texture(sceneImg, passTexcoord).rgb;
	//fragColour.rgb = texture(postProcImg, passTexcoord).rgb;
}