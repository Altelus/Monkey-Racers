#version 330 core

in vec2 passTexcoord;

uniform sampler2D sceneImg;
//uniform float middleGrey;

layout (location=0) out vec4 fragColour;

float relativeLuminance(in vec3 rgb)
{
	return (0.2126*rgb.r + 0.7152*rgb.g + 0.0722*rgb.b);
}

//could also be done using tonemaps rather then mathematically
vec3 brightPass(in sampler2D img, in vec2 uv, in float middle)
{
	vec3 colour = texture(img, uv).rgb;

	float lum = relativeLuminance(colour);

	float bright = pow(lum, middle/lum);//if divisor = 0, OpenGL will output 0

	//return vec3(relativeLuminance(colour));
	//return vec3(bright);
	return vec3(bright * colour);

}

void main()
{
	fragColour.rgb = brightPass(sceneImg, passTexcoord, 0.5f);
}