#pragma once

#include <string>
#include <vector>
#include <memory>
#include <assimp/material.h>
#include "Modules/Renderer/TextureType.h"

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
	static std::pair<TextureType, Texture2D> createTexture2D(TextureType type, const char* fileName);

private:
	void processNode(aiNode* node, const aiScene* scene);
	std::unique_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<std::unique_ptr<Mesh>> m_meshes;
	std::string m_directory;
	std::string m_modelName;

};
