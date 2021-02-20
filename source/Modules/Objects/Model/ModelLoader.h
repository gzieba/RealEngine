#pragma once

#include <string>
#include <vector>
#include <memory>
#include <assimp/material.h>

class Model;
class Mesh;
class aiNode;
struct aiScene;
class aiMesh;
class aiMaterial;

class ModelLoader
{
	typedef std::tuple<unsigned char*, int, int, int> Texture2D;

public:
	ModelLoader() = default;
	std::unique_ptr<Model> loadModel(std::string filePath);

private:
	void processNode(aiNode* node, const aiScene* scene);
	std::unique_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);
	Texture2D createTexture2D(const char* fileName);
	std::vector<Texture2D> loadMaterialTextures(aiMaterial* material, aiTextureType type);

	std::vector<std::unique_ptr<Mesh>> m_meshes;
	std::string m_directory;
	std::string m_modelName;

};
