/*
	Phong Lighting FS

	GLSL fragment shader that performs per-fragment Phong Lighting.
	Also applies texture.
*/

#version 330 core

in vertex
{
	vec3 positionObj;
	vec3 normalObj;
	vec2 texcoordObj;
} data;

uniform vec3 eyePos;
uniform vec3 lightPos;
uniform sampler2D diffuseTex;

layout (location=0) out vec4 fragColour;


vec3 PhongLighting(in vec3 fragPos, in vec3 fragNorm, in vec3 diffuseColour)
{
	// specular colour: 
	// diffuse map provides diffuse colour... why not a specular map?
	// (it doesn't have to be white reflecting back at us)
	const vec3 specularColour = vec3(1.0);

	const float shininess = 10.0;


	// ...this is generally a dark constant
	const vec3 ambient = vec3(0.00, 0.00, 0.05);


	// diffuse component
	vec3 N = normalize(fragNorm);
	vec3 L = normalize(lightPos - fragPos);
	float Lambert = max(0.0, dot(L, N));


	// specular coefficient
	vec3 E = normalize(eyePos - fragPos);
	vec3 R = reflect(L, N);
	float Phong = max(0.0, dot(R, -E));
	Phong = pow(Phong, shininess);


	// add components
	vec3 diffuse = Lambert * diffuseColour;
	vec3 specular = Phong * specularColour;
	return ( diffuse + specular + ambient );
}


void main()
{
	vec3 diffuseColour = texture(diffuseTex, data.texcoordObj).rgb;

	fragColour.rgb = PhongLighting(data.positionObj, data.normalObj, diffuseColour);
}
