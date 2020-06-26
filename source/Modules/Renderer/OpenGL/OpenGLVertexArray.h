#pragma once

#include <memory>
#include <vector>

class OpenGLIndexBuffer;
class OpenGLVertexBuffer;
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

	std::unique_ptr<OpenGLIndexBuffer> m_indexBuffer;
	std::unique_ptr<OpenGLVertexBuffer> m_vertexBuffer;
};

