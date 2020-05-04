#pragma once

#include <memory>
#include <vector>

#include "Modules/Renderer/Interface/IVertexArray.h"

class OpenGLIndexBuffer;
class OpenGLVertexBuffer;
class Vertex;

class OpenGLVertexArray : public IVertexArray
{
public:
	OpenGLVertexArray(std::vector<Vertex>& vertexData, std::vector<unsigned int>& indexData);
	virtual ~OpenGLVertexArray();

	void bind() const override;
	void unbind() const override;

private:
	unsigned int m_vertexArrayObject;

	std::unique_ptr<OpenGLIndexBuffer> m_indexBuffer;
	std::unique_ptr<OpenGLVertexBuffer> m_vertexBuffer;
};

