#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices=4) out;

uniform mat4 modelView;
uniform mat4 proj;
uniform float partSize;

out vec2 texCoord;

void main()
{
	vec4 positionEye = modelView*gl_in[0].gl_Position;

	vec4 offset = vec4(0.0);

	//bottem left
	offset.x = -partSize;
	offset.y = -partSize;
	gl_Position = proj * (positionEye + offset);
	texCoord = vec2(0, 1);
	EmitVertex();

	//bottem right
	offset.x = partSize;
	gl_Position = proj * (positionEye + offset);
	texCoord.x = 1.0;
	EmitVertex();

	//top left
	offset.x = -partSize;
	offset.y = +partSize;
	gl_Position = proj * (positionEye + offset);
	texCoord = vec2(0.0, 0.0);
	EmitVertex();

	//top right
	offset.x = partSize;
	gl_Position = proj * (positionEye + offset);
	texCoord.x = 1.0;
	EmitVertex();

	EndPrimitive();
}