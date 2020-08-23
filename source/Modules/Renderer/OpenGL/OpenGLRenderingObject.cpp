#include "OpenGLRenderingObject.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

OpenGLRenderingObject::OpenGLRenderingObject(unsigned int id, Transform transform, std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	: m_id(id)
	, m_transform(transform)
	, m_vao(OpenGLVertexArray(vertices, indices))
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

OpenGLVertexArray OpenGLRenderingObject::getVAO() const
{
	return m_vao;
}

void OpenGLRenderingObject::setupShader(OpenGLShader shader)
{
	shader.useShader();
	setupTransformation();
	shader.setUniform("model", m_modelMatrix);
	shader.setUniform("view", m_viewMatrix);
	shader.setUniform("projection", m_projectionMatrix);
}

void OpenGLRenderingObject::setupTransformation()
{
	m_modelMatrix = glm::translate(m_modelMatrix, m_transform.getPosition());
	glm::vec3 currentRotation = m_transform.getRotation();
	m_modelMatrix *= glm::eulerAngleXYZ(glm::radians(currentRotation.x), glm::radians(currentRotation.y), glm::radians(currentRotation.z));
	m_modelMatrix = glm::scale(m_modelMatrix, m_transform.getScale());

	//m_viewMatrix = m_camera->GetViewMatrix();

	m_projectionMatrix = glm::perspective(
				glm::radians(90.0f),
				static_cast<float>(1280) / static_cast<float>(720),
				0.1f,
				100.0f);
}
