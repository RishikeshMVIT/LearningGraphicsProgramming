#pragma once

#include <glad\glad.h>

#include "VBO.h"

class VAO
{
public:
	VAO();

	void LinkAttributes(VBO& vbo, GLuint layout, GLuint componentCount, GLenum type, GLsizeiptr stride, void* offset);

	void Bind();
	void Unbind();
	void Delete();

public:
	GLuint ID;
};

