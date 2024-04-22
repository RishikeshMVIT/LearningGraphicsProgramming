#version 330 core

in vec3 vertexColor;
in vec2 texCoords;

out vec4 fragColor;

uniform sampler2D inTexture;

void main()
{
    fragColor = texture(inTexture, texCoords) * vec4(vertexColor, 1.0f);
}