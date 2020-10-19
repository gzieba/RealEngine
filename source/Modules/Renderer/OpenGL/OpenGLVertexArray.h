#pragma once

#include <memory>
#include <vector>

#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBuffer.h"

class Vertex;

class OpenGLVertexArray
{
public:
	OpenGLVertexArray(std::vector<Vertex>& vertexData, std::vector<unsigned int>& indexData);
	~OpenGLVertexArray();

	void bind() const;

private:
	unsigned int m_vertexArrayObject;

	std::unique_ptr<OpenGLIndexBuffer> m_indexBuffer;
	std::unique_ptr<OpenGLVertexBuffer> m_vertexBuffer;
};

