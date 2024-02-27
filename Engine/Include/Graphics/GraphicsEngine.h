#pragma once

#include <Platform\CoreWindow.h>
#include <Math\Vector4.h>
#include <Math\Quad.h>
#include <Graphics\VertexArrayObject.h>
#include <Graphics\ShaderProgram.h>
#include <Graphics\UniformBuffer.h>

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

public:
	void Clear(const Vector4& color);
	void SetViewport(const Quad& quad);
	void SetVertexArrayObject(const VertexArrayObjectPtr& vao);
	void DrawTriangles(const TriangleType& triangleType, U32 vertexCount, U32 offset);
	void SetShaderProgram(const ShaderProgramPtr& program);
	void SetUniformBuffer(const UniformBufferPtr& buffer, U32 slot);

public:
	VertexArrayObjectPtr CreateVertexArrayObject(const VertexBufferDesc& data);
	ShaderProgramPtr CreateShaderProgram(const ShaderProgramDesc& desc);
	UniformBufferPtr CreateUniformBuffer(const UniformBufferDesc& desc);
};

