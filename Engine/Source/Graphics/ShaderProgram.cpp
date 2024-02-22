#include <Graphics\ShaderProgram.h>

ShaderProgram::ShaderProgram(const ShaderProgramDesc& desc)
{
	m_programID = glCreateProgram();
	Attach(desc.vertexShaderFilePath, VertexShader);
	Attach(desc.fragmentShaderFilePath, FragmentShader);
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
	if (!shaderStream.is_open())
		return;

	std::stringstream sstr;
	sstr << shaderStream.rdbuf();
	shaderCode = sstr.str();
	shaderStream.close();

	U32 shaderID = 0;

	switch (type)
	{
		case ShaderType::VertexShader:
		{
			glCreateShader(GL_VERTEX_SHADER);
		}
		case ShadeType::FragmentShader:
		{
			glCreateShader(GL_FRAGMENT_SHADER);
		}
		case ShadeType::GeometryShader:
		case ShadeType::TesselationShader:
		case ShadeType::ComputeShader:
		{

		}
	}

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
