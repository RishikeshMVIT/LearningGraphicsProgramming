#version 410 core

layout(location = 0) in vec3 inColor;

layout(location = 0) out vec4 outColor;

void main()
{
	outColor = vec4(0, 0, 0, 1);
	outColor.rgb = inColor;
}