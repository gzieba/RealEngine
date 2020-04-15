#include "Model.h"

#include "Mesh.h"

Model::Model(std::string name, std::vector<Mesh*> meshes)
	: m_meshes(meshes)
	, m_name(name)
{

}

std::string Model::getName() const
{
	return m_name;
}
