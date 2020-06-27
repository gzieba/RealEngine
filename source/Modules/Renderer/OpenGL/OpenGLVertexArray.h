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
	void unbind() const;

private:
	unsigned int m_vertexArrayObject;

	OpenGLIndexBuffer m_indexBuffer;
	OpenGLVertexBuffer m_vertexBuffer;
};

