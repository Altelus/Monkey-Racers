
#version 330 core

in vec2 passTexcoord;

layout (location=0) out vec4 fragColour;

uniform sampler2D sceneDiffuse;
uniform sampler2D sceneNormals;
uniform sampler2D sceneDepth;

uniform vec2 pixelSize;
uniform float lineWidth;

// Finding edges - Horizonal Kernel
float horizontalSobel(in sampler2D image, in vec2 centerUV, in float amplifier)
{
	vec2 offsetUV;

	vec3 totalSample = vec3(0.0);

	offsetUV = lineWidth * vec2(-pixelSize.x, -pixelSize.y);
	totalSample += -1.0 * texture(image, centerUV + offsetUV).rgb;

	offsetUV = lineWidth * vec2(-pixelSize.x, 0.0);
	totalSample += -2.0 * texture(image, centerUV + offsetUV).rgb;

	offsetUV = lineWidth * vec2(-pixelSize.x, pixelSize.y);
	totalSample += -1.0 * texture(image, centerUV + offsetUV).rgb;

	offsetUV = lineWidth * vec2(pixelSize.x, -pixelSize.y);
	totalSample += 1.0 * texture(image, centerUV + offsetUV).rgb;

	offsetUV = lineWidth * vec2(pixelSize.x, 0.0);
	totalSample += 2.0 * texture(image, centerUV + offsetUV).rgb;

	offsetUV = lineWidth * vec2(pixelSize.x, pixelSize.y);
	totalSample += 1.0 * texture(image, centerUV + offsetUV).rgb;

	float edge = dot(totalSample, totalSample) * amplifier;
	edge = clamp(edge, 0.0, 1.0);
	edge = (1.0 - edge) * amplifier;
	edge = clamp(edge, 0.0, 1.0);
	return edge;
}

// Finding edges - Vertical Kernel
float verticalSobel(in sampler2D image, in vec2 centerUV, in float amplifier)
{
	vec2 offsetUV;

	vec3 totalSample = vec3(0.0);

	offsetUV = lineWidth * vec2(-pixelSize.x, -pixelSize.y);
	totalSample += -1.0 * texture(image, centerUV + offsetUV).rgb;

	offsetUV = lineWidth * vec2(0.0, -pixelSize.y);
	totalSample += -2.0 * texture(image, centerUV + offsetUV).rgb;

	offsetUV = lineWidth * vec2(pixelSize.x, -pixelSize.y);
	totalSample += -1.0 * texture(image, centerUV + offsetUV).rgb;

	offsetUV = lineWidth * vec2(-pixelSize.x, pixelSize.y);
	totalSample += 1.0 * texture(image, centerUV + offsetUV).rgb;

	offsetUV = lineWidth * vec2(0.0, pixelSize.y);
	totalSample += 2.0 * texture(image, centerUV + offsetUV).rgb;

	offsetUV = lineWidth * vec2(pixelSize.x, pixelSize.y);
	totalSample += 1.0 * texture(image, centerUV + offsetUV).rgb;

	float edge = dot(totalSample, totalSample) * amplifier;
	edge = clamp(edge, 0.0, 1.0);
	edge = (1.0 - edge) * amplifier;
	edge = clamp(edge, 0.0, 1.0);
	return edge;
}

void main()
{
	//fragColour.rb = passTexcoord;
	float normalEdgeH = horizontalSobel(sceneNormals, passTexcoord, 100000.0);
	float normalEdgeV = verticalSobel(sceneNormals, passTexcoord, 100000.0);

	float edge = normalEdgeH * normalEdgeV;

	// As normals may be similar surfaces may seem melted, so we need to apply depth
	float depthEdgeH = horizontalSobel(sceneDepth, passTexcoord, 1000.0);	// Amplified by 100 because things further turn white very quickly
	float depthEdgeV = verticalSobel(sceneDepth, passTexcoord, 1000.0);	// Amplified by 100 because things further turn white very quickly
	
	float depthEdge = depthEdgeH * depthEdgeV;

	edge *= depthEdge;

	//vec3 diffuse = texture(sceneNormals, passTexcoord).rgb;	// For test
	vec3 diffuse = texture(sceneDiffuse, passTexcoord).rgb;
	
	//fragColour.rgb = diffuse;
	fragColour.rgb = diffuse * edge;
}