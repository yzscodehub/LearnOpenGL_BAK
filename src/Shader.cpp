#include "Shader.h"
#include "Renderer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


Shader::Shader(const std::string& filepath)
	: m_filepath(filepath), m_rendererID(0)
{
	ShaderProgramSource source = ParseShader(m_filepath);
	std::cout << "VERTEX" << std::endl;
	std::cout << source.VertexSource << std::endl;
	std::cout << "FRAGMENT" << std::endl;
	std::cout << source.FragmentSource << std::endl;
	
	m_rendererID = CreateShaderProgram(source.VertexSource, source.FragmentSource);

	Bind();
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_rendererID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_rendererID));
}

void Shader::UnBind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
	if (m_uniformLoactionCache.find(name) != m_uniformLoactionCache.end()) {
		return m_uniformLoactionCache[name];
	}

	GLCall(int location = glGetUniformLocation(m_rendererID, name.c_str()));
	if (location == -1) {
		std::cout << "No active uniform variable with name " << name << " found" << std::endl;
	}

	m_uniformLoactionCache[name] = location;

	return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);
	std::string line;
	std::stringstream ss[2];

	enum class ShaderType
	{
		None = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	ShaderType type;
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	// 错误检查
	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to Compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShaderProgram(const std::string& vertexShader, const std::string fragmentShader)
{
	// 创建一个着色器程序
	GLCall(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

