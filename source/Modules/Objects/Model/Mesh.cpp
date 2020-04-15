#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	: m_indices(indices)
	, m_vertices(vertices)
{

}
