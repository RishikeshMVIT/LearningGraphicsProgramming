#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad\glad.h>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);

	//Enable shader
	void Use();
	void Delete();

	//Uniform Utility Functions
	void SetBool(const std::string& name, bool value)	const;
	void SetInt(const std::string& name, int value)		const;
	void SetFloat(const std::string& name, float value) const;

private:
	void CheckCompileErrors(GLuint shader, const char* type);

public:
	GLuint ID = 0;
};

