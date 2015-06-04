#version 330 core

in vec2 passTexcoord;

uniform sampler2D sceneImg1;
uniform sampler2D sceneImg2;
uniform sampler2D sceneImg3;
uniform sampler2D sceneImg4;

layout (location=0) out vec4 fragColour;

void main()
{
	//fragColour.rgb = vec3(1.0,0.0,0.0);

	vec3 d1 = 0.417*texture(sceneImg1, passTexcoord).rgb;
	vec3 d2 = 0.25*texture(sceneImg2, passTexcoord).rgb;
	vec3 d3 = 0.167*texture(sceneImg3, passTexcoord).rgb;
	vec3 d4 = 0.083*texture(sceneImg4, passTexcoord).rgb;

	fragColour.rgb = d1 + d2 + d3 + d4;
	//fragColour.rgb = d1;
	//fragColour.rgb = d2;
	//fragColour.rgb = d3;
	//fragColour.rgb = d4;

	//fragColour.rgb = (texture(sceneImg, passTexcoord).rgb) +
	//				 (texture(postProcImg, passTexcoord).rgb);

	//fragColour.rgb = texture(sceneImg, passTexcoord).rgb;
	//fragColour.rgb = texture(postProcImg, passTexcoord).rgb;
}