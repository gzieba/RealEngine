#pragma once

#include <variant>
#include <glm/glm.hpp>

enum class ShaderType;

class OpenGLShader
{
public:
	OpenGLShader(const ShaderType vertexShaderType, const ShaderType fragmentShaderType);

	void useShader() const;
	void setUniform(const char* name, std::variant<int, float, glm::vec3, glm::mat4> value) const;

private:
	void compileShaders();
	const char* shaderSource(const ShaderType type) const;

	unsigned int m_shaderProgram;

    ShaderType m_vertexShaderType;
    ShaderType m_fragmentShaderType;
};

