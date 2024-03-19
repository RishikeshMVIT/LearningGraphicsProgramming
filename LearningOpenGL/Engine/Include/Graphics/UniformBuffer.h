#pragma once

#include <Prerequisites.h>
#include <glad\glad.h>

class UniformBuffer
{
public:
	UniformBuffer(const UniformBufferDesc& desc);
	~UniformBuffer();

	void SetData(void* data);

	U32 GetID();

private:

	U32 m_ID = 0;
	U32 m_size = 0;
};

