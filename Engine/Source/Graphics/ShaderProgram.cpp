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
		return;
	}

	U32 shaderID = 0;

	if (type == VertexShader)
		shaderID = glCreateShader(GL_VERTEX_SHADER);
	else if (type == FragmentShader)
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//switch (type)
	//{
	//	case ShaderType::VertexShader:
	//	{
	//		glCreateShader(GL_VERTEX_SHADER);
	//		break;
	//	}
	//	case ShaderType::FragmentShader:
	//	{
	//		glCreateShader(GL_FRAGMENT_SHADER);
	//		break;
	//	}
	//}

	auto sourcePointer = shaderCode.c_str();

	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);

	glAttachShader(m_programID, shaderID);
	m_attachedShaders[type] = shaderID;
}

void ShaderProgram::Link()
{
	glLinkProgram(m_programID);
}
