#pragma once

#include <glad\glad.h>
#include <stb\stb_image.h>

#include "Shader.h"

class Texture
{
public:
	Texture(const char* image, GLenum type, GLenum slot, GLenum format, GLenum pixelType);
	~Texture();

	void AssignTextureUnit(Shader& shader, const char* uniform, GLuint unit);

	void Bind();
	void Unbind();
	void Delete();

private:
	GLuint id;
	GLenum type;

	unsigned char* data = 0;

};

