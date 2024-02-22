#pragma once

#include <Prerequisites.h>
#include <glad\glad.h>

class VertexArrayObject
{
public:
	VertexArrayObject(const VertexBufferData& data);
	~VertexArrayObject();

public:
	U32 GetID();
	U32 GetVertexBufferSize();
	U32 GetVertexSize();

private:

	U32 m_vertexBufferID = 0;
	U32 m_vertexArrayObjectID = 0;
	VertexBufferData m_vertexBufferData;
};

