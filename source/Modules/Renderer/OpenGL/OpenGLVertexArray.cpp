#include "OpenGLVertexArray.h"

#include <glad/glad.h>

#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBuffer.h"

namespace
{
constexpr auto VERTEX_ARRAY_COUNT = 1;
}

OpenGLVertexArray::OpenGLVertexArray(std::vector<Vertex>& vertexData, std::vector<unsigned int>& indexData)
	: m_indexBuffer(indexData)
	, m_vertexBuffer(vertexData)
{
	glGenVertexArrays(VERTEX_ARRAY_COUNT, &m_vertexArrayObject);
	bind();
}

OpenGLVertexArray::~OpenGLVertexArray()
{
	glDeleteVertexArrays(VERTEX_ARRAY_COUNT, &m_vertexArrayObject);
}

void OpenGLVertexArray::bind() const
{
	glBindVertexArray(m_vertexArrayObject);
}

void OpenGLVertexArray::unbind() const
{
	glBindVertexArray(0);
}
