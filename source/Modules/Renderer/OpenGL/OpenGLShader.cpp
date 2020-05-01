#include "OpenGLShader.h"

#include <glad/glad.h>
#include "Common/glm/gtc/type_ptr.hpp"

#include "Modules/Renderer/ShaderType.h"
#include "Common/logging.h"

namespace
{
constexpr auto SHADER_COUNT = 1;
constexpr auto SHADER_LENGTH = 0;

const std::string VERTEX_SHADER_SOURCE =
		#include "Shaders/vertex_shader.glsl"
;

const std::string FRAGMENT_SHADER_SOURCE =
		#include "Shaders/fragment_shader.glsl"
;
}

OpenGLShader::OpenGLShader(const ShaderType vertexShaderType, const ShaderType fragmentShaderType)
	: m_vertexShaderType(vertexShaderType)
	, m_fragmentShaderType(fragmentShaderType)
{
	compileShaders();
}

void OpenGLShader::useShader() const
{
	glUseProgram(m_shaderProgram);
}

void OpenGLShader::setUniform(const char* name, std::variant<int, float, glm::vec3, glm::mat4> value)
{
	auto uniformLocation = glGetUniformLocation(m_shaderProgram, name);
	if(uniformLocation < 0)
	{
		LOG(ERROR) << LOCATION << "Incorrect uniform name: " << name;
		return;
	}
	if(std::get_if<int>(&value))
	{
		glUniform1i(uniformLocation, std::get<int>(value));
		return;
	}
	if(std::get_if<float>(&value))
	{
		glUniform1f(uniformLocation, std::get<float>(value));
		return;
	}
	if(std::get_if<glm::vec3>(&value))
	{
		glUniform3fv(uniformLocation, 1, glm::value_ptr(std::get<glm::vec3>(value)));
		return;
	}
	if(std::get_if<glm::mat4>(&value))
	{
		glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(std::get<glm::mat4>(value)));
		return;
	}
	LOG(WARNING) << LOCATION << "Value of incorrect type.";
	return;
}

void OpenGLShader::compileShaders()
{
	const char* vertexShaderSource[] = { shaderSource(m_vertexShaderType) };
	const char* fragmentShaderSource[] = { shaderSource(m_fragmentShaderType) };

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, SHADER_COUNT, vertexShaderSource, &SHADER_LENGTH);
	glCompileShader(vertexShader);

	int vertexCompileSucceded;
	char vertexInfoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexCompileSucceded);

	if(!vertexCompileSucceded)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, vertexInfoLog);
		LOG(ERROR) << LOCATION << "SHADER::VERTEX::COMPILATON_FAILED: " << vertexInfoLog;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, SHADER_COUNT, fragmentShaderSource, &SHADER_LENGTH);
	glCompileShader(fragmentShader);

	int fragmentCompileSucceded;
	char fragmentInfoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentCompileSucceded);

	if(!fragmentCompileSucceded)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, fragmentInfoLog);
		LOG(ERROR) << LOCATION << "SHADER::FRAGMENT::COMPILATION_FAILED: " << fragmentInfoLog;
	}

	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vertexShader);
	glAttachShader(m_shaderProgram, fragmentShader);
	glLinkProgram(m_shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

const char* OpenGLShader::shaderSource(const ShaderType type) const
{
	switch(type)
	{
		case ShaderType::OpenGLVertexShader:
			return VERTEX_SHADER_SOURCE.c_str();
		case ShaderType::OpenGLFragmentShader:
			return FRAGMENT_SHADER_SOURCE.c_str();
		default:
			return "";
	}
}
