#pragma once

#include <memory>
#include <vector>

#include "Common/Components/Transform.h"
#include "Common/Components/Vertex.h"

#include "OpenGLCamera.h"
#include "OpenGLShader.h"
#include "OpenGLVertexArray.h"

class OpenGLRenderingObject
{
public:
	OpenGLRenderingObject(unsigned int id, Transform transform, std::vector<Vertex> vertices, std::vector<unsigned int> indices);

	unsigned int getID() const;
	unsigned int getIndicesCount() const;
	Transform getTransform() const;
	void setTransform(Transform transform);
	OpenGLVertexArray getVAO() const;
	void setupShader(OpenGLShader shader, const OpenGLCamera& camera);

private:
	void setupTransformation(const OpenGLCamera& camera);

	unsigned int m_id;
	unsigned int m_indicesCount;
	Transform m_transform;
	OpenGLVertexArray m_vao;

	glm::mat4 m_modelMatrix = glm::mat4(1.0f);
	glm::mat4 m_viewMatrix = glm::mat4(1.0f);
	glm::mat4 m_projectionMatrix = glm::mat4(1.0f);
};

