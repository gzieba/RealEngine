#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace
{
constexpr auto BUFFER_COUNT = 1;
}

OpenGLIndexBuffer::OpenGLIndexBuffer(std::vector<unsigned int> &data)
{
	glGenBuffers(BUFFER_COUNT, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data.size(), data.data(), GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(BUFFER_COUNT, &m_indexBuffer);
}
