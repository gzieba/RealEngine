#include "OpenGLRenderingObject.h"

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
