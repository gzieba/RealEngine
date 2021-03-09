#pragma once

#include <vector>
#include <tuple>
#include <map>

#include "Common/Components/Vertex.h"

class Mesh
{
	std::vector<unsigned int> m_indices;
	std::vector<Vertex> m_vertices;

public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	std::vector<unsigned int> getIndices() const;
	std::vector<Vertex> getVertices() const;
};
