#pragma once

#include <Platform\CoreWindow.h>
#include <Math\Vector4.h>
#include <Math\Quad.h>
#include <Graphics\VertexArrayObject.h>
#include <Graphics\ShaderProgram.h>

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

public:
	void Clear(const Vector4& color);
	void SetViewport(const Quad& quad);
	void SetVertexArrayObject(const VertexArrayObjectPtr& vao);
	void DrawTriangles(U32 vertexCount, U32 offset);
	void SetShaderProgram(const ShaderProgramPtr& program);

public:
	VertexArrayObjectPtr CreateVertexArrayObject(const VertexBufferDesc& data);
	ShaderProgramPtr CreateShaderProgram(const ShaderProgramDesc& desc);
};

