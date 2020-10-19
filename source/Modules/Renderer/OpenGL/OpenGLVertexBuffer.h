#pragma once

#include <vector>

struct Vertex;

class OpenGLVertexBuffer
{
public:
	OpenGLVertexBuffer() = default;
	OpenGLVertexBuffer(std::vector<Vertex>& data);
	~OpenGLVertexBuffer();

private:
	unsigned int m_vertexBuffer;
};
