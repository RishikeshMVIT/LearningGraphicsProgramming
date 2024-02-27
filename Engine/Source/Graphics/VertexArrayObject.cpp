#include <Graphics\VertexArrayObject.h>

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& desc)
{
	if (!desc.vertexCount)	ENGINE_ERROR("VertexArrayObject: Vertex Count is NULL");
	if (!desc.vertexSize)	ENGINE_ERROR("VertexArrayObject: Vertex Size is NULL");
	if (!desc.vertices)		ENGINE_ERROR("VertexArrayObject: Vertex Array is empty");

	glGenVertexArrays(1, &m_vertexArrayObjectID);
	glBindVertexArray(m_vertexArrayObjectID);

	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, desc.vertexSize * desc.vertexCount, desc.vertices, GL_STATIC_DRAW);

	for (U32 i = 0; i < desc.attributeCount; i++)
	{
		glVertexAttribPointer(
			i,
			desc.attributes[i].elementCount,
			GL_FLOAT,
			GL_FALSE,
			desc.vertexSize,
			(void*)(i == 0 ? 0 : desc.attributes[i].elementCount * sizeof(F32))
		);
		glEnableVertexAttribArray(i);
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, desc.vertexSize, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	m_vertexBufferDesc = desc;
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
	return m_vertexBufferDesc.vertexCount;
}

U32 VertexArrayObject::GetVertexSize()
{
	return m_vertexBufferDesc.vertexSize;
}
