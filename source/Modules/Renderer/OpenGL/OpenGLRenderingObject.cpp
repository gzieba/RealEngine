#include "OpenGLRenderingObject.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <Common/logging.h>

OpenGLRenderingObject::OpenGLRenderingObject(unsigned int id,
											 Transform transform,
											 std::vector<Vertex> vertices,
											 std::vector<unsigned int> indices)
	: m_id(id)
	, m_transform(transform)
	, m_vao(std::make_unique<OpenGLVertexArray>(vertices, indices))
	, m_indicesCount(indices.size())
{
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

void OpenGLRenderingObject::setTexture(TextureType type, OpenGLRenderingObject::Texture2D data)
{
	m_textures.at(type) = {std::get<0>(data), std::get<1>(data),
							std::get<2>(data), std::get<3>(data)};
}

const std::unique_ptr<OpenGLVertexArray>& OpenGLRenderingObject::getVAO() const
{
	return m_vao;
}

void OpenGLRenderingObject::setupShader(const OpenGLShader& shader, const OpenGLCamera& camera)
{
	shader.useShader();
	setupTransformation(camera);
	shader.setUniform("model", m_modelMatrix);
	shader.setUniform("view", m_viewMatrix);
	shader.setUniform("projection", m_projectionMatrix);
	shader.setUniform("viewPosition", camera.getPosition());
}

void OpenGLRenderingObject::setupTextures(const OpenGLShader& shader)
{
	for(const auto& object : m_textures)
	{
		if(object.second.isValid())
		{
			glActiveTexture(GL_TEXTURE0 + static_cast<int>(object.first));

			std::string textureName;

			switch (object.first)
			{
				case TextureType::albedo:
					textureName = "albedoTexture";
					break;
				case TextureType::normal:
					textureName = "normalTexture";
					break;
				case TextureType::metallic:
					textureName = "metallicTexture";
					break;
				case TextureType::roughness:
					textureName = "roughnessTexture";
					break;
				case TextureType::ao:
					textureName = "aoTexture";
					break;
				default:
					return;
			}
			auto uniformName = "material." + textureName;
			shader.setUniform(uniformName.c_str(), static_cast<int>(object.first));
			m_textures.at(object.first).bind();
		}
	}
}

void OpenGLRenderingObject::setupLight(const OpenGLShader &shader, OpenGLLighting lighting)
{
	shader.setUniform("directionalLight.direction", lighting.getDirectionalLight().position);
	shader.setUniform("directionalLight.color", lighting.getDirectionalLight().color);
}

void OpenGLRenderingObject::setupTransformation(const OpenGLCamera& camera)
{
	m_modelMatrix = glm::identity<glm::mat4>();
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
