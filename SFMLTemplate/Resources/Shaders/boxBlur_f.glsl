
#version 330 core

in vec2 passTexcoord;

uniform sampler2D sceneImg;
uniform vec2 pixelSize;//offset to next pixel in uv space

layout (location=0) out vec4 fragColour;

vec3 boxBlur(in sampler2D img, in vec2 centerUV, in vec2 pixel)
{
	//return texture(img, centerUV).rgb;

	vec2 offsetUV;

	//vec4 totalSample = 1.0 * texture(img, centerUV);
	vec4 totalSample = texture(img, centerUV);

	// bottem left
	offsetUV = -pixel;
	totalSample += 1 * texture(img, centerUV+offsetUV);

	// bottem
	offsetUV.x = 0.0;
	totalSample += 1 * texture(img, centerUV+offsetUV);

	// bottem right
	offsetUV.x = +pixel.x;
	totalSample += 1 * texture(img, centerUV+offsetUV);

	// right
	offsetUV.y = 0.0;
	totalSample += 1 * texture(img, centerUV+offsetUV);

	// left
	offsetUV.x = -pixel.x;
	totalSample += 1 * texture(img, centerUV+offsetUV);

	// top left
	offsetUV.y = +pixel.y;
	totalSample += 1 * texture(img, centerUV+offsetUV);

	// top
	offsetUV.x = 0.0;
	totalSample += 1 * texture(img, centerUV+offsetUV);

	// top right
	offsetUV.x = +pixel.x;
	totalSample += 1 * texture(img, centerUV+offsetUV);

	// average
	totalSample /= 9.0;
	return totalSample.rgb;
}

void main()
{
	//fragColour.rgb = vec3(0.0, 1.0, 0.0);
	//fragColour.rgb = texture(sceneImg, passTexcoord).rgb;
	fragColour.rgb = boxBlur(sceneImg, passTexcoord, pixelSize);
}