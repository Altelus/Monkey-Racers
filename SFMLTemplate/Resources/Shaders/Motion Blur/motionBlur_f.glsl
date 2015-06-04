#version 330 core

in vec2 passTexcoord;

uniform sampler2D sceneDiffuse;
uniform sampler2D sceneDepth;

uniform mat4 inverseViewProj;
uniform mat4 prevViewProj;

layout (location=0) out vec4 fragColour;

void main()
{
	// pixel to world space
	float depthSample = texture(sceneDepth, passTexcoord).r;
	vec4 H = vec4((passTexcoord.x * 2) - 1, (1 - passTexcoord.y) * 2 - 1, depthSample, 1.0);

	vec4 D = inverseViewProj * H;

	vec4 worldPos = D / D.w;

	vec4 currentPos = H;

	// computer velocity vectors
	vec4 previousPos = prevViewProj * worldPos;

	vec2 velocity = (currentPos-previousPos).xy*0.0001;

	// motion blur sampling along velocity vector
	vec2 texCoord = passTexcoord;

	vec3 diffuse = texture(sceneDiffuse, texCoord).rgb;
	texCoord += velocity;

	for (int i = 0; i < 254; i++)
	{
		texCoord += velocity;
		diffuse += texture(sceneDiffuse, texCoord).rgb;
	}
	diffuse = diffuse / 256;

	fragColour.rgb = diffuse;
}