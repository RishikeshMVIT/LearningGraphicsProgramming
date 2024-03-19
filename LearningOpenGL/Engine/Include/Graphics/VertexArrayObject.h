#pragma once

#include <Prerequisites.h>
#include <glad\glad.h>

class VertexArrayObject
{
public:
	VertexArrayObject(const VertexBufferDesc& desc);
	~VertexArrayObject();

public:
	U32 GetID();
	U32 GetVertexBufferSize();
	U32 GetVertexSize();

private:

	U32 m_vertexBufferID = 0;
	U32 m_vertexArrayObjectID = 0;
	VertexBufferDesc m_vertexBufferDesc;
};

