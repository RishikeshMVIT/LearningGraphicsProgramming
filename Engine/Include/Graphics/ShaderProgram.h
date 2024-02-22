#pragma once

#include <glad\glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <Prerequisites.h>

class ShaderProgram
{
public: 
	ShaderProgram(const ShaderProgramDesc& desc);
	~ShaderProgram();

public:
	U32 GetID();

private:
	void Attach(const wchar_t* shaderFilePath, const ShaderType& type);
	void Link();

private:
	U32 m_programID = 0;
	U32 m_attachedShaders[2] = {};
};

