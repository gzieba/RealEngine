#pragma once

#include <vector>
#include <string>
#include <memory>

#include "Mesh.h"

class Model
{
	std::vector<std::unique_ptr<Mesh>> m_meshes;
public:
	Model(std::vector<std::unique_ptr<Mesh>> meshes);
};

