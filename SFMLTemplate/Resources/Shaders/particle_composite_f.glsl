#version 330 core

in vec2 passTexcoord;

uniform sampler2D sceneImg;
uniform sampler2D partImg;
uniform sampler2D sceneDepth;
uniform sampler2D partDepth;

layout (location=0) out vec4 fragColour;

void main()
{
	fragColour = texture(sceneImg, passTexcoord);
	
	vec4 partDiffuse = texture(partImg, passTexcoord);
	fragColour += partDiffuse;

	//fragColour -= partDiffuse;
	//fragColour.rgb = texture(sceneImg, passTexcoord).rgb;
	//fragColour.rgb = texture(postProcImg, passTexcoord).rgb;
}