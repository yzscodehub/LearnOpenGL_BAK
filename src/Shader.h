#pragma once

#include <string>
#include <unordered_map>

struct  ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	// Set uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	unsigned int GetUniformLocation(const std::string& name);

	unsigned int CreateShaderProgram(const std::string& vertexShader, const std::string fragmentShader);

	unsigned int CompileShader(unsigned int type, const std::string& source);

	ShaderProgramSource ParseShader(const std::string& filePath);

private:
	unsigned int m_rendererID;
	std::string m_filepath;
	std::unordered_map<std::string, int> m_uniformLoactionCache;
};

