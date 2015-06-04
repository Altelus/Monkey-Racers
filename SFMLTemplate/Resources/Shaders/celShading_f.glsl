
#version 330 core

// Receiving structure
in vertex
{
	vec3 positionObj;
	vec3 normalObj;
	vec2 texcoordObj;
} data;

layout (location=0) out vec4 fragColour;	// We need location as we have multiple targets
layout (location=1) out vec4 normalColour;

uniform sampler2D diffuseTex;
uniform sampler2D qMapTex;

uniform vec3 lightPos;
uniform vec3 eyePos;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float celShading(in vec3 pos, in vec3 norm)
{
	vec3 N = normalize(norm);
	vec3 L = normalize(lightPos - pos);
	
	float Lambert = max(0.0, dot(N, L));
	Lambert = texture(qMapTex, vec2(Lambert, 0.0)).r;

	return Lambert;
}

vec3 GoochShading(in vec3 pos, in vec3 norm)
{
	const vec3 cool = vec3(0.0, 0.0, 0.3);
	const vec3 warm = vec3(0.3, 0.3, 0.0);

	vec3 N = normalize(norm);
	vec3 L = normalize(lightPos - pos);

	float Lambert = max(0.0, dot(N, L));

	float Gooch = dot(N, L) * 0.5 + 0.5;

	vec3 GoochSample = mix(cool, warm, Gooch);

	vec3 diffuse = Lambert * texture(diffuseTex, data.texcoordObj).rgb;

	return diffuse + GoochSample;
}

float hatching(float uv, float freq, float weight)
{
	float sawtooth = fract(uv * freq);
	float triangle = abs(2.0 * sawtooth - 1.0);
	float square = step(weight, triangle);

	return square;
}

float hatching2f(vec2 uv, float freq, float weight)
{
	return hatching(length(uv), freq, weight);
}

void main()
{
	float cel = celShading(data.positionObj, data.normalObj);

	vec3 diffuse = texture(diffuseTex, data.texcoordObj).rgb;
	diffuse += 0.5*cel * vec3(0.992, 0.722, 0.075);
	normalColour.rgb = data.normalObj * 0.5 + 0.5;	// If color is between -1 and 1 this will make sure to keep it in range 0 to 1 (i.e. * 0.5 + 0.5)

	//float z = gl_FragCoord.z / gl_FragCoord.w;
	//float density = 0.001;
	//float fogFactor = exp2(-density * density * z * z * 1.442685);
	//fogFactor = clamp(fogFactor, 0.0, 1.0);
	//fragColour.rgb = mix(vec3(0.722, 0.961, 0.949), diffuse, fogFactor);


	vec3 fogColour = vec3(0.722, 0.961, 0.949);
	float z = gl_FragCoord.z / gl_FragCoord.w;
	float density = 0.001;
	float fog = exp2(-density * density * z * z);
	fog = clamp(fog, 0.0, 1.0);

	fragColour.rgb = mix(fogColour, diffuse, fog);

	//fragColour.rgb = vec3(z);

	//fragColour = vec4(z, z, z, 1.0);
}