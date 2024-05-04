#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uvCoords;

out vec3 vertexColor;
out vec2 texCoords;

uniform mat4 CAMERA_MATRIX;

void main()
{
   gl_Position = CAMERA_MATRIX * vec4(position, 1.0);
   vertexColor = color;
   texCoords = uvCoords;
}