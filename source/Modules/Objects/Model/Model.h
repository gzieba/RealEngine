#pragma once

#include <vector>
#include <string>

class Mesh;

class Model
{
	std::vector<Mesh*> m_meshes;
public:
	Model(std::vector<Mesh*> meshes);
};

