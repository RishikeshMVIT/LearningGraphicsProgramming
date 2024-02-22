#include <Graphics\VertexArrayObject.h>

VertexArrayObject::VertexArrayObject(const VertexBufferData& data)
{
	glGenBuffers(1, &m_vertexBufferID);
	glGenVertexArrays(1, &m_vertexArrayObjectID);
	glBindVertexArray(m_vertexArrayObjectID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, data.vertexSize * data.vertexCount, data.vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data.vertexSize, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	m_vertexBufferData = data;
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteBuffers(1, &m_vertexBufferID);
	glDeleteVertexArrays(1, &m_vertexArrayObjectID);

}

U32 VertexArrayObject::GetID()
{
	return m_vertexArrayObjectID;
}

U32 VertexArrayObject::GetVertexBufferSize()
{
	return m_vertexBufferData.vertexCount;
}

U32 VertexArrayObject::GetVertexSize()
{
	return m_vertexBufferData.vertexSize;
}
