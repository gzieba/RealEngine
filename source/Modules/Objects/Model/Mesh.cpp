#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture2D> texturesData)
	: m_indices(indices)
	, m_vertices(vertices)
    , m_texturesData(texturesData)
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

std::vector<Mesh::Texture2D> Mesh::getTextures() const
{
    return m_texturesData;
}
