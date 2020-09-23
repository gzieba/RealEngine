#pragma once

#include <string>
#include <vector>
#include <memory>

class Model;
class Mesh;
class aiNode;
struct aiScene;
class aiMesh;

class ModelLoader
{
public:
	ModelLoader() = default;
	std::unique_ptr<Model> loadModel(std::string filePath);

private:
	void processNode(aiNode* node, const aiScene* scene);
	std::unique_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<std::unique_ptr<Mesh>> m_meshes;

};
