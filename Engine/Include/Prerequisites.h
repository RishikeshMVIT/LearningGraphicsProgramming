#pragma once

#include <memory>

class VertexArrayObject;
class ShaderProgram;

typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;
typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;

typedef float F32;
typedef int I32;
typedef unsigned int U32;

struct VertexBufferData
{
	void* vertices = nullptr;
	U32 vertexSize = 0;
	U32 vertexCount = 0;
};

struct ShaderProgramDesc
{
	const wchar_t* vertexShaderFilePath;
	const wchar_t* fragmentShaderFilePath;
};

enum ShaderType
{
	VertexShader = 0,
	FragmentShader,
	GeometryShader,
	TesselationShader,
	ComputeShader
};
