
#version 330 core

in vec2 passTexcoord;

uniform sampler2D sceneImg;
uniform vec2 pixelSize;//offset to next pixel in uv space

layout (location=0) out vec4 fragColour;

vec3 gaussBlur2D(in sampler2D img, in vec2 centerUV, in vec2 pixel)
{
	//return texture(img, centerUV).rgb;

	vec2 offsetUV;

	//vec4 totalSample = 1.0 * texture(img, centerUV);
	vec4 totalSample = 41 * texture(img, centerUV);

	// bottem left
	offsetUV = -pixel;
	totalSample += 16 * texture(img, centerUV+offsetUV);

	// bottem
	offsetUV.x = 0.0;
	totalSample += 26 * texture(img, centerUV+offsetUV);

	// bottem right
	offsetUV.x = +pixel.x;
	totalSample += 16 * texture(img, centerUV+offsetUV);

	// right
	offsetUV.y = 0.0;
	totalSample += 26 * texture(img, centerUV+offsetUV);

	// left
	offsetUV.x = -pixel.x;
	totalSample += 26 * texture(img, centerUV+offsetUV);

	// top left
	offsetUV.y = +pixel.y;
	totalSample += 16 * texture(img, centerUV+offsetUV);

	// top
	offsetUV.x = 0.0;
	totalSample += 26 * texture(img, centerUV+offsetUV);

	// top right
	offsetUV.x = +pixel.x;
	totalSample += 16 * texture(img, centerUV+offsetUV);

	////////////////////////////////////////////////////
	
	//// top left to right
	offsetUV = -2*pixel;
	totalSample += 1 * texture(img, centerUV+offsetUV);

	offsetUV.x +=pixel.x;
	totalSample += 4 * texture(img, centerUV+offsetUV);

	offsetUV.x +=pixel.x;
	totalSample += 7 * texture(img, centerUV+offsetUV);

	offsetUV.x +=pixel.x;
	totalSample += 4 * texture(img, centerUV+offsetUV);

	offsetUV.x +=pixel.x;
	totalSample += 1 * texture(img, centerUV+offsetUV);

	//// top right down to bottem right
	offsetUV.y -=pixel.y;
	totalSample += 4 * texture(img, centerUV+offsetUV);

	offsetUV.y -=pixel.y;
	totalSample += 7 * texture(img, centerUV+offsetUV);

	offsetUV.y -=pixel.y;
	totalSample += 4 * texture(img, centerUV+offsetUV);

	offsetUV.y -=pixel.y;
	totalSample += 1 * texture(img, centerUV+offsetUV);

	//// top left to bottem left
	offsetUV.x = -2*pixel.x;
	offsetUV.y = pixel.y;
	totalSample += 4 * texture(img, centerUV+offsetUV);

	offsetUV.y -=pixel.y;
	totalSample += 7 * texture(img, centerUV+offsetUV);

	offsetUV.y -=pixel.y;
	totalSample += 4 * texture(img, centerUV+offsetUV);

	offsetUV.y -=pixel.y;
	totalSample += 1 * texture(img, centerUV+offsetUV);

	//// bottem left to bottem right
	offsetUV.x = -pixel.x;
	offsetUV.y = -2*pixel.y;
	totalSample += 4 * texture(img, centerUV+offsetUV);

	offsetUV.x +=pixel.x;
	totalSample += 7 * texture(img, centerUV+offsetUV);

	offsetUV.x +=pixel.x;
	totalSample += 4 * texture(img, centerUV+offsetUV);

	/////////////////////////////////////////////////////
	// average
	totalSample /= 273;
	return totalSample.rgb;
}

vec3 gaussBlur1Dvertical(in sampler2D img, in vec2 centerUV, in float pixel)
{
	//offsets: 0.0, 1.3846153846, 3.2307692308
	//weights: 0.2270270270, 0.3162162162, 0.0702702703

	vec2 offsetUV = vec2(0.0, 0.0);

	vec4 totalSample =  0.2270270270 * texture(img, centerUV);
	
	offsetUV.y = 1.3846153846 * pixelSize;
	totalSample += 0.3162162162 * texture(img, centerUV+offsetUV);
	totalSample += 0.3162162162 * texture(img, centerUV-offsetUV);

	offsetUV.y = 3.2307692308 * pixelSize;
	totalSample += 0.0702702703 * texture(img, centerUV+offsetUV);
	totalSample += 0.0702702703 * texture(img, centerUV-offsetUV);

	return totalSample.rgb;
}

vec3 gaussBlur1DHorizontal(in sampler2D img, in vec2 centerUV, in float pixel)
{
	//offsets: 0.0, 1.3846153846, 3.2307692308
	//weights: 0.2270270270, 0.3162162162, 0.0702702703

	vec2 offsetUV = vec2(0.0, 0.0);

	vec4 totalSample =  0.2270270270 * texture(img, centerUV);
	
	offsetUV.x = 1.3846153846 * pixelSize;
	totalSample += 0.3162162162 * texture(img, centerUV+offsetUV);
	totalSample += 0.3162162162 * texture(img, centerUV-offsetUV);

	offsetUV.x = 3.2307692308 * pixelSize;
	totalSample += 0.0702702703 * texture(img, centerUV+offsetUV);
	totalSample += 0.0702702703 * texture(img, centerUV-offsetUV);

	return totalSample.rgb;
}

void main()
{
	//fragColour.rgb = vec3(0.0, 1.0, 0.0);
	//fragColour.rgb = texture(sceneImg, passTexcoord).rgb;
	//fragColour.rgb = gaussBlur2D(sceneImg, passTexcoord, pixelSize);

	fragColour.rgb = gaussBlur2D(sceneImg, passTexcoord, pixelSize);
}