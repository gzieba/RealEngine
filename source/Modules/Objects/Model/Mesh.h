#pragma once

#include <vector>
#include <tuple>

#include "Common/Components/Vertex.h"

class Mesh
{
	typedef std::tuple<unsigned char*, int, int, int> Texture2D;

	std::vector<unsigned int> m_indices;
	std::vector<Vertex> m_vertices;
	std::vector<Texture2D> m_texturesData;

public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture2D> texturesData);
	std::vector<unsigned int> getIndices() const;
	std::vector<Vertex> getVertices() const;
	std::vector<Texture2D> getTextures() const;
};
