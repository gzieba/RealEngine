#include "OpenGLRenderingObject.h"

OpenGLRenderingObject::OpenGLRenderingObject(unsigned int id, Transform transform, std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	: m_id(id)
	, m_transform(transform)
	, m_vao(std::make_unique<OpenGLVertexArray>(vertices, indices))
{

}

unsigned int OpenGLRenderingObject::getID() const
{
	return m_id;
}

void OpenGLRenderingObject::setTransform(Transform transform)
{
	m_transform = transform;
}
