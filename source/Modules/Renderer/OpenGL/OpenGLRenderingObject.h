#pragma once

#include <memory>
#include <vector>

#include "Common/Components/Transform.h"
#include "Common/Components/Vertex.h"

#include "OpenGLVertexArray.h"

class OpenGLRenderingObject
{
public:
	OpenGLRenderingObject(unsigned int id, Transform transform, std::vector<Vertex> vertices, std::vector<unsigned int> indices);

	unsigned int getID() const;
	unsigned int getIndicesCount() const;
	Transform getTransform() const;
	void setTransform(Transform transform);
	OpenGLVertexArray getVAO() const;

private:
	unsigned int m_id;
	unsigned int m_indicesCount;
	Transform m_transform;
	OpenGLVertexArray m_vao;
};

