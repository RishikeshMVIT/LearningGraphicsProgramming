#pragma once

#include <glad\glad.h>
#include <stb\stb_image.h>

#include "Shader.h"

class Texture
{
public:
	Texture(const char* image, GLenum type, GLuint slot, GLenum format, GLenum pixelType);

	void AssignTextureUnit(Shader& shader, const char* uniform, GLuint unit);

	void Bind();
	void Unbind();
	void Delete();

private:
	GLuint ID;
	GLenum type;
	GLuint unit;
};

