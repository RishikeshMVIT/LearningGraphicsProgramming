#pragma once

#include <memory>
#include <sstream>
#include <iostream>
#include <stdexcept>

class VertexArrayObject;
class ShaderProgram;
class UniformBuffer;

typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;
typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;
typedef std::shared_ptr<UniformBuffer> UniformBufferPtr;

typedef float F32;
typedef int I32;
typedef unsigned int U32;


struct VertexAttribute
{
	U32 elementCount = 0;
};

struct VertexBufferDesc
{
	void* vertices = nullptr;
	U32 vertexSize = 0;
	U32 vertexCount = 0;

	VertexAttribute* attributes = nullptr;
	U32 attributeCount = 0;
};

struct ShaderProgramDesc
{
	const wchar_t* vertexShaderFilePath;
	const wchar_t* fragmentShaderFilePath;
};

struct UniformBufferDesc
{
	U32 size = 0;
};

struct UniformData
{
	F32 scale;
};

enum TriangleType
{
	TriangleList = 0,
	TriangleStrip,
	TriangleFan
};

enum ShaderType
{
	VertexShader = 0,
	FragmentShader,
	GeometryShader,
	TesselationShader,
	ComputeShader
};

#define ENGINE_ERROR(msg)\
{\
	std::stringstream log;\
	log << "Engine Error: " << msg << std::endl;\
	throw std::runtime_error(log.str());\
}

#define ENGINE_WARN(msg)\
{\
	std::wclog << "Engine Warning: " << msg << std::endl;\
}


#define ENGINE_INFO(msg)\
{\
	std::wclog << "Engine Info: " << msg << std::endl;\
}