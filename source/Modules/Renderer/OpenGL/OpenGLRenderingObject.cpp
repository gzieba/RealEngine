#include "OpenGLRenderingObject.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <Common/logging.h>

namespace
{
constexpr auto DEFAULT_DIRECTION = glm::vec3(-0.2f, -1.0f, -0.3f);
constexpr auto DEFAULT_COLOR = glm::vec3(1.0f, 1.0f, 1.0f);
constexpr auto DEFAULT_AMBIENT = glm::vec3(0.05f, 0.05f, 0.05f);
constexpr auto DEFAULT_DIFFUSE = glm::vec3(0.4f, 0.4f, 0.4f);
constexpr auto DEFAULT_SPECULAR = glm::vec3(0.5f, 0.5f, 0.5f);
}

OpenGLRenderingObject::OpenGLRenderingObject(unsigned int id,
											 Transform transform,
											 std::vector<Vertex> vertices,
											 std::vector<unsigned int> indices,
											 std::vector<Texture2D> textures)
	: m_id(id)
	, m_transform(transform)
	, m_vao(std::make_unique<OpenGLVertexArray>(vertices, indices))
	, m_indicesCount(indices.size())
{
	for(const auto& texture : textures)
		m_textures.emplace_back(std::get<0>(texture),
								std::get<1>(texture),
								std::get<2>(texture),
								std::get<3>(texture));
}

unsigned int OpenGLRenderingObject::getID() const
{
	return m_id;
}

unsigned int OpenGLRenderingObject::getIndicesCount() const
{
	return m_indicesCount;
}

Transform OpenGLRenderingObject::getTransform() const
{
	return m_transform;
}

void OpenGLRenderingObject::setTransform(Transform transform)
{
	m_transform = transform;
}

const std::unique_ptr<OpenGLVertexArray>& OpenGLRenderingObject::getVAO() const
{
	return m_vao;
}

void OpenGLRenderingObject::setupShader(OpenGLShader shader, const OpenGLCamera& camera)
{
	shader.useShader();
	setupTransformation(camera);
	shader.setUniform("model", m_modelMatrix);
	shader.setUniform("view", m_viewMatrix);
	shader.setUniform("projection", m_projectionMatrix);
}

void OpenGLRenderingObject::setupTextures(OpenGLShader shader)
{
	unsigned int diffuseTextureNumber = 1;
	unsigned int specularTextureNumber = 1;

	for(unsigned int i = 0; i < m_textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		std::string number;
		std::string textureName;

		switch (i)
		{
			case 0:
				number = std::to_string(diffuseTextureNumber++);
				textureName = "diffuseTexture" + number;
				break;
			case 1:
				number = std::to_string(specularTextureNumber++);
				textureName = "specularTexture" + number;
				break;
			default:
				return;
		}
		auto uniformName = "material." + textureName;
		shader.setUniform(uniformName.c_str(), static_cast<int>(i));
		m_textures[i].bind();
	}
	shader.setUniform("material.shininess", 0.5f);
}

void OpenGLRenderingObject::setupLight(const OpenGLShader &shader)
{
	shader.setUniform("directionalLight.direction", DEFAULT_DIRECTION);
	shader.setUniform("directionalLight.color", DEFAULT_COLOR);
	shader.setUniform("directionalLight.ambient", DEFAULT_AMBIENT);
	shader.setUniform("directionalLight.diffuse", DEFAULT_DIFFUSE);
	shader.setUniform("directionalLight.specular", DEFAULT_SPECULAR);
}

void OpenGLRenderingObject::setupTransformation(const OpenGLCamera& camera)
{
	m_modelMatrix = glm::translate(m_modelMatrix, m_transform.getPosition());
	glm::vec3 currentRotation = m_transform.getRotation();
	m_modelMatrix *= glm::eulerAngleXYZ(glm::radians(currentRotation.x), glm::radians(currentRotation.y), glm::radians(currentRotation.z));
	m_modelMatrix = glm::scale(m_modelMatrix, m_transform.getScale());

	m_viewMatrix = camera.getViewMatrix();

	m_projectionMatrix = glm::perspective(
				glm::radians(camera.getFOV()),
				static_cast<float>(1280) / static_cast<float>(720),
				0.1f,
				100.0f);
}
