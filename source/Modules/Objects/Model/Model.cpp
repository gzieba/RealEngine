#include "Model.h"

Model::Model(std::vector<std::unique_ptr<Mesh>> meshes)
	: m_meshes(std::move(meshes))
{

}

const std::vector<std::unique_ptr<Mesh>> &Model::getMeshes() const
{
	return m_meshes;
}
