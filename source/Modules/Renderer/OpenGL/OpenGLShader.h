#pragma once

#include "Modules/Renderer/Interface/IShader.h"

enum class ShaderType;

class OpenGLShader : public IShader
{
public:
	OpenGLShader(const ShaderType vertexShaderType, const ShaderType fragmentShaderType);
	virtual ~OpenGLShader() = default;

	virtual void useShader() const override;
	virtual void setUniform(const char* name, std::variant<int, float, glm::vec3, glm::mat4> value) const override;

private:
	void compileShaders();
	const char* shaderSource(const ShaderType type) const;

	unsigned int m_shaderProgram;

	const ShaderType m_vertexShaderType;
	const ShaderType m_fragmentShaderType;
};

