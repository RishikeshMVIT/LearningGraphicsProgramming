#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inVertexColor;
layout (location = 2) in vec2 inUVCoords;
layout (location = 3) in vec3 inNormal;

out vec3 vertexColor;
out vec2 uvCoords;
out vec3 normal;
out vec3 currentPosition;

uniform mat4 CAMERA_MATRIX;
uniform mat4 model;

void main()
{
	currentPosition = vec3(model * vec4(inPosition, 1.0));
	gl_Position = CAMERA_MATRIX * vec4(currentPosition, 1.0);
	
	vertexColor = inVertexColor;
	uvCoords = inUVCoords;
	normal = normalize(inNormal);
}