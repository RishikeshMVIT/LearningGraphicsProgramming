#include <Graphics\ShaderProgram.h>

ShaderProgram::ShaderProgram(const ShaderProgramDesc& desc)
{
	m_programID = glCreateProgram();
	Attach(desc.vertexShaderFilePath, ShaderType::VertexShader);
	Attach(desc.fragmentShaderFilePath, ShaderType::FragmentShader);
	Link();
}

ShaderProgram::~ShaderProgram()
{
	for (U32 i = 0; i < 2; i++)
	{
		glDetachShader(m_programID, m_attachedShaders[i]);
		glDeleteShader(m_attachedShaders[i]);
	}
	glDeleteProgram(m_programID);
}

U32 ShaderProgram::GetID()
{
	return m_programID;
}

void ShaderProgram::SetUniformBufferSlot(const char* name, U32 slot)
{
	U32 index = glGetUniformBlockIndex(m_programID, name);
	glUniformBlockBinding(m_programID, index, slot);
}

void ShaderProgram::Attach(const wchar_t* shaderFilePath, const ShaderType& type)
{
	std::string shaderCode;
	std::ifstream shaderStream(shaderFilePath);

	if (shaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	}
	else
	{
		ENGINE_WARN("ShaderProgram: " << shaderFilePath << "not found");
		return;
	}

	U32 shaderID = 0;

	//if (type == VertexShader)
	//	shaderID = glCreateShader(GL_VERTEX_SHADER);
	//else if (type == FragmentShader)
	//	shaderID = glCreateShader(GL_FRAGMENT_SHADER);

	switch (type)
	{
		case ShaderType::VertexShader:
		{
			shaderID = glCreateShader(GL_VERTEX_SHADER);
			break;
		}
		case ShaderType::FragmentShader:
		{
			shaderID = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		}
	}

	auto sourcePointer = shaderCode.c_str();

	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);

	// Compilation Error Checking
	I32 logLength = 0;
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> errorMessage(logLength + 1);
		glGetShaderInfoLog(shaderID, logLength, NULL, &errorMessage[0]);
		ENGINE_WARN("ShaderProgram: " << shaderFilePath << " Compiled with errors: " << std::endl << &errorMessage[0]);
		return;
	}


	glAttachShader(m_programID, shaderID);
	m_attachedShaders[type] = shaderID;

	ENGINE_INFO("ShaderProgram: " << shaderFilePath << " Compiled successfully")
}

void ShaderProgram::Link()
{
	glLinkProgram(m_programID);

	I32 logLength = 0;
	glGetShaderiv(m_programID, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> errorMessage(logLength + 1);
		glGetShaderInfoLog(m_programID, logLength, NULL, &errorMessage[0]);
		ENGINE_WARN("ShaderProgram: " << std::endl << &errorMessage[0]);
		return;
	}
}
