#pragma once

#include <string>
#include <vector>

class Model;
class Mesh;
class aiNode;
class aiScene;
class aiMesh;

class ModelLoader
{
public:
	ModelLoader();
	Model* loadModel(std::string filePath);

private:
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Mesh*> m_meshes;

};
