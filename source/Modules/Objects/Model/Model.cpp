#include "Model.h"

Model::Model(std::vector<std::unique_ptr<Mesh>> meshes)
	: m_meshes(std::move(meshes))
{

}
