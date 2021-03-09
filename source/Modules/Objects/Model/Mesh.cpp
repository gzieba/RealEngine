#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	: m_indices(indices)
	, m_vertices(vertices)
{

}

std::vector<unsigned int> Mesh::getIndices() const
{
	return m_indices;
}

std::vector<Vertex> Mesh::getVertices() const
{
    return m_vertices;
}
