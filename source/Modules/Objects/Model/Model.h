#pragma once

#include <vector>
#include <string>

class Mesh;

class Model
{
	std::vector<Mesh*> m_meshes;
	std::string m_name;
public:
	Model(std::string name, std::vector<Mesh*> meshes);

	std::string getName() const;
};

