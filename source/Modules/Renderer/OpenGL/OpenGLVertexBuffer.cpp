#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

#include "Common/Components/Vertex.h"

namespace
{
constexpr auto BUFFER_COUNT = 1;
}

OpenGLVertexBuffer::OpenGLVertexBuffer(std::vector<Vertex>& data)
{
	glGenBuffers(BUFFER_COUNT, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * data.size(), data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(2);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteVertexArrays(BUFFER_COUNT, &m_vertexBuffer);
}
