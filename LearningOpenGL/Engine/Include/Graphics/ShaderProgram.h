#pragma once

#include <glad\glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <Prerequisites.h>

class ShaderProgram
{
public: 
	ShaderProgram(const ShaderProgramDesc& desc);
	~ShaderProgram();

public:
	U32 GetID();

public:
	void SetUniformBufferSlot(const char* name, U32 slot);

private:
	void Attach(const wchar_t* shaderFilePath, const ShaderType& type);
	void Link();

private:
	U32 m_programID = 0;
	U32 m_attachedShaders[2];
};

