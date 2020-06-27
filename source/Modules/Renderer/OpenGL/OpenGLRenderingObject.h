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
	void setTransform(Transform transform);

private:
	unsigned int m_id;
	Transform m_transform;
	std::unique_ptr<OpenGLVertexArray> m_vao;
};

