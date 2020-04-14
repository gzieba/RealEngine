#pragma once

#include "Common/glm/glm.hpp"
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

class Mesh
{

	std::vector<unsigned int> m_indices;
	std::vector<Vertex> m_vertices;

public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
};
